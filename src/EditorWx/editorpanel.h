#pragma once

#include "workingthreads.h"
#include "flatsash.h"

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
	
	void OnIdle(wxIdleEvent& event);


private:
	View3D *m_pview;
	FilePage *m_fp;
	wxDECLARE_EVENT_TABLE();
};


class LogWindow;
class  LogPane : public FlatSashWindow
{
	wxDECLARE_ABSTRACT_CLASS(LogPane);
public:
	LogPane(wxWindow *parent, FilePage *fb);
	~LogPane() { }
	void UpdateThemeColor();
	void OnClose(wxCommandEvent &ev);
	LogWindow *GetLogWnd() {	return m_plog;	}
private:
	LogWindow *m_plog;
	FilePage *m_fb;
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
	LogWindow *GetLogWnd() { return m_logwn ? m_logwn->GetLogWnd() : NULL; }
	Worker * GetWorker() { return m_worker; }
	void Check();
	void Draw3D();
	void ConvertGcmc();
	void ConvertGcmc(const wchar_t *src_fname, const  wchar_t *dst_fname, const wchar_t *args);
	void UpdateStatistics(const ConvertGCMCInfo &dt);
	void UpdateSimulationPos(int index, int dist, const TrackPointGL &pt);

	wxString GetSavedFileName();
	bool DoFileSave(bool askToSave, bool bSaveAs);		

	void ShowLog(); 
	void HideLog();
	void Hide3D();
	void Show3D();

	void DoLayout(const wxSize &sz = wxDefaultSize);
	void OnSize(wxSizeEvent& event);
	void OnSashDrag(wxSashEvent& event);
private:	
	EditorPanel *m_editor;
	View3DPanel *m_view3d;
	LogPane *m_logwn;
//	wxSplitterWindow *m_splitter;
	Worker *m_worker;
	int m_view3dsize;
	int m_splashpos;

private:
	wxDECLARE_EVENT_TABLE();
};

