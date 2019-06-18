#pragma once

#include "environmentsimple.h"
#include "executorlog.h"
#include "ExecutorView.h"
#include "GCodeInterpreter.h"
#include <wx/thread.h>
#include <wx/process.h>
#include "wx/event.h"

struct ConvertGCMCInfo
{
	double feed_len;
	double traverce_len;
	CoordsBox box;
};

class GCMCConversionEvent : public wxThreadEvent
{
public:
	GCMCConversionEvent(wxEventType command_type = -1) : wxThreadEvent(command_type) {	}
	GCMCConversionEvent(const GCMCConversionEvent& e) : wxThreadEvent(e)
	{
		m_cidata = e.GetCIData();
	}
	~GCMCConversionEvent() 
	{
		;
	}

	wxEvent *Clone() const wxOVERRIDE { return new GCMCConversionEvent(*this); }
	const ConvertGCMCInfo &GetCIData() const { return m_cidata; }
	void SetCIData(const ConvertGCMCInfo &data) { m_cidata = data; }
protected:
	ConvertGCMCInfo m_cidata;
private:
	wxDECLARE_DYNAMIC_CLASS_NO_ASSIGN(GCMCConversionEvent);
};



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



class Draw3DThread : public wxThread
{
public:
	Draw3DThread(Worker *handler, const wchar_t *fname_);
	~Draw3DThread();

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

enum DoAfterConvertGcmc
{
	ConvertGcmcNothing,
	ConvertGcmcOpenFile,
	ConvertGcmcPasteFile,
	ConvertGcmc3DDraw
};


class GcmcProcess : public wxProcess
{
public:
	GcmcProcess(Worker *worker, const wchar_t *dstfn, DoAfterConvertGcmc todo);
	virtual void OnTerminate(int pid, int status) wxOVERRIDE;
	virtual bool HasInput();

private:
	DoAfterConvertGcmc what_to_do;
	std::wstring dst_file;
	Worker *m_worker;
};


class FilePage;
class LogWindow;

class Worker : public wxEvtHandler
{
	friend class CheckGCodeThread;
	friend class Draw3DThread;
	friend class GcmcProcess;
public:
	Worker(FilePage *fp);
	~Worker();
	void StopAll();
	bool IsRunning() { 	return (m_checkThread || m_simulateThread); 	}
	void  Check();
	void  Draw3D();
	int DoConvertGcmc(DoAfterConvertGcmc what_to_do);
	LogWindow *GetLogWnd();
	int RunGcmc(const wchar_t *src_fname, const  wchar_t *dst_fname, const wchar_t *args, DoAfterConvertGcmc what_to_do);

protected:
	//proccessing messages
	void OnCheckGCodeUpdate(wxThreadEvent &ev);
	void OnCheckGCodeCompletion(GCMCConversionEvent &ev);
	void OnDraw3DUpdate(wxThreadEvent &ev);
	void OnDraw3DCompletion(GCMCConversionEvent &ev);
	void OnTimer(wxTimerEvent &event);
private:
	void Do3DDraw(const wchar_t *fname);
	void AppendGcmcError(wxString &src);
	void GcmcProcessTerminated(int status, const wchar_t *dst_fname, DoAfterConvertGcmc what_to_do);
	bool CheckFileExist(const wchar_t *fname);
	void SendEvnToFrame(wxEventType commandType, const wchar_t *str,int i = - 1);
private:

	FilePage *m_fp;	
	wxCriticalSection m_critsect;
	CheckGCodeThread *m_checkThread;
	Draw3DThread *m_simulateThread;
	wxTimer m_timer;
	GcmcProcess *m_gcmcProcess;
	unsigned int m_gcmc_running_in_sec;

	wxDECLARE_EVENT_TABLE();
};


//wxDECLARE_EVENT(EVT_CHECK_GCODE_UPDATE, GCMCConversionEvent);
wxDECLARE_EVENT(EVT_CHECK_GCODE_COMPLETE, GCMCConversionEvent);
//wxDECLARE_EVENT(EVT_CHECK_SIMULATE_UPDATE, GCMCConversionEvent);
wxDECLARE_EVENT(EVT_CHECK_SIMULATE_COMPLETE, GCMCConversionEvent);


typedef void (wxEvtHandler::*GCMCFunction)(GCMCConversionEvent&);

#define GCMCEventHandler(func)  wxEVENT_HANDLER_CAST(GCMCFunction, func)

#define EVT_GCMC_CONVERSION(ex, fn) \
    wx__DECLARE_EVT1(ex, -1, GCMCEventHandler(fn))
