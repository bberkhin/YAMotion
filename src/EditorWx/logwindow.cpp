#include "wx/wx.h"
#include "logwindow.h"
#include "defsext.h"


wxBEGIN_EVENT_TABLE(LogWindow, wxSimpleHtmlListBox)

EVT_LISTBOX(wxID_ANY, LogWindow::OnLboxSelect)
EVT_LISTBOX_DCLICK(wxID_ANY, LogWindow::OnLboxDClick)
EVT_KEY_DOWN(LogWindow::OnKeyDown)

wxEND_EVENT_TABLE()

LogWindow::LogWindow(wxEvtHandler *_handler ) 
	: handler(_handler), wxSimpleHtmlListBox()
{

}

LogWindow::LogWindow(wxWindow *parent, wxEvtHandler *_handler, wxWindowID id )
	: handler(_handler) , wxSimpleHtmlListBox(parent, id, wxDefaultPosition, wxDefaultSize,
		0, NULL, 0)
{
	m_vScrollBar = 0;
	SetClientDataType(wxClientData_Object);
	SetWindowStyle( GetWindowStyle() & (~(wxVSCROLL | wxHSCROLL)));
}


LogWindow::~LogWindow()
{
}

void LogWindow::SetVScrollBar(wxScrollBar *barv)
{
	m_vScrollBar = barv;
}

void LogWindow::SetHScrollBar(wxScrollBar *bar)
{
	m_hScrollBar = bar;
}


void LogWindow::Append(MsgStatusLevel lvl, const wchar_t *str, int linen, bool update )
{
	wxString label = L"<font color=";
	switch (lvl)
	{
		case MSLError: label += _("#880000> Error! "); break;
		case MSLFileStatus: label += L"#008888>"; break;
		case MSLInfo: label += L"#008800>"; break;
		case MSLUndefened: label += L"#000000>"; break;
		case MSLWarning: label += _("#000088>Warning! "); break;	
	}
	if (linen > 0)
	{
		label += ::wxString::Format(_("Line %d: "), linen);
	}
	label += str;
	label += L"</font>";
	IntClientData *data = new IntClientData(linen);
	wxSimpleHtmlListBox::Append(label,data);
	if (update)
		Update();
}



void LogWindow::SetScrollbar(int orient, int pos, int thumbvisible, int range, bool refresh)
{
	if (m_vScrollBar && orient != wxHORIZONTAL)
		m_vScrollBar->SetScrollbar(pos, thumbvisible, range, thumbvisible, refresh);
	else if (m_hScrollBar && orient == wxHORIZONTAL)
		m_hScrollBar->SetScrollbar(pos, thumbvisible, range, thumbvisible, refresh);
	else
		wxSimpleHtmlListBox::SetScrollbar(orient, pos, thumbvisible, range, refresh);
}
void LogWindow::SetScrollPos(int orient, int pos, bool refresh)
{
	if (m_vScrollBar && orient != wxHORIZONTAL)
		m_vScrollBar->SetThumbPosition(pos);
	else if (m_hScrollBar && orient == wxHORIZONTAL)
		m_hScrollBar->SetThumbPosition(pos);
	else
		wxSimpleHtmlListBox::SetScrollPos(orient, pos,refresh);
}
int LogWindow::GetScrollPos(int orient) const
{
	if (m_vScrollBar && orient != wxHORIZONTAL)
		return m_vScrollBar->GetThumbPosition();
	else if (m_hScrollBar && orient == wxHORIZONTAL)
		return m_hScrollBar->GetThumbPosition();
	else
		return wxSimpleHtmlListBox::GetScrollPos(orient);
}
int LogWindow::GetScrollThumb(int orient) const
{
	if (m_vScrollBar && orient != wxHORIZONTAL)
		return m_vScrollBar->GetThumbSize();
	else if (m_hScrollBar && orient == wxHORIZONTAL)
		return m_hScrollBar->GetThumbSize();
	else
		return wxSimpleHtmlListBox::GetScrollThumb(orient);
}
int LogWindow::GetScrollRange(int orient) const
{
	if (m_vScrollBar && orient != wxHORIZONTAL)
		return m_vScrollBar->GetRange();
	else if (m_hScrollBar && orient == wxHORIZONTAL)
		return m_hScrollBar->GetRange();
	else
		return wxSimpleHtmlListBox::GetScrollRange(orient);
}
// scroll window to the specified position
void LogWindow::ScrollWindow(int dx, int dy, const wxRect* rect)
{
	wxSimpleHtmlListBox::ScrollWindow(dx, dy, rect);
}





void LogWindow::OnLboxSelect(wxCommandEvent& event)
{
	//wxSimpleHtmlListBox::Append(L"OnLboxSelect");
}

void LogWindow::OnLboxDClick(wxCommandEvent& event)
{
	DoSinchronize();
}

void LogWindow::DoSinchronize()
{
	//Move to indows line
	int n = GetSelection();
	if (n < 0 || n >= (int)GetCount())
		return;
	IntClientData *data = dynamic_cast<IntClientData *>(GetClientObject(n));
	if (data == NULL || data->GetData() <= 0 )
		return;

	IntClientData *dataCmd = data;// new IntClientData(data->GetData());
	wxCommandEvent *ev = new wxCommandEvent(wxEVT_MENU,ID_SELECTLINE);
	ev->SetClientObject(dataCmd);
	wxQueueEvent(handler, ev);
}

void LogWindow::Clear()
{
	wxItemContainer::Clear();
	SetClientDataType(wxClientData_Object);
}


void LogWindow::OnKeyDown(wxKeyEvent &event)
{
	if (event.GetKeyCode() == WXK_RETURN )
		DoSinchronize();	
	event.Skip();
}