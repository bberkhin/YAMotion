#pragma once
#include <wx\html\htmlwin.h>

//class WelcomProcessor;

class WelcomeWndHtml : 	public wxHtmlWindow
{

public:
	WelcomeWndHtml(wxWindow *parent); 
	~WelcomeWndHtml();
	void OnHtmlLinkClicked(wxHtmlLinkEvent &event);
	void ShowWelcome(bool bShow);
	void SetHomePage();
	void OnSize(wxSizeEvent& event);
	//void OnEraseBgEvent(wxEraseEvent& event);
public:
	void RunCommand(const wxString &url, int baseCmd);
	void UpdateFooter();
private:
	wxDECLARE_EVENT_TABLE();
	wxDECLARE_NO_COPY_CLASS(WelcomeWndHtml);
private:
	//WelcomProcessor *processor;
	wxFrame *pWelcomeFrame;
};

class WelcomeWnd : public wxPanel
{
	wxDECLARE_ABSTRACT_CLASS(WelcomeWnd);
public:
	WelcomeWnd(wxWindow *parent);
	virtual ~WelcomeWnd();
	void OnHtmlLinkClicked(wxHtmlLinkEvent &event);
	void OnSize(wxSizeEvent& event);
	
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

	wxDECLARE_EVENT_TABLE();
};

