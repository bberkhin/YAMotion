#pragma once
#include "edit.h"    

class EditorPanel : 	public wxPanel
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

