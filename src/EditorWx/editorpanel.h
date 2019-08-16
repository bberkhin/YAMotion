#pragma once

#include "workingthreads.h"
#include "flatsash.h"
#include "domath.h"
#include "logwindow.h"

class FilePage;
class Edit;

class EditorPanel : public wxPanel
{
	wxDECLARE_ABSTRACT_CLASS(EditorPanel);
public:
	EditorPanel(wxWindow *parent, FilePage *fp,int filetype, const wxString &filename, bool isnew);
	virtual ~EditorPanel();
	Edit *GetEdit() { return m_pedit; }
	void UpdateThemeColor();
	void OnTo3DButton(wxCommandEvent& ev);
	void OnToGcodeButton(wxCommandEvent& ev);
	void OnCheckButton(wxCommandEvent& ev);

protected:
	wxBoxSizer *CreateHeaderPanel();
private:
	Edit *m_pedit;
	FilePage *m_fp;
	wxDECLARE_EVENT_TABLE();
};

#define View3DPanelBase FlatSashWindow//wxSashWindow//wxPanel

class View3D;
class View3DPanel : public View3DPanelBase//wxSashWindow//wxPanel
{
	wxDECLARE_ABSTRACT_CLASS(View3DPanel);
public:
	View3DPanel(wxWindow *parent, FilePage *fb);
	virtual ~View3DPanel();	
	void UpdateThemeColor();	
	View3D *Get3D() { return m_pview; }
	void UpdateStatistics(const ConvertGCMCInfo &dt);
	void UpdateSimulationPos(int index, int dist, const TrackPointGL &pt);
	void OnSpeedChanged(wxScrollEvent& event);
protected:
	wxBoxSizer *CreateHeaderPanel();
	wxSizer *CreateFooterPanel();
	wxSizer *CreateSimulationPanel();
	wxString GetSpeedBtLabel();
	void SetValue(int id, const double &val, bool clear);
	void OnClose(wxCommandEvent& ev);
	void OnStandartView(wxCommandEvent& ev);
	void OnMenuView(wxCommandEvent& ev);
	void OnSimulateProgress(wxScrollEvent& event);
	void OnPauseSimulate(wxCommandEvent& event);
	void OnRunSimulate(wxCommandEvent& event);
	void OnStopSimulate(wxCommandEvent& event);
	void OnSetSimulateSpeed(wxCommandEvent& event);
	void OnTune3DView(wxCommandEvent& event);
	
	void OnIdle(wxIdleEvent& event);


private:
	View3D *m_pview;
	FilePage *m_fp;
	wxDECLARE_EVENT_TABLE();
};


class wxAnimationCtrl;

class  LogPane : public FlatSashWindow
{
	wxDECLARE_ABSTRACT_CLASS(LogPane);
public:
	LogPane(wxWindow *parent, FilePage *fb);
	~LogPane() { }
	void UpdateThemeColor();
	void OnClose(wxCommandEvent &ev);
	void StartPulse();
	void Pulse();
	void StopPulse();
	void Clear() { m_plog->Clear(); }
	void Append(MsgStatusLevel lvl, const wchar_t *str, int linen = 0, bool update = false)
			{ m_plog->Append(lvl, str,linen,update ); }

private:
	LogWindow *m_plog;
	FilePage *m_fb;
	wxAnimationCtrl  *m_workingAnim;
	wxDECLARE_EVENT_TABLE();
};



class wxSplitterWindow;
class Worker;

class FilePage : public wxPanel
{
	wxDECLARE_ABSTRACT_CLASS(FilePage);
public:
	FilePage(wxWindow *parent, int filetype, const wxString &filename, bool isnew);
	virtual ~FilePage();
	void UpdateThemeColor();
	Edit *GetEdit() { return m_editor->GetEdit(); }
	View3D *Get3D() { return m_view3d ? m_view3d->Get3D() : NULL; }
	LogPane *GetLogWnd() { return m_logwn; }// ? m_logwn->GetLogWnd() : NULL; }
	Worker * GetWorker() { return m_worker; }
	bool IsModified();
	void Check();
	void Draw3D();
	void ConvertGcmc();
	void ConvertGcmc(const wchar_t *src_fname, const  wchar_t *dst_fname, const wchar_t *args, bool addprologepilog);
	void UpdateStatistics(const ConvertGCMCInfo &dt);
	void UpdateSimulationPos(int index, int dist, const TrackPointGL &pt);
	void DoMathCalc(std::shared_ptr<DoMathBase> mth);

	wxString GetSavedFileName();
	bool DoFileSave(bool askToSave, bool bSaveAs);		

	void ShowLog(); 
	void HideLog();
	void Hide3D();
	void Show3D();

	void DoLayout(const wxSize &sz = wxDefaultSize, bool from3dview = false);
	void OnSize(wxSizeEvent& event);
	void OnSashDrag(wxSashEvent& event);
private:
	EditorPanel *m_editor;
	View3DPanel *m_view3d;
	LogPane *m_logwn;
//	wxSplitterWindow *m_splitter;
	Worker *m_worker;
	int m_view3dsize;
	int m_logwndsize;

private:
	wxDECLARE_EVENT_TABLE();
};

