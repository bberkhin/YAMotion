#include "wx/wx.h"
#include "wx/event.h"
#include <wx/thread.h>
#include "wx/process.h"
#include "defsext.h"
#include "app.h"

#include "workingthreads.h"
#include "editorpanel.h"
#include "edit.h"
#include "logwindow.h"
#include "View3D.h"

//#include "wx/filename.h" // filename support

//#include "appframe.h"


CheckGCodeThread::CheckGCodeThread(Worker *woker, const wxString &fname_)
: fname(fname_), wxThread(wxTHREAD_DETACHED)
{

	m_woker = woker;
	pexec = new ExecutorLogWnd(m_woker->GetLogWnd(), true);
	plogger = new LoggerWnd(m_woker->GetLogWnd());
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

	plogger->log(LOG_INFORMATIONSUM, _("Feed Lenght: %f"), pexec->get_feed_len());
	plogger->log(LOG_INFORMATIONSUM, _("Traverce Lenght: %f"), pexec->get_traverce_len());
	plogger->log(LOG_INFORMATIONSUM, _("X Min: %f X Max %f"), pexec->getBox().Min.x, pexec->getBox().Max.x);
	plogger->log(LOG_INFORMATIONSUM, _("Y Min: %f Y Max %f"), pexec->getBox().Min.y, pexec->getBox().Max.y);
	plogger->log(LOG_INFORMATIONSUM, _("Z Min: %f Z Max %f"), pexec->getBox().Min.z, pexec->getBox().Max.z);

	wxQueueEvent(m_woker, new wxThreadEvent(wxEVT_THREAD, CHECK_GCODE_COMPLETE));
	return NULL;
}



SimulateGCodeThread::SimulateGCodeThread(Worker *worker, const wchar_t *fname_)
	: fname(fname_), wxThread(wxTHREAD_DETACHED)
{

	m_worker = worker;
	pexec = new ExecutorView(plogger);
	plogger = new LoggerWnd(m_worker->GetLogWnd());
	ppret = new GCodeInterpreter(wxGetApp().GetEnvironment(), pexec, plogger);
}

void SimulateGCodeThread::Update3DView()
{
	
	View3D *p3Dview = m_worker->m_fp->Get3D();
	if (p3Dview)
	{
		p3Dview->setTrack(getTack());
		p3Dview->setBox(getBox());
	}
}

SimulateGCodeThread::~SimulateGCodeThread()
{
	wxCriticalSectionLocker enter(m_worker->m_critsect);
	// the thread is being destroyed; make sure not to leave dangling pointers around	
	Update3DView();
	m_worker->m_simulateThread = NULL;
	if (pexec) delete pexec;
	if (plogger) delete plogger;
	if (ppret) delete ppret;
}


wxThread::ExitCode SimulateGCodeThread::Entry()
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

	wxQueueEvent(m_worker, new wxThreadEvent(wxEVT_THREAD, CHECK_SIMULATE_COMPLETE));
	return NULL;
}





Worker::Worker(FilePage *fp) : m_fp(fp)
{
	m_checkThread = NULL;
	m_simulateThread = NULL;
}
Worker::~Worker()
{
	DoClose();
}

void Worker::DoClose()
{
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

	
}



void  Worker::CheckGCode()
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
		;// DoConvertGcmc(ConvertGcmcNothing);
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
		DoDraw(fname.c_str());
	}
	else if (pedit->GetFileType() == FILETYPE_GCMC)
	{
		;// DoConvertGcmc(ConvertGcmcRunSimilate);
	}
}


void Worker::DoDraw(const wchar_t *fname)
{
	if (m_simulateThread == NULL)
	{
		m_simulateThread = new SimulateGCodeThread(this, fname);
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

/*
void AppFrame::OnSimulateCompletion(wxThreadEvent&)
{
	//drea
	wxCriticalSectionLocker enter(critsect);
	if (simulateThread)
	{
		simulateThread->Update3DView();
	}
}
*/