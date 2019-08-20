#pragma once

#include "environmentsimple.h"
#include "executorlog.h"
#include "ExecutorView.h"
#include "GCodeInterpreter.h"
#include <wx/thread.h>
#include <wx/process.h>
#include "wx/event.h"
#include "wx/filename.h"
#include "View3D.h"
#include "domath.h"

struct ConvertGCMCInfo
{
	double feed_len;
	double traverce_len;
	CoordsBox box;
	bool runsimulaion;
	int num_errors;
	int exit_code;
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
	wxFileName fname;
};



class Draw3DThread : public wxThread
{
public:
	Draw3DThread(Worker *handler, const wchar_t *fname_, bool runsimulation);
	~Draw3DThread();

	TrackPoints &getTack() { return pexec->getTrack(); }
	CoordsBox getBox() { return pexec->getBox(); }

	void Update3DView();
	
protected:
	virtual wxThread::ExitCode Entry();
	Worker *m_worker;
	LoggerWnd *plogger;
	ExecutorView *pexec;
	GCodeInterpreter *ppret;
	wxFileName fname;
	bool m_runsimulation;
	bool isOk;
	//View3D *m_3Dview;
};

class SimulateThreadEvent : public wxThreadEvent
{
public:
	SimulateThreadEvent(wxEventType command_type = -1) : tilldistance(-1), tillindex(-1), wxThreadEvent(command_type) {	}
	SimulateThreadEvent(int tillindex_, int tilldistance_, TrackPointGL &end_point_, wxEventType command_type = -1) :
		tillindex(tillindex_),tilldistance(tilldistance_), end_point(end_point_), wxThreadEvent(command_type)	{	}
	SimulateThreadEvent(const SimulateThreadEvent &e) : wxThreadEvent(e)
	{
		tillindex = e.get_index();
		tilldistance = e.get_distance();
		end_point = e.get_end_point();
	}
	~SimulateThreadEvent()
	{
	}
	wxThreadEvent *Clone() { return new SimulateThreadEvent(*this); }
	int get_index() const { return tillindex; }
	int get_distance() const { return tilldistance; }
	const TrackPointGL &get_end_point() const { return end_point; }
private:
	int tillindex;
	int tilldistance;
	TrackPointGL end_point;
private:
	wxDECLARE_DYNAMIC_CLASS_NO_ASSIGN(GCMCConversionEvent);
};


class SimulateCutting : public wxThread
{
public:
	SimulateCutting(Worker *handler, int speed)
		: m_worker(handler), m_speedk(speed), wxThread(wxTHREAD_DETACHED)
	{

	}
	~SimulateCutting();	
	void SetSeedK(int speed) { m_speedk = speed; }
protected:
	virtual wxThread::ExitCode Entry();
	int m_speedk;
	Worker *m_worker;
};

class Edit;
class MathTransform : public wxThread
{
public:
	MathTransform(Worker *worker, Edit *edit, std::shared_ptr<DoMathBase> mth);
	~MathTransform();
protected:
	virtual wxThread::ExitCode Entry();
	Worker *m_worker;
	std::shared_ptr<DoMathBase> m_mth;
	Edit *m_edit;
	LoggerWnd *plogger;
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
	~GcmcProcess();
	virtual void OnTerminate(int pid, int status) wxOVERRIDE;
	virtual bool HasInput();

private:
	DoAfterConvertGcmc what_to_do;
	std::wstring dst_file;
	Worker *m_worker;
};




class FilePage;
class LogPane;

class Worker : public wxEvtHandler
{
	friend class CheckGCodeThread;
	friend class Draw3DThread;
	friend class GcmcProcess;
	friend class SimulateCutting;
	friend class MathTransform;
public:
	Worker(FilePage *fp);
	~Worker();
	void StopAll();
	bool IsRunning() { 	return (m_checkThread || m_drawThread || m_mathThread ); }
	void  Check();
	void  Draw3D( bool runsimulation );
	int DoConvertGcmc(DoAfterConvertGcmc what_to_do);
	LogPane *GetLogWnd();
	int RunGcmc(const wchar_t *src_fname, const  wchar_t *dst_fname, const wchar_t *args, DoAfterConvertGcmc what_to_do, bool addprologepilog = true);
	void SemulateStart();
	void SemulatePause();
	void SemulateStop();
	bool CanSimulateStart();
	bool CanSimulateStop();
	bool CanSimulatePaused();
	void SetSimulationPos(int percent);
	void SetSimulationSpeed(int times );
	int GetSimulationSpeed() {	return m_speedk;}
	void RunMath(std::shared_ptr<DoMathBase> mth);

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
	MathTransform *m_mathThread;
	wxTimer m_timer;
	GcmcProcess *m_gcmcProcess;
	unsigned int m_gcmc_running_in_sec;
	int m_speedk; // simuleation speed koefficient
	

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


