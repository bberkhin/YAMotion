#pragma once

#include "workingthreads.h"

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


class View3D;
class View3DPanel : public wxPanel
{
	wxDECLARE_ABSTRACT_CLASS(View3DPanel);
public:
	View3DPanel(wxWindow *parent);
	virtual ~View3DPanel();	
	void UpdateThemeColor();	
	View3D *Get3D() { return m_pview; }
	void UpdateStatistics(const ConvertGCMCInfo &dt);
protected:
	wxBoxSizer *CreateHeaderPanel();
	wxSizer *CreateFooterPanel();
	void SetValue(int id, const double &val);
private:
	View3D *m_pview;
	wxDECLARE_EVENT_TABLE();
};


class LogWindow;
class  LogPane : public wxPanel
{
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
	View3D *Get3D() { return m_view3d->Get3D(); }
	LogWindow *GetLogWnd() { return m_logwn->GetLogWnd(); }
	void Check();
	void Draw3D();
	void ConvertGcmc();
	void UpdateStatistics(const ConvertGCMCInfo &dt);
	
	void ShowLog(); 
	void HideLog();
	bool DoFileSave(bool askToSave, bool bSaveAs);
private:
	EditorPanel *m_editor;
	View3DPanel *m_view3d;
	LogPane *m_logwn;
	wxSplitterWindow *m_splitter;
	Worker *m_worker;

private:
	wxDECLARE_EVENT_TABLE();
};

