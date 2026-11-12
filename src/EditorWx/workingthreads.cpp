#include "wx/wx.h"

#include "workingthreads.h"
#include "editorpanel.h"
#include "edit.h"
#include "logwindow.h"
#include "View3D.h"
#include "standartpaths.h"


#include "app.h"
#include "appframe.h"
#include "wx/txtstrm.h"
#include "wx/cmdline.h"
#include "wx/tokenzr.h"
//#include "wx/filename.h" // filename support
#include "defsext.h"



wxIMPLEMENT_DYNAMIC_CLASS(GCMCConversionEvent, wxThreadEvent);
wxIMPLEMENT_DYNAMIC_CLASS(SimulateThreadEvent, wxThreadEvent);

wxDEFINE_EVENT(EVT_CHECK_GCODE_COMPLETE, GCMCConversionEvent);
wxDEFINE_EVENT(EVT_DRAW_GCODE_COMPLETE, GCMCConversionEvent);
wxDEFINE_EVENT(EVT_SIMULATE_UPDATE, SimulateThreadEvent);
wxDEFINE_EVENT(EVT_SIMULATE_COMPLETE, SimulateThreadEvent);


CheckGCodeThread::CheckGCodeThread(Worker *woker, const wxString &fname_)
: fname(fname_), wxThread(wxTHREAD_DETACHED)
{

	m_woker = woker;
	Preferences *pref = Preferences::Get();	
	plogger = new LoggerWnd(m_woker);
	pexec = new ExecutorLogWnd(plogger,this, pref->Common().enableLogExecution);
	ppret = new GCodeInterpreter(wxGetApp().GetEnvironment(), pexec, plogger, 100 );
	m_woker->m_fp->GetLogWnd()->StartPulse();
}

CheckGCodeThread::~CheckGCodeThread()
{
	
	wxCriticalSectionLocker enter(m_woker->m_critsect);
	m_woker->m_checkThread = NULL;
	if (pexec) delete pexec;
	if (plogger) delete plogger;
	if (ppret) delete ppret;
	m_woker->m_fp->GetLogWnd()->StopPulse();
}


wxThread::ExitCode CheckGCodeThread::Entry()
{
	if (ppret)
	{
		if (!ppret->open_nc_file(fname.GetFullPath().wc_str()))
		{
			plogger->log(LOG_ERROR, wxString::Format(_("Can not open file: %s ..."), fname.GetFullPath()).c_str() );
			return NULL;
		}
		plogger->log(LOG_INFORMATION, wxString::Format(_("Start checking: %s"), fname.GetFullName()).c_str());
		ppret->execute_file();
	}

	ConvertGCMCInfo dt;
	dt.exit_code = ppret->get_state().code;
	dt.num_errors = plogger->errors_count();
	dt.feed_len = pexec->get_feed_len();
	dt.traverce_len = pexec->get_traverce_len();
	dt.box = pexec->getBox();
	dt.runsimulaion = false;
	GCMCConversionEvent *ev = new GCMCConversionEvent(EVT_CHECK_GCODE_COMPLETE);
	ev->SetCIData(dt);
	wxQueueEvent(m_woker, ev);
	
	return NULL;
}



Draw3DThread::Draw3DThread(Worker *worker, const wchar_t *fname_, bool runsimulation)
	: fname(fname_), m_runsimulation(runsimulation), wxThread(wxTHREAD_DETACHED)
{

	m_worker = worker;
	plogger = new LoggerWnd(m_worker);
	pexec = new ExecutorView(plogger, wxGetApp().GetEnvironment(), this );
	ppret = new GCodeInterpreter(wxGetApp().GetEnvironment(), pexec, plogger, 100);
	m_worker->m_fp->GetLogWnd()->StartPulse();
}

Draw3DThread::~Draw3DThread()
{
	wxCriticalSectionLocker enter(m_worker->m_critsect);
	Update3DView();
	m_worker->m_drawThread = NULL;
	if (pexec) delete pexec;
	if (plogger) delete plogger;
	if (ppret) delete ppret;
	m_worker->m_fp->GetLogWnd()->StopPulse();
}

void Draw3DThread::Update3DView()
{	
	View3D *p3Dview = m_worker->m_fp->Get3D();
	if (p3Dview)
	{
		if (getTack().empty())
		{
			p3Dview->clear();
		}
		else
		{
			p3Dview->setTrack(getTack());
			p3Dview->setBox(getBox());
		}
		/*
		if ( plogger->errors_count() == 0)
		{
			p3Dview->setTrack(getTack());
			p3Dview->setBox(getBox());
		}
		else
			p3Dview->clear();
			*/
	}
}

wxThread::ExitCode Draw3DThread::Entry()
{
	if (!ppret->open_nc_file(fname.GetFullPath().c_str()))
	{
		plogger->log(LOG_ERROR, wxString::Format(_("Can not open file: %s ..."), fname.GetFullPath()).c_str());
		return NULL;
	}
	plogger->log(LOG_INFORMATION, wxString::Format(_("Start checking & drawing: %s"), fname.GetFullName()).c_str());

	ppret->execute_file();
	
	//output stat
	ConvertGCMCInfo dt;
	dt.exit_code = ppret->get_state().code;
	dt.num_errors = plogger->errors_count();
	dt.feed_len = pexec->get_feed_len();
	dt.traverce_len = pexec->get_traverce_len();
	dt.box = pexec->getBox();
	dt.runsimulaion = m_runsimulation;
	GCMCConversionEvent *ev = new GCMCConversionEvent(EVT_DRAW_GCODE_COMPLETE);
	ev->SetCIData(dt);
	wxQueueEvent(m_worker, ev);
	return NULL;
}


wxThread::ExitCode SimulateCutting::Entry()
{

	size_t tracksize;
	TrackPointGL end_point;
	View3D *view = m_worker->m_fp->Get3D();
	if (!view)
		return 0;


	TrackPoints &track = view->getTrack();
	tracksize = track.size();
	if (tracksize < 2) // nothing to do
	{
		wxQueueEvent(view, new SimulateThreadEvent(EVT_SIMULATE_COMPLETE));
		return 0;
	}
	int tickdelay = 50; // fix
	double distancefortick;
	double segmentdist = 0;
	double currentdistoftick = 0;
	double fulldistance = 0;
	TrackPointGL second;

	// check may be we are srtarting not from the starting point
	end_point = track[0];
	
	size_t i = 1;

	if (view->simulateLastIndex != wxNOT_FOUND)
	{
		i = view->simulateLastIndex + 1;
		end_point = track[i-1];
		//calc full distance for good updates
		for (size_t j = 1; j < i; j++)
		{
			fulldistance += glm::distance(track[j - 1].position, track[j].position);
		}

	}
	int lastspeed = end_point.speed * m_speedk;
	int newspeed;
	bool first = true;
	while (i < tracksize)
	{

		if (TestDestroy())
			break;

		{
			wxCriticalSectionLocker enter(m_worker->m_critsect);
			second = track[i];
			newspeed = second.speed * m_speedk;
		}
		//calculate tick distance 	
		
		if (first)
		{
			lastspeed = newspeed;
			first = false;
		}

		else if (newspeed != lastspeed) // we move from point
		{
			lastspeed = newspeed;
			glm::vec3 move =  (second.position - end_point.position);
			end_point = second;
			fulldistance += move.length();
			currentdistoftick = 0;
			wxMilliSleep(tickdelay);
			SimulateThreadEvent event(i - 1, int(fulldistance), end_point, EVT_SIMULATE_UPDATE);
			wxQueueEvent(m_worker, event.Clone());
			i++;
			continue;
		}
		
		segmentdist = glm::distance(end_point.position, second.position);
		distancefortick = (newspeed / 60.f) * (tickdelay / 1000.f); //(to mm_in_sek)/sec			

	    if (currentdistoftick + segmentdist < distancefortick) // add point to the step
		{
			fulldistance += segmentdist;
			currentdistoftick += segmentdist;
			end_point = second;
			++i;
		}
		else // we should fine next end_point on the same segment
		{
			double needdistanse = distancefortick - currentdistoftick;
			float k = float(needdistanse / segmentdist);
			fulldistance += needdistanse;
			
			glm::vec3 move = k * (second.position - end_point.position);
			end_point.position = end_point.position + move;
			end_point.line = second.line;
			end_point.isFast = second.isFast;
			currentdistoftick = 0;
			
			wxMilliSleep(tickdelay);
			
			SimulateThreadEvent event(i-1, int(fulldistance), end_point, EVT_SIMULATE_UPDATE);
			wxQueueEvent(m_worker, event.Clone());
		}
	}
	SimulateThreadEvent event(-1, -1, second, EVT_SIMULATE_UPDATE);
	wxQueueEvent(m_worker, event.Clone());

	wxQueueEvent(m_worker, new SimulateThreadEvent(EVT_SIMULATE_COMPLETE));
	return 0;
}

SimulateCutting::~SimulateCutting()
{
	wxCriticalSectionLocker enter(m_worker->m_critsect);
	m_worker->m_simulateThread = NULL;
}





GcmcRunThread::GcmcRunThread(Worker *worker, const std::vector<std::string> &args, const wxString &workdir,
	const wchar_t *dstfn, DoAfterConvertGcmc todo)
	: wxThread(wxTHREAD_JOINABLE), m_worker(worker), m_args(args), m_workdir(workdir.mb_str(wxConvLocal)),
	m_dstFile(dstfn), m_todo(todo), m_cancel(0)
{
}

void GcmcRunThread::LogCallback(const char *text, void *user)
{
	// called on the compiler thread while it works: pass the lines on to the GUI thread
	GcmcRunThread *self = static_cast<GcmcRunThread *>(user);
	wxThreadEvent *ev = new wxThreadEvent(wxEVT_THREAD, GCMC_RUN_OUTPUT);
	ev->SetString(wxString(text, wxConvAuto()));
	wxQueueEvent(self->m_worker, ev);
}

wxThread::ExitCode GcmcRunThread::Entry()
{
	std::vector<char *> argv;
	for (std::string &a : m_args)
		argv.push_back(&a[0]);
	argv.push_back(NULL);

	gcmc_params_t params;
	memset(&params, 0, sizeof(params));
	params.workdir = m_workdir.empty() ? NULL : m_workdir.c_str();
	params.log = LogCallback;
	params.log_user = this;
	params.cancel = &m_cancel;

	int rc = gcmc_run((int)m_args.size(), argv.data(), &params);

	wxThreadEvent *ev = new wxThreadEvent(wxEVT_THREAD, GCMC_RUN_FINISHED);
	ev->SetInt(rc);
	wxQueueEvent(m_worker, ev);
	return (ExitCode)0;
}







wxBEGIN_EVENT_TABLE(Worker, wxEvtHandler)
	// PROCESSING
	EVT_THREAD(CHECK_GCODE_UPDATE, Worker::OnCheckGCodeUpdate)
	EVT_GCMC_CONVERSION(EVT_CHECK_GCODE_COMPLETE, Worker::OnCheckGCodeCompletion)
	EVT_THREAD(DRAW_GCODE_UPDATE, Worker::OnDraw3DUpdate)
	EVT_GCMC_CONVERSION(EVT_DRAW_GCODE_COMPLETE, Worker::OnDraw3DCompletion)
	EVT_TIMER(wxID_ANY, Worker::OnTimer)
	EVT_THREAD(GCMC_RUN_OUTPUT, Worker::OnGcmcOutput)
	EVT_THREAD(GCMC_RUN_FINISHED, Worker::OnGcmcFinished)

	EVT_SIMULATION(EVT_SIMULATE_UPDATE, Worker::OnSimulateUpdate)
	EVT_SIMULATION(EVT_SIMULATE_COMPLETE, Worker::OnSimulateCompletion)
wxEND_EVENT_TABLE()


Worker::Worker(FilePage *fp) : m_timer(this), m_fp(fp)
{
	m_checkThread = NULL;
	m_drawThread = NULL;
	m_gcmcThread = NULL;
	m_simulateThread = NULL;
	m_mathThread = NULL;
	m_gcmc_running_in_sec = 0;
	m_speedk = 1;
}

Worker::~Worker()
{
	StopAll();
}

void Worker::StopAll()
{
	if (m_timer.IsRunning())
		m_timer.Stop();

	{
		wxCriticalSectionLocker enter(m_critsect);
		if (m_checkThread)         // does the thread still exist?
		{
			//m_checkThread->Kill();
			m_checkThread->Delete(); //Kill();
		}

		if (m_drawThread)
		{
			m_drawThread->Delete(); //->Kill();
		}
		if (m_simulateThread)
		{
			if (!m_simulateThread->IsRunning())
				m_simulateThread->Resume();
			//m_simulateThread->Kill();
			m_simulateThread->Delete(); //Kill();
		}
		if (m_mathThread)
		{
			m_mathThread->Delete(); //Kill();
		}
		if (m_gcmcThread)
			m_gcmcThread->Cancel();
	}

	while (1)
	{
		{ // was the ~MyThread() function executed?
			wxCriticalSectionLocker enter(m_critsect);
			if (!m_checkThread && !m_drawThread && !m_simulateThread && !m_mathThread)
				break;
		}
		// wait for thread completion
		wxThread::This()->Sleep(1);
	}
	m_checkThread = NULL;
	m_drawThread = NULL;
	m_simulateThread = NULL;
	m_mathThread = NULL;
	if (m_gcmcThread)
	{
		m_gcmcThread->Wait();
		delete m_gcmcThread;
		m_gcmcThread = NULL;
	}
}



void  Worker::Check()
{
	if (IsRunning())
		return;

	wxString fname = m_fp->GetSavedFileName();	
	if (fname.empty())
		return;

	Edit *pedit = m_fp->GetEdit();
	m_fp->GetLogWnd()->Clear();

	if (pedit->GetFileType() == FILETYPE_NC)
	{
		m_checkThread = new CheckGCodeThread(this, fname);
		if (m_checkThread->Run() != wxTHREAD_NO_ERROR)
		{
			wxLogError("Can't create the thread!");
			delete m_checkThread;
			m_checkThread = NULL;
		}
	}
	else if (pedit->GetFileType() == FILETYPE_GCMC)
	{
		 DoConvertGcmc(ConvertGcmcNothing);
	}
}


void  Worker::Draw3D(bool runsimulation)
{
	if (IsRunning())
		return;
	wxString fname = m_fp->GetSavedFileName();
	if (fname.empty())
		return;
	
	Edit *pedit = m_fp->GetEdit();
	m_fp->GetLogWnd()->Clear();

	if (pedit->GetFileType() == FILETYPE_NC)
	{
		Do3DDraw( fname.c_str(), runsimulation);
	}
	else if (pedit->GetFileType() == FILETYPE_GCMC)
	{
		 DoConvertGcmc(runsimulation ? ConvertGcmc3DDrawAndSimulate : ConvertGcmc3DDraw );
	}
}


void Worker::Do3DDraw(const wchar_t *fname, bool runsimulation)
{
	if (m_drawThread == NULL)
	{
		SemulateStop();
		m_drawThread = new Draw3DThread(this, fname, runsimulation);
		if (m_drawThread->Run() != wxTHREAD_NO_ERROR)
		{
			m_fp->GetLogWnd()->Append(MSLError, _("Can't create the thread to run simulate"));
			delete m_drawThread;
			m_drawThread = NULL;

		}
	}
}


LogPane *Worker::GetLogWnd()
{ 
	return m_fp->GetLogWnd(); 
}


void Worker::OnCheckGCodeCompletion(GCMCConversionEvent &ev)
{
	if (ev.GetCIData().exit_code == PROGRAMM_ABORTED)
		GetLogWnd()->Append(MSLInfo, _("Checking aborted"));
	else if ( ev.GetCIData().num_errors == 0)
		GetLogWnd()->Append(MSLInfo, _("Checking completed with no error"));
	else
	{
		int n = ev.GetCIData().num_errors;
		GetLogWnd()->Append(MSLErrorNoLabel, _("Checking completed with ") + wxString::Format(wxPLURAL("%d error.", "%d errors.", n), n));
	}
	
	//m_fp->UpdateStatistics(ev.GetCIData());

}

void Worker::OnCheckGCodeUpdate(wxThreadEvent &ev)
{
	// convert from ILogerr Error Code to LogWindow error 
	MsgStatusLevel lvl = (MsgStatusLevel)ev.GetInt();
	int linen = static_cast<int>(ev.GetExtraLong());
	GetLogWnd()->Append(lvl, ev.GetString(), linen, true);
	if (lvl == LOG_ERROR)
		m_fp->ShowLog(); // it can be hide for 3d draw
}

void Worker::OnDraw3DUpdate(wxThreadEvent &ev)
{
	GetLogWnd()->Append(MSLInfo, ev.GetString());
}

void Worker::OnDraw3DCompletion(GCMCConversionEvent &ev)
{
	if (ev.GetCIData().exit_code == PROGRAMM_ABORTED)
		GetLogWnd()->Append(MSLInfo, _("Drawing aborted"));
	else if (ev.GetCIData().num_errors == 0)
	{
		GetLogWnd()->Append(MSLInfo, _("Drawing completed"));
		m_fp->UpdateStatistics(ev.GetCIData());
		if (ev.GetCIData().runsimulaion)
		{
			// we need check that there is exist to simulate
			View3D *view = m_fp->Get3D();
			if (view && !view->IsEmpty())
				SemulateStart();
		}
	}
	else
	{
		int n = ev.GetCIData().num_errors;
		GetLogWnd()->Append(MSLErrorNoLabel, wxString::Format(wxPLURAL("There is %d error.", "There are %d errors.", n) ,n ));
	}
}




bool Worker::CheckFileExist(const wchar_t *fname)
{
	if (StandartPaths::Get()->CheckFileExist(fname))
		return true;
	GetLogWnd()->Append(MSLError, wxString::Format("File %s not found.", fname));
	return false;

}

// Source format:
// FILENAME:LINE:CHAR: ERRORTYPE: MSG\n
// ERRORTYPE = { "error", "internal error", "fatal","warning"  }
//or just
// MSG \n

void Worker::AppendGcmcError(wxString &src)
{
	bool formated = false;
	size_t colon1 = wxString::npos, colon2 = wxString::npos, colon3 = wxString::npos, colon4 = wxString::npos;
	if ((colon1 = src.find(':', 0)) != wxString::npos)
	{
		if (colon1 == 1) // грязный костыль если полное имя файла то : не раздалитель
		{
			colon1 = src.find(':', 2);
		}
		if (colon1 != wxString::npos && ((colon2 = src.find(':', colon1 + 1)) != wxString::npos) )
		{
			if ((colon3 = src.find(':', colon2 + 1)) != wxString::npos)
			{
				if ((colon4 = src.find(':', colon3 + 1)) != wxString::npos)
				{
					formated = true;
				}
			}
		}
	}
	if (!formated)
	{
		GetLogWnd()->Append(MSLError, src);
	}
	else
	{
		std::wstring output;
		std::wstring tmp;
		std::filesystem::path path = src.SubString(0, colon1).wc_str();
		if (path.has_filename())
		{
			output = L"File: ";
			output += path.filename();
			output += L" ";
		}
		tmp = src.SubString(colon1 + 1, colon2).wc_str();
		int linen = _wtoi(tmp.c_str());
		tmp = src.SubString(colon3 + 2, colon4).wc_str(); // Erro type
		MsgStatusLevel lvl = MSLError;
		if (tmp.compare(L"warning:") == 0)
			lvl = MSLWarning;
		else if (tmp.compare(L"Runtime message():") == 0)
			lvl = MSLInfo;

		output += src.Mid(colon4 + 1).wc_str(); // get message
		GetLogWnd()->Append(lvl, output.c_str(), linen);
	}

}


int Worker::RunGcmc(const wchar_t *src_fname, const  wchar_t *dst_fname, const wchar_t *args, DoAfterConvertGcmc what_to_do, bool addprologepilog)
{

	GetLogWnd()->Clear();
	// cheks files
	if (!CheckFileExist(src_fname))
		return 1;

	// the compiler is built into the program; relative names are resolved against the source file folder
	wxString workdir = StandartPaths::Get()->GetDirFromFName(src_fname).c_str();
	// get file name without path
	std::filesystem::path src_fname_no_path = std::filesystem::path(src_fname).filename();
	std::filesystem::path dst_fname_no_path;

	if (StandartPaths::Get()->GetDirFromFName(dst_fname).compare(workdir.wc_str()) == 0)
		dst_fname_no_path = std::filesystem::path(dst_fname).filename();
	else
		dst_fname_no_path = dst_fname;

	std::vector<std::string> av;
	wxString shown = L"gcmc";
	auto add = [&](const wxString &s)
	{
		av.push_back(std::string(s.mb_str(wxConvLocal)));
		shown += L" ";
		shown += s;
	};

	av.push_back("gcmc");
	add(L"-o");
	add(dst_fname_no_path.c_str());
	if (args)
	{
		wxArrayString extra = wxCmdLineParser::ConvertStringToArgs(args, wxCMD_LINE_SPLIT_DOS);
		for (size_t i = 0; i < extra.GetCount(); ++i)
			add(extra[i]);
	}
	add(L"-q"); // do not use prologue\epilogue
	add(wxString(L"--include=") + StandartPaths::Get()->GetLibraryPath().c_str());
	add(wxString::Format(L"--precision=%d", Preferences::Get()->PostPocessing().Precision()));

	if (addprologepilog) // if we paste in thr existing file do not add prologue and epilogue
	{
		const wxString &pro_fn = Preferences::Get()->PostPocessing().PrologFileName();
		if (!pro_fn.IsEmpty())
			add(wxString::Format(L"--prologue=%s", pro_fn));

		const wxString &epi_fn = Preferences::Get()->PostPocessing().EpilogFileName();
		if (!epi_fn.IsEmpty())
			add(wxString::Format(L"--epilogue=%s", epi_fn));
	}
	add(src_fname_no_path.c_str());

	if (m_gcmcThread)
	{
		GetLogWnd()->Append(MSLInfo, _("gcmc already running"));
		return 1;
	}

	if (what_to_do == ConvertGcmcNothing || what_to_do == ConvertGcmc3DDraw )
		GetLogWnd()->Append(MSLInfo, _("Start checking..."));
	else
		GetLogWnd()->Append(MSLInfo, _("Start converting..."));

	GetLogWnd()->Append(MSLInfo, shown.c_str());

	if (m_timer.IsRunning())
		m_timer.Stop();

	m_gcmc_running_in_sec = 0;
	m_timer.Start(100);

	GetLogWnd()->StartPulse();
	m_gcmcThread = new GcmcRunThread(this, av, workdir, dst_fname, what_to_do);
	if (m_gcmcThread->Create() != wxTHREAD_NO_ERROR || m_gcmcThread->Run() != wxTHREAD_NO_ERROR)
	{
		delete m_gcmcThread;
		m_gcmcThread = NULL;
		m_timer.Stop();
		GetLogWnd()->StopPulse();
		return 1;
	}
	return 0;

}


void Worker::SendEvnToFrame(wxEventType  commandType, const wchar_t *str, int i)
{
	wxCommandEvent event(commandType);
	if ( str )
		event.SetString(str);
	if ( i != -1 )
		event.SetInt(i);

	event.SetEventObject(this);
	wxGetApp().GetFrame()->ProcessWindowEvent(event);
}

void Worker::OnGcmcOutput(wxThreadEvent &ev)
{
	// the compiler output arrives while it is running
	wxString text = ev.GetString();
	wxStringTokenizer lines(text, L"\r\n", wxTOKEN_STRTOK);
	while (lines.HasMoreTokens())
	{
		wxString msg = lines.GetNextToken();
		AppendGcmcError(msg);
	}
}

void Worker::OnGcmcFinished(wxThreadEvent &ev)
{
	if (!m_gcmcThread)
		return;

	GetLogWnd()->StopPulse();
	std::wstring dst = m_gcmcThread->m_dstFile;
	DoAfterConvertGcmc todo = m_gcmcThread->m_todo;
	GcmcProcessTerminated(ev.GetInt(), dst.c_str(), todo);
}

void Worker::GcmcProcessTerminated(int status, const wchar_t *dst_fname, DoAfterConvertGcmc what_to_do)
{

	if (m_gcmcThread)
	{
		wxString wxdstfile(dst_fname); // copy string befor delete the thread
		m_gcmc_running_in_sec = 0;
		m_timer.Stop();
		m_gcmcThread->Wait();
		delete m_gcmcThread;
		m_gcmcThread = NULL;
		wxString inf;
		if (what_to_do == ConvertGcmcNothing || what_to_do == ConvertGcmc3DDraw)
		{
			if (status == 0)
				inf = _("Checking completed with no error");
			else
				inf = _("Checking completed with errors");
		}
		else
		{
			if (status == 0)
				inf = _("Converting completed with no error");
			else
				inf = _("Converting completed with errors");
		}
		
		GetLogWnd()->Append(status == 0 ? MSLInfo : MSLErrorNoLabel, inf);
		Edit *pedit;
		if (status == 0)
		{
			switch (what_to_do)
			{
				case ConvertGcmcOpenFile:
					wxGetApp().GetFrame()->FileOpen(wxdstfile, true);
					break;
				case ConvertGcmcPasteFile:
					pedit = m_fp->GetEdit();
					if (pedit != NULL)
						pedit->PasteFile( wxdstfile );
					break;
				//case ConvertGcmcNewFile:	
				//	//SendEvnToFrame(FILE_NEW_EVENT, dst_fname, FILETYPE_NC);
				//	wxGetApp().GetFrame()->DoNewFile(FILETYPE_NC, wxEmptyString, true, dst_fname);
				//	break;
				case ConvertGcmc3DDraw:
					Do3DDraw(wxdstfile,false);
					break;
				case ConvertGcmc3DDrawAndSimulate:
					Do3DDraw(wxdstfile, true);
					break;
			}
		}
	}
}

int Worker::DoConvertGcmc(DoAfterConvertGcmc what_to_do)
{
	Edit *pedit = m_fp->GetEdit();
	if (!pedit)
		return 1;

	
	wxFileName dst_fname = pedit->GetFileName();
	if ( !dst_fname.IsOk() )
		return 1;		
	dst_fname.SetExt(Preferences::Get()->PostPocessing().FileExtension());
	return RunGcmc(pedit->GetFileName(), dst_fname.GetFullPath(), 0, what_to_do);
}

void Worker::OnTimer(wxTimerEvent &event)
{
	wxTimer &tm = event.GetTimer();
	m_gcmc_running_in_sec++;

	//SetTitle(wxString::Format(L"Process gcmc %d sec.", m_gcmc_running_in_sec));
	if (!m_gcmcThread)
		return;

	
	if (m_gcmc_running_in_sec == 600 )
	{
		m_gcmc_running_in_sec = 0;
		int rez = wxMessageBox(_("GCMC is running very long time/ Would you like to kill the process?"), wxMessageBoxCaptionStr,
			wxYES_NO | wxICON_QUESTION);
		if (rez == wxYES)
			m_gcmcThread->Cancel();
	}
	
	
}



bool  Worker::CanSimulateStart()
{
	View3D *view = m_fp->Get3D();
	if (!view) return false;

	return  !(view->IsEmpty() || (m_simulateThread && m_simulateThread->IsRunning()));
}

bool Worker::CanSimulateStop()
{
	return (m_simulateThread != NULL);
}

bool Worker::CanSimulatePaused()
{
	return (m_simulateThread && m_simulateThread->IsRunning());
}

void Worker::SemulateStart()
{
	View3D *view = m_fp->Get3D();
	if (!view)
		return;

	if (m_simulateThread)
	{
		if (!m_simulateThread->IsRunning())
			m_simulateThread->Resume();
		return;
	}

	// Run view 3d autatically one time
	if ( view->IsEmpty() )
	{
		Draw3D( true );
		return;
	}


	//view->setSimulationPos( 0 );
	//cur_gcode_line = 0;	
	m_simulateThread = new SimulateCutting(this, m_speedk);

	if (m_simulateThread->Run() != wxTHREAD_NO_ERROR)
	{
		delete m_simulateThread;
		m_simulateThread = NULL;
	}
	view->Refresh(false);

}


void Worker::SemulatePause()
{
	if (m_simulateThread && m_simulateThread->IsRunning())
		m_simulateThread->Pause();
}

void Worker::SemulateStop()
{
	//if (m_simulateThread)
		//m_simulateThread->Delete();
	StopAll();
	TrackPointGL pt;
	pt.line = 0;
	m_fp->UpdateSimulationPos(wxNOT_FOUND, wxNOT_FOUND, pt);
}


void Worker::OnSimulateUpdate(SimulateThreadEvent& evs)
{
	m_fp->UpdateSimulationPos(evs.get_index(), evs.get_distance(), evs.get_end_point() );
}

void Worker::OnSimulateCompletion(SimulateThreadEvent&)
{
	View3D *view = m_fp->Get3D();
	if (!view)
		return;

	view->setSimulationPos(wxNOT_FOUND);
}

void  Worker::SetSimulationPos(int idistance)
{
	View3D *view = m_fp->Get3D();
	if (!view)
		return;
	StopAll();
	//calculate distance
	size_t tracksize;
	TrackPointGL end_point;

	TrackPoints &track = view->getTrack();
	tracksize = track.size();
	if (tracksize < 2)
		return;

	end_point = track[0];
	double distance = idistance;
	double segmentdist = 0;
	double fulldistance = 0;
	TrackPointGL second;
	size_t i = 1;
	while (i < tracksize)
	{
		second = track[i];
		segmentdist = glm::distance(end_point.position, second.position);
		if (fulldistance + segmentdist < distance) // add point to the step
		{			
			fulldistance += segmentdist;
			end_point = second;
			++i;
		}
		else // we should find next end_point on the same segment
		{
			double needdistanse = (fulldistance + segmentdist) - distance;
			float k = 1.f - float(needdistanse / segmentdist);
			glm::vec3 move = k * (second.position - end_point.position);
			end_point.position = end_point.position + move;
			end_point.line = second.line;
			end_point.isFast = second.isFast;
			break;
		}
	}
	m_fp->UpdateSimulationPos(i-1, idistance, end_point);
}

void  Worker::SetSimulationSpeed( int times )
{
	m_speedk = times;

	View3D *view = m_fp->Get3D();
	if (!view)
		return;		
	if (m_simulateThread)
	{
		wxCriticalSectionLocker enter(m_critsect);
		m_simulateThread->SetSeedK(m_speedk);
	}


	//tickdelay = view->get_tick_delay(); // tick delay may be changed
	//int mm_in_sec = mm_in_min / 60;
//	view->setSimulationSpeed(mm_in_sec);	
	
}


MathTransform::MathTransform(Worker *worker, Edit *edit, std::shared_ptr<DoMathBase> mth)
	: m_worker(worker), m_edit(edit), m_mth(mth), wxThread(wxTHREAD_DETACHED)
{
	plogger = new LoggerWnd(m_worker);
	m_worker->m_fp->GetLogWnd()->StartPulse();
}

MathTransform::~MathTransform()
{

	wxCriticalSectionLocker enter(m_worker->m_critsect);
	m_worker->m_mathThread = NULL;
	delete plogger;
	m_worker->m_fp->GetLogWnd()->StopPulse();
}


wxThread::ExitCode MathTransform::Entry()
{
	if (!m_edit)
		return NULL;

	char strOut[MAX_GCODE_LINELEN];
	int line_start;
	int line_end;
	long from, to;
	wxString new_file_content;

	if (m_mth->InSelected())
	{
		m_edit->GetSelection(&from, &to);
		if (from == to)
		{
			plogger->log(LOG_ERROR, _("Uups there is no any selection"));
			return NULL;
		}
		line_start = m_edit->LineFromPosition(from);
		line_end = m_edit->LineFromPosition(to-1);

	}
	else
	{
		line_start = 0;
		line_end = m_edit->GetLineCount() - 1;
	}
	from = m_edit->PositionFromLine(line_start);
	if ( line_end == m_edit->GetLineCount() - 1 )
		to = m_edit->GetLastPosition();
	else
		to = m_edit->PositionFromLine(line_end + 1);

	
	// copy all lines befor target if needed
	if (m_mth->InNewFile() && from != 0 )
	{
		m_edit->SetTargetRange(0, from);
		new_file_content = m_edit->GetTargetText();
	}

	m_edit->SetTargetRange(from, to);

	plogger->log(LOG_INFORMATION, _("Start transforming: %d lines..."), line_end- line_start);
	for (int i = line_start; i <= line_end; i++)
	{
		if (TestDestroy())
		{
			plogger->log(LOG_INFORMATION, _("Transforming aborted"));
			return NULL;
		}
		
		wxString str = m_edit->GetLine(i);
		if (m_mth->Process(str.c_str(), strOut))
		{
			new_file_content += strOut;
		}
		else
			new_file_content += str;
	}
	if (!m_mth->InNewFile())
	{
		m_edit->ReplaceTarget(new_file_content);
	}
	else
	{
		// copy end of file if needed
		if (line_end != m_edit->GetLineCount() - 1)
		{
			m_edit->SetTargetRange(to, m_edit->GetLastPosition() );
			new_file_content += m_edit->GetTargetText();
		}
		FileNewEvent *ev = new FileNewEvent(FILE_NEW_EVENT);
		ev->TakeFileContext(new_file_content);
		ev->SetInt(FILETYPE_NC);
		ev->SetEventObject(m_worker);
		wxQueueEvent(wxGetApp().GetFrame(), ev);
	}

	if (m_mth->InSelected())
	{
		to = m_edit->PositionFromLine(line_end + 1);
		m_edit->SetSelection(from, m_edit->PositionBefore(to));
	}
	plogger->log(LOG_INFORMATION, _("Transforming completed."));
	return NULL;
}


void  Worker::RunMath(std::shared_ptr<DoMathBase> mth)
{
	if (IsRunning())
		return;
	
	Edit *pedit = m_fp->GetEdit();
	if (pedit->GetFileType() != FILETYPE_NC)
		return;

	m_fp->GetLogWnd()->Clear();

	m_mathThread = new MathTransform(this, pedit, mth);
	if (m_mathThread->Run() != wxTHREAD_NO_ERROR)
	{
		wxLogError("Can't create the thread!");
		delete m_mathThread;
		m_mathThread = NULL;
	}
}