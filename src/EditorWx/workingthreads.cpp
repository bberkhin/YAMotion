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
//#include "wx/filename.h" // filename support
#include "defsext.h"



wxIMPLEMENT_DYNAMIC_CLASS(GCMCConversionEvent, wxThreadEvent);

//wxDEFINE_EVENT(EVT_CHECK_GCODE_UPDATE, GCMCConversionEvent);
wxDEFINE_EVENT(EVT_CHECK_GCODE_COMPLETE, GCMCConversionEvent);
//wxDEFINE_EVENT(EVT_CHECK_SIMULATE_UPDATE, GCMCConversionEvent);
wxDEFINE_EVENT(EVT_CHECK_SIMULATE_COMPLETE, GCMCConversionEvent);



CheckGCodeThread::CheckGCodeThread(Worker *woker, const wxString &fname_)
: fname(fname_), wxThread(wxTHREAD_DETACHED)
{

	m_woker = woker;
	pexec = new ExecutorLogWnd(m_woker, true);
	plogger = new LoggerWnd(m_woker);
	ppret = new GCodeInterpreter(wxGetApp().GetEnvironment(), pexec, plogger);

}

CheckGCodeThread::~CheckGCodeThread()
{
	
	wxCriticalSectionLocker enter(m_woker->m_critsect);
	m_woker->m_checkThread = NULL;

	if (pexec) delete pexec;
	if (plogger) delete plogger;
	if (ppret) delete ppret;
}


wxThread::ExitCode CheckGCodeThread::Entry()
{
	if (ppret)
	{
		if (!ppret->open_nc_file(fname.c_str()))
		{
			plogger->log(LOG_ERROR, _("Can not open file: %s"), fname.c_str());
			return NULL;
		}
		ppret->execute_file();
	}

	ConvertGCMCInfo dt;
	dt.feed_len = pexec->get_feed_len();
	dt.traverce_len = pexec->get_traverce_len();
	dt.box = pexec->getBox();

	GCMCConversionEvent *ev = new GCMCConversionEvent(EVT_CHECK_GCODE_COMPLETE);
	ev->SetCIData(dt);
	wxQueueEvent(m_woker, ev);
	return NULL;
}



Draw3DThread::Draw3DThread(Worker *worker, const wchar_t *fname_)
	: fname(fname_), wxThread(wxTHREAD_DETACHED)
{

	m_worker = worker;
	plogger = new LoggerWnd(m_worker);
	pexec = new ExecutorView(plogger);
	ppret = new GCodeInterpreter(wxGetApp().GetEnvironment(), pexec, plogger);
}

void Draw3DThread::Update3DView()
{
	
	View3D *p3Dview = m_worker->m_fp->Get3D();
	if (p3Dview)
	{
		p3Dview->setTrack(getTack());
		p3Dview->setBox(getBox());
	}
}

Draw3DThread::~Draw3DThread()
{
	wxCriticalSectionLocker enter(m_worker->m_critsect);
	// the thread is being destroyed; make sure not to leave dangling pointers around	
	Update3DView();
	m_worker->m_simulateThread = NULL;
	if (pexec) delete pexec;
	if (plogger) delete plogger;
	if (ppret) delete ppret;
}


wxThread::ExitCode Draw3DThread::Entry()
{
	if (ppret)
	{
		if (!ppret->open_nc_file(fname.c_str()))
		{
			plogger->log(LOG_ERROR, _("Can not open file: %s"), fname.c_str());
			return NULL;
		}
		ppret->execute_file();
	}
	//output stat
	ConvertGCMCInfo dt;
	dt.feed_len = pexec->get_feed_len();
	dt.traverce_len = pexec->get_traverce_len();
	dt.box = pexec->getBox();
	GCMCConversionEvent *ev = new GCMCConversionEvent(EVT_CHECK_SIMULATE_COMPLETE);
	ev->SetCIData(dt);
	wxQueueEvent(m_worker, ev);
	return NULL;
}


GcmcProcess::GcmcProcess(Worker *worker, const wchar_t *dstfn, DoAfterConvertGcmc todo)
: m_worker(worker) ,dst_file(dstfn), what_to_do(todo), wxProcess( wxGetApp().GetFrame() )
{
	Redirect();
}


void GcmcProcess::OnTerminate(int pid, int status)
{
	// show the rest of the output
	while (HasInput())
		;

	m_worker->GcmcProcessTerminated(status, dst_file.c_str(), what_to_do);
}

bool GcmcProcess::HasInput()
{
	bool hasInput = false;

	if (IsInputAvailable())
	{
		wxTextInputStream tis(*GetInputStream());
		// this assumes that the output is always line buffered
		wxString msg;
		msg << tis.ReadLine();
		m_worker->AppendGcmcError(msg);
		hasInput = true;
	}

	if (IsErrorAvailable())
	{
		wxTextInputStream tis(*GetErrorStream());
		// this assumes that the output is always line buffered
		wxString msg;
		msg << tis.ReadLine();
		m_worker->AppendGcmcError(msg);
		hasInput = true;
	}
	return hasInput;
}




wxBEGIN_EVENT_TABLE(Worker, wxEvtHandler)
	// PROCESSING
	EVT_THREAD(CHECK_GCODE_UPDATE, Worker::OnCheckGCodeUpdate)
	EVT_GCMC_CONVERSION(EVT_CHECK_GCODE_COMPLETE, Worker::OnCheckGCodeCompletion)
	EVT_THREAD(CHECK_SIMULATE_UPDATE, Worker::OnDraw3DUpdate)
	EVT_GCMC_CONVERSION(EVT_CHECK_SIMULATE_COMPLETE, Worker::OnDraw3DCompletion)
	EVT_TIMER(wxID_ANY, Worker::OnTimer)
wxEND_EVENT_TABLE()


Worker::Worker(FilePage *fp) : m_timer(this), m_fp(fp)
{
	m_checkThread = NULL;
	m_simulateThread = NULL;
	m_gcmcProcess = NULL;
	m_gcmc_running_in_sec = 0;
}
Worker::~Worker()
{
	StopAll();
}

void Worker::StopAll()
{
	if (m_timer.IsRunning())
		m_timer.Stop();

	View3D *view = m_fp->Get3D();
	if (view)
		view->processClosing();

	wxCriticalSectionLocker enter(m_critsect);
	if (m_checkThread)         // does the thread still exist?
	{
		m_checkThread->Delete();
	}

	if (m_simulateThread)
	{
		m_simulateThread->Delete();
	}

	while (1)
	{
		{ // was the ~MyThread() function executed?
			wxCriticalSectionLocker enter(m_critsect);
			if (!m_checkThread && !m_simulateThread)
				break;
		}
		// wait for thread completion
		wxThread::This()->Sleep(1);
	}
	m_checkThread = NULL;
	m_simulateThread = NULL;
}



void  Worker::Check()
{
	if (IsRunning())
		return;

	Edit *pedit = m_fp->GetEdit();
	if (!pedit)
		return;

	wxString fname = GetSavedFileName();
	
	if (fname.empty())
		return;
	
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


void  Worker::Draw3D()
{
	if (IsRunning() )
		return;

	Edit *pedit = m_fp->GetEdit();
	if (!pedit)
		return;


	wxString fname = GetSavedFileName();
	if (fname.empty())
		return;

	m_fp->GetLogWnd()->Clear();

	if (pedit->GetFileType() == FILETYPE_NC)
	{
		Do3DDraw(fname.c_str());
	}
	else if (pedit->GetFileType() == FILETYPE_GCMC)
	{
		 DoConvertGcmc(ConvertGcmc3DDraw);
	}
}


void Worker::Do3DDraw(const wchar_t *fname)
{
	if (m_simulateThread == NULL)
	{
		m_simulateThread = new Draw3DThread(this, fname);
		if (m_simulateThread->Run() != wxTHREAD_NO_ERROR)
		{
			m_fp->GetLogWnd()->Append(MSLError, _("Can't create the thread to run simulate"));
			delete m_simulateThread;
			m_simulateThread = NULL;

		}
	}
}


LogWindow *Worker::GetLogWnd()
{ 
	return m_fp->GetLogWnd(); 
}

wxString Worker::GetSavedFileName()
{
	if (!m_fp->DoFileSave(false, false))
		return wxString();

	Edit *pedit = m_fp->GetEdit();
	return  pedit ? pedit->GetFileName() : wxString();
}


void Worker::OnCheckGCodeCompletion(GCMCConversionEvent &ev)
{
	GetLogWnd()->Append(MSLInfo, _("Checking completed"));
	m_fp->UpdateStatistics(ev.GetCIData());

}

void Worker::OnCheckGCodeUpdate(wxThreadEvent &ev)
{
	// convert from ILogerr Error Code to LogWindow error 
	MsgStatusLevel lvl = (MsgStatusLevel)ev.GetInt();
	int linen = static_cast<int>(ev.GetExtraLong());
	GetLogWnd()->Append(lvl, ev.GetString(), linen, true);
}

void Worker::OnDraw3DUpdate(wxThreadEvent &ev)
{
	GetLogWnd()->Append(MSLInfo, ev.GetString());
}

void Worker::OnDraw3DCompletion(GCMCConversionEvent &ev)
{
	GetLogWnd()->Append(MSLInfo, _("Drawing completed"));
	m_fp->UpdateStatistics( ev.GetCIData() );
}




bool Worker::CheckFileExist(const wchar_t *fname)
{
	if (StandartPaths::Get()->CheckFileExist(fname))
		return true;

	wxString inf = wxString::Format("File %s not found.", fname);
	GetLogWnd()->Append(MSLError, inf);
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
		if ((colon2 = src.find(':', colon1 + 1)) != wxString::npos)
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
		if (tmp.compare(L"warning") == 0)
			lvl = MSLWarning;

		output += src.Mid(colon4 + 1).wc_str(); // get message
		GetLogWnd()->Append(lvl, output.c_str(), linen);
	}

}


int Worker::RunGcmc(const wchar_t *src_fname, const  wchar_t *dst_fname, const wchar_t *args, DoAfterConvertGcmc what_to_do)
{

	GetLogWnd()->Clear();
	// cheks files
	if (!CheckFileExist(src_fname))
		return 1;

	wxExecuteEnv env;

	env.cwd = StandartPaths::Get()->GetDirFromFName(src_fname).c_str();
	// get file name without path
	std::filesystem::path src_fname_no_path = std::filesystem::path(src_fname).filename();
	std::filesystem::path dst_fname_no_path;

	if (StandartPaths::Get()->GetDirFromFName(dst_fname).compare(env.cwd) == 0)
		dst_fname_no_path = std::filesystem::path(dst_fname).filename();
	else
		dst_fname_no_path = dst_fname;


	wxString arg = StandartPaths::Get()->GetExecutablePath(L"gcmc_vc.exe").c_str();

	if (!CheckFileExist(arg))
		return 1;

	arg += " -o ";
	arg += dst_fname_no_path.c_str();
	arg += " ";
	if (args)
		arg += args;
	arg += " ";
	arg += src_fname_no_path.c_str();

	wxArrayString output;
	wxArrayString errors;


#if 0 
	m_logwnd->Append(MSLInfo, L"Start converting...");
	m_logwnd->Append(MSLInfo, arg.c_str());
	int code = wxExecute(arg, output, errors, wxEXEC_SYNC | wxEXEC_HIDE_CONSOLE, &env);
	for (size_t i = 0; i < errors.Count(); ++i)
	{
		AppendGcmcError(errors[i]);
	}

	wxString inf = wxString::Format("Process terminated with exit code %d", code);
	m_logwnd->Append(code == 0 ? MSLInfo : MSLError, inf);

	return code;
#endif

	if (m_gcmcProcess)
	{
		GetLogWnd()->Append(MSLInfo, _("gcmc_vc.exe already running"));
		return 1;
	}
	GetLogWnd()->Append(MSLInfo, _("Start converting..."));
	GetLogWnd()->Append(MSLInfo, arg.c_str());

	if (m_timer.IsRunning())
		m_timer.Stop();

	m_gcmc_running_in_sec = 0;
	m_timer.Start(1000);

	m_gcmcProcess = new GcmcProcess(this, dst_fname, what_to_do);
	int code = wxExecute(arg, wxEXEC_ASYNC | wxEXEC_HIDE_CONSOLE | wxEXEC_NODISABLE, m_gcmcProcess, &env);
	return code;

}


void Worker::SendEvnToFrame(wxEventType commandType, const wchar_t *str, int i)
{
	wxCommandEvent event(commandType);
	if ( str )
		event.SetString(str);
	if ( i != -1 )
		event.SetInt(i);

	event.SetEventObject(this);
	wxGetApp().GetFrame()->ProcessWindowEvent(event);
}

void Worker::GcmcProcessTerminated(int status, const wchar_t *dst_fname, DoAfterConvertGcmc what_to_do)
{

	if (m_gcmcProcess)
	{
		m_gcmc_running_in_sec = 0;
		m_timer.Stop();
		wxString inf = wxString::Format(_("Process terminated with exit code %d"), status);
		GetLogWnd()->Append(status == 0 ? MSLInfo : MSLError, inf);
		Edit *pedit;
		if (status == 0)
		{
			switch (what_to_do)
			{
				case ConvertGcmcOpenFile:
					wxGetApp().GetFrame()->FileOpen(dst_fname);
					break;
				case ConvertGcmcPasteFile:
					pedit = m_fp->GetEdit();
					if (pedit != NULL)
						pedit->PasteFile(dst_fname);
					break;
				case ConvertGcmcNewFile:	
					//SendEvnToFrame(FILE_NEW_EVENT, dst_fname, FILETYPE_NC);
					wxGetApp().GetFrame()->DoNewFile(FILETYPE_NC, wxEmptyString, true, dst_fname);
					break;
				case ConvertGcmc3DDraw:
					Do3DDraw(dst_fname);
					break;
			}
		}
		delete m_gcmcProcess;
		m_gcmcProcess = NULL;
	}
}

int Worker::DoConvertGcmc(DoAfterConvertGcmc what_to_do)
{
	Edit *pedit = m_fp->GetEdit();
	if (!pedit)
		return 1;

	wxString src_fname = pedit->GetFileName();
	if (src_fname.IsEmpty())
		return 1;
	wxString dst_fname = src_fname.BeforeLast('.');
	if (dst_fname.IsEmpty())
		dst_fname = src_fname;
	dst_fname += wxString(".nc");

	return RunGcmc(src_fname, dst_fname, 0, what_to_do);
}

void Worker::OnTimer(wxTimerEvent &event)
{
	static bool needToAsk = true;
	if (m_gcmc_running_in_sec == 0)
		needToAsk = true;

	wxTimer &tm = event.GetTimer();
	m_gcmc_running_in_sec++;

	//SetTitle(wxString::Format(L"Process gcmc %d sec.", m_gcmc_running_in_sec));
	if (m_gcmcProcess && needToAsk && (m_gcmc_running_in_sec % 60) == 0)
	{
		int rez = wxMessageBox(_("GCMC is running very long time/ Would you like to kill the process?"), wxMessageBoxCaptionStr,
			wxYES_NO | wxICON_QUESTION);
		if (rez == wxYES)
			wxKill(m_gcmcProcess->GetPid(), wxSIGKILL, NULL, wxKILL_CHILDREN);
	}
}