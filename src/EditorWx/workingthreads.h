#pragma once

#include "environmentsimple.h"
#include "executorlog.h"
#include "ExecutorView.h"
#include "GCodeInterpreter.h"
#include <wx/thread.h>
#include <wx/process.h>
#include "wx/event.h"
#include "View3D.h"

struct ConvertGCMCInfo
{
	double feed_len;
	double traverce_len;
	CoordsBox box;
	bool runsimulaion;
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
	Draw3DThread(Worker *handler, const wchar_t *fname_, bool runsimulation);
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
	bool m_runsimulation;
	//View3D *m_3Dview;
};

class SimulateThreadEvent : public wxThreadEvent
{
public:
	SimulateThreadEvent(wxEventType command_type = -1) : wxThreadEvent(command_type) {	}
	SimulateThreadEvent(int tillIndex_, TrackPointGL &end_point_, wxEventType command_type = -1) :
		tillindex(tillIndex_), end_point(end_point_), wxThreadEvent(command_type)	{	}
	SimulateThreadEvent(const SimulateThreadEvent &e) : wxThreadEvent(e)
	{
		tillindex = e.get_index();
		end_point = e.get_end_point();
	}
	~SimulateThreadEvent()
	{
	}
	wxThreadEvent *Clone() { return new SimulateThreadEvent(*this); }
	int get_index() const { return tillindex; }
	const TrackPointGL &get_end_point() const { return end_point; }
private:
	int tillindex;
	TrackPointGL end_point;
private:
	wxDECLARE_DYNAMIC_CLASS_NO_ASSIGN(GCMCConversionEvent);
};


class SimulateCutting : public wxThread
{
public:
	SimulateCutting(Worker *handler)
		: m_worker(handler), wxThread(wxTHREAD_DETACHED)
	{

	}
	~SimulateCutting();
protected:
	virtual wxThread::ExitCode Entry();
	Worker *m_worker;
};


enum DoAfterConvertGcmc
{
	ConvertGcmcNothing,
	ConvertGcmcOpenFile,
	ConvertGcmcPasteFile,
	ConvertGcmc3DDraw,
	ConvertGcmc3DDrawAndSimulate
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
	friend class SimulateCutting;
public:
	Worker(FilePage *fp);
	~Worker();
	void StopAll();
	bool IsRunning() { 	return (m_checkThread || m_drawThread); 	}
	void  Check();
	void  Draw3D( bool runsimulation );
	int DoConvertGcmc(DoAfterConvertGcmc what_to_do);
	LogWindow *GetLogWnd();
	int RunGcmc(const wchar_t *src_fname, const  wchar_t *dst_fname, const wchar_t *args, DoAfterConvertGcmc what_to_do);
	void SemulateStart();
	void SemulatePause();
	void SemulateStop();
	bool CanSimulateStart();
	bool CanSimulateStop();
	bool CanSimulatePaused();
	int  SetSimulationPos(int percent);
	int  SetSimulationSpeed(int percent);


protected:
	//proccessing messages
	void OnCheckGCodeUpdate(wxThreadEvent &ev);
	void OnCheckGCodeCompletion(GCMCConversionEvent &ev);
	void OnDraw3DUpdate(wxThreadEvent &ev);
	void OnDraw3DCompletion(GCMCConversionEvent &ev);
	void OnSimulateUpdate(SimulateThreadEvent &ev);
	void OnSimulateCompletion(SimulateThreadEvent &ev);

	void OnTimer(wxTimerEvent &event);


private:
	void Do3DDraw(const wchar_t *fname, bool runsimulation);
	void AppendGcmcError(wxString &src);
	void GcmcProcessTerminated(int status, const wchar_t *dst_fname, DoAfterConvertGcmc what_to_do);
	bool CheckFileExist(const wchar_t *fname);
	void SendEvnToFrame(wxEventType commandType, const wchar_t *str,int i = - 1);
private:

	FilePage *m_fp;	
	wxCriticalSection m_critsect;
	CheckGCodeThread *m_checkThread;
	Draw3DThread *m_drawThread;
	SimulateCutting *m_simulateThread;
	wxTimer m_timer;
	GcmcProcess *m_gcmcProcess;
	unsigned int m_gcmc_running_in_sec;

	wxDECLARE_EVENT_TABLE();
};


wxDECLARE_EVENT(EVT_CHECK_GCODE_COMPLETE, GCMCConversionEvent);
wxDECLARE_EVENT(EVT_DRAW_GCODE_COMPLETE, GCMCConversionEvent);
wxDECLARE_EVENT(EVT_SIMULATE_UPDATE, SimulateThreadEvent);
wxDECLARE_EVENT(EVT_SIMULATE_COMPLETE, SimulateThreadEvent);

typedef void (wxEvtHandler::*GCMCFunction)(GCMCConversionEvent&);

#define GCMCEventHandler(func)  wxEVENT_HANDLER_CAST(GCMCFunction, func)

#define EVT_GCMC_CONVERSION(ex, fn) \
    wx__DECLARE_EVT1(ex, -1, GCMCEventHandler(fn))



typedef void (wxEvtHandler::*SimulateEvntFunction)(SimulateThreadEvent&);
#define SimulateEventHandler(func)  wxEVENT_HANDLER_CAST(SimulateEvntFunction, func)

#define EVT_SIMULATION(ex, fn) \
    wx__DECLARE_EVT1(ex, -1, SimulateEventHandler(fn))


