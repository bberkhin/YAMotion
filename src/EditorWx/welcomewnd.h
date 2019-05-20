#pragma once
#include <wx\html\htmlwin.h>

//class WelcomProcessor;

class WelcomeWnd : 	public wxHtmlWindow
{

public:
	WelcomeWnd(wxWindow *parent); 
	~WelcomeWnd();
	void OnHtmlLinkClicked(wxHtmlLinkEvent &event);
	void ShowWelcome(bool bShow);
	void SetHomePage();
	//void OnEraseBgEvent(wxEraseEvent& event);
public:
	void RunCommand(const wxString &url, int baseCmd);
private:
	wxDECLARE_EVENT_TABLE();
	wxDECLARE_NO_COPY_CLASS(WelcomeWnd);
private:
	//WelcomProcessor *processor;
	wxFrame *pWelcomeFrame;
};

