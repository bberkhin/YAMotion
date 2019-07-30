#pragma once
#include "wx/filename.h"

class WelcomeWnd : public wxPanel
{
	wxDECLARE_ABSTRACT_CLASS(WelcomeWnd);
public:
	WelcomeWnd(wxWindow *parent);
	virtual ~WelcomeWnd();
	void OnSize(wxSizeEvent& event);
	void AddLastFilesToMenu(bool update = true);
	
private:
	wxBoxSizer *CreateRecentFilesList();
	wxBoxSizer *CreateFooter();
	wxBoxSizer *CreateCommand();
	wxBoxSizer *CreateDoc();
	void UpdateThemeColor();
	void AddColumnHeader(wxBoxSizer *pane, const wxString &text);
	void AddCommand(wxBoxSizer *pane, const wxString &text, int cmd, bool right = false);
	void AddRecentFile(wxBoxSizer *pane, const wxFileName &p, int n); 
	void AddHelpLink(wxBoxSizer *pane, const wxString &text, int cmd);

private:
	wxColor m_bgColor; //clrs->Get(ColourScheme::WINDOW);
	wxColor m_bghColor; 
	wxColor m_fgColor; //clrs->Get(ColourScheme::WINDOW_TEXT);
	wxColor m_fghColor;
	wxBoxSizer *m_LastFiles;

	wxDECLARE_EVENT_TABLE();
};

