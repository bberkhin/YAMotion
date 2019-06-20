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

class FlatScrollBar;
class LogWindow : public wxSimpleHtmlListBox
{
public:
	LogWindow(wxEvtHandler *_handler);
	LogWindow(wxWindow *parent, wxEvtHandler *_handler, wxWindowID id);
	~LogWindow();
	void Append(MsgStatusLevel lvl, const wchar_t *str, int linen = 0, bool update = false);
	void SetVScrollBar(wxScrollBar *bar);
	void SetHScrollBar(wxScrollBar *bar);

	void OnLboxSelect(wxCommandEvent& event);
	void OnLboxDClick(wxCommandEvent& event);
	void OnKeyDown(wxKeyEvent &event);
	void Clear();

	virtual bool CanScroll(int orient) const { return true; }
	// configure the window scrollbars
	virtual void SetScrollbar(int orient,	int pos,	int thumbvisible,	int range,	bool refresh = true) ;
	virtual void SetScrollPos(int orient, int pos, bool refresh = true);
	virtual int GetScrollPos(int orient) const ;
	virtual int GetScrollThumb(int orient) const;
	virtual int GetScrollRange(int orient) const;
	// scroll window to the specified position
	virtual void ScrollWindow(int dx, int dy,	const wxRect* rect = NULL);


	
private:
	void DoSinchronize();
	void RemoveScrollbar();
private:
	wxScrollBar *m_vScrollBar;
	wxScrollBar *m_hScrollBar;
	wxEvtHandler *handler;
	wxDECLARE_EVENT_TABLE();
};

