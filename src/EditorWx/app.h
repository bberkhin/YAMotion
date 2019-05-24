#pragma once
#include "ienvironment.h"

class AppFrame;

//----------------------------------------------------------------------------
//
class App : public wxApp
{
	friend class AppFrame;
public:
	App() : m_restart(false) { }
	~App();
	

	//! the main function called during application start
	virtual bool OnInit() wxOVERRIDE;

	//! application exit function
	virtual int OnExit() wxOVERRIDE;
	void Restart();
	bool GetUptadeInfo(wxString &out);
	IEnvironment *GetEnvironment() { return env.get(); }
	virtual void OnEventLoopEnter(wxEventLoopBase* WXUNUSED(loop)) wxOVERRIDE;

	// create the file system watcher here, because it needs an active loop
	
private:
	//! frame window
	AppFrame *m_frame;

protected:
	// Lang support
	wxLocale m_locale;  // locale we'll be using
	bool m_restart;
	// envaroment
	std::shared_ptr<IEnvironment> env;
	wxDECLARE_EVENT_TABLE();
};

// created dynamically by wxWidgets
wxDECLARE_APP(App);


extern const wxString g_langNames[];
extern const wxLanguage g_langIds[];
extern const int g_lang_count;
