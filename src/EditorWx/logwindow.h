#pragma once
#include "wx/htmllbox.h"
#include "ilogger.h"


enum MsgStatusLevel
{
	MSLUndefened = 0,
	MSLWarning = LOG_WARNING,
	MSLError = LOG_ERROR,
	MSLInfo = LOG_INFORMATION,
	MSLFileStatus = LOG_INFORMATIONSUM
	
};

class LogWindow : public wxSimpleHtmlListBox
{
public:
	LogWindow(wxEvtHandler *_handler);
	LogWindow(wxWindow *parent, wxEvtHandler *_handler, wxWindowID id);
	~LogWindow();
	void Append(MsgStatusLevel lvl, const wchar_t *str, int linen = 0, bool update = false);

	void OnLboxSelect(wxCommandEvent& event);
	void OnLboxDClick(wxCommandEvent& event);
	void OnKeyDown(wxKeyEvent &event);
	void Clear();
private:
	void DoSinchronize();
private:
	wxEvtHandler *handler;
	wxDECLARE_EVENT_TABLE();
};

