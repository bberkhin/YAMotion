#pragma once
#include "edit.h"    

class EditorPanel : public wxPanel
{
	wxDECLARE_ABSTRACT_CLASS(EditorPanel);
public:
	EditorPanel(wxWindow *parent, int filetype, const wxString &filename, bool isnew);
	virtual ~EditorPanel();
	Edit *GetEdit() { return m_pedit; }
	void UpdateThemeColor();
	void OnTo3DButton(wxCommandEvent& ev);
	void OnToGcodeButton(wxCommandEvent& ev);

protected:
	wxBoxSizer *CreateHeaderPanel();
private:
	Edit *m_pedit;
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
protected:
	wxBoxSizer *CreateHeaderPanel();
	wxSizer *CreateFooterPanel();
private:
	View3D *m_pview;
	wxDECLARE_EVENT_TABLE();
};


class FilePage : public wxPanel
{
	wxDECLARE_ABSTRACT_CLASS(FilePage);
public:
	FilePage(wxWindow *parent, int filetype, const wxString &filename, bool isnew);
	virtual ~FilePage();
	void UpdateThemeColor();
	Edit *GetEdit() { return m_editor->GetEdit(); }
	View3D *Get3D() { return m_view3d->Get3D(); }
	
private:
	EditorPanel *m_editor;
	View3DPanel *m_view3d;
private:
	wxDECLARE_EVENT_TABLE();
};
