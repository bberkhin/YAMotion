#pragma once

#include "environmentsimple.h"
#include "executorlog.h"
#include "ExecutorView.h"
#include "GCodeInterpreter.h"

class Worker;

class CheckGCodeThread : public wxThread
{
public:
	CheckGCodeThread(Worker *handler, const wxString &fname_);
	~CheckGCodeThread();
protected:
	virtual wxThread::ExitCode Entry();
	Worker *m_woker;
	LoggerWnd *plogger;
	ExecutorLogWnd *pexec;
	GCodeInterpreter *ppret;
	wxString fname;
};



class SimulateGCodeThread : public wxThread
{
public:
	SimulateGCodeThread(Worker *handler, const wchar_t *fname_);
	~SimulateGCodeThread();

	std::vector<TrackPoint> *getTack() { return pexec->getTrack(); }
	CoordsBox getBox() { return pexec->getBox(); }

	void Update3DView();
	
protected:
	virtual wxThread::ExitCode Entry();
	Worker *m_worker;
	LoggerWnd *plogger;
	ExecutorView *pexec;
	GCodeInterpreter *ppret;
	wxString fname;
	//View3D *m_3Dview;
};



class FilePage;
class LogWindow;

class Worker : public wxEvtHandler
{
	friend class CheckGCodeThread;
	friend class SimulateGCodeThread;
public:
	Worker(FilePage *fp);
	~Worker();
	void DoClose();
	bool IsRunning() { 	return (!m_checkThread || !m_simulateThread); 	}
	void  CheckGCode();
	void  Draw3D();
	LogWindow *GetLogWnd();

private:
	void DoDraw(const wchar_t *fname);
	wxString GetSavedFileName();

public:
	
private:

	FilePage *m_fp;	
	wxCriticalSection m_critsect;
	CheckGCodeThread *m_checkThread;
	SimulateGCodeThread *m_simulateThread;
};