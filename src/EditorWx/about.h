#pragma once

// ----------------------------------------------------------------------------
//! about box of the application APP_VENDOR-APP_NAME


class AppAbout : public wxDialog {

public:
	//! constructor
	AppAbout(wxWindow *parent,
		int milliseconds = 0,
		long style = 0);

	//! destructor
	~AppAbout();

	// event handlers
	void OnTimerEvent(wxTimerEvent &event);
	void UpdateThemeColor();

private:
	// timer
	wxTimer *m_timer;

	wxDECLARE_EVENT_TABLE();
};
