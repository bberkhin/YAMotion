#include "wx/wx.h"
#include "logwindow.h"
#include "defsext.h"
#include "prefs.h"

#define MARGIN_ITEM_HEIGHT 2

wxBEGIN_EVENT_TABLE(LogWindow, BaseLogClass)

EVT_LISTBOX(wxID_ANY, LogWindow::OnLboxSelect)
EVT_LISTBOX_DCLICK(wxID_ANY, LogWindow::OnLboxDClick)
EVT_SCROLL(LogWindow::OnScroll)
EVT_KEY_DOWN(LogWindow::OnKeyDown)

wxEND_EVENT_TABLE()

LogWindow::LogWindow(wxEvtHandler *_handler ) 
	: handler(_handler), BaseLogClass()
{

}

LogWindow::LogWindow(wxWindow *parent, wxEvtHandler *_handler, wxWindowID id )
	: handler(_handler) , BaseLogClass()
{
	m_vScrollBar = 0;
	m_hScrollBar = 0;
	m_height = -1;


	(void)Create(parent, id, wxDefaultPosition, wxDefaultSize, 0);

	SetClientDataType(wxClientData_Object);
	SetWindowStyle(GetWindowStyle() & (~(wxVSCROLL | wxHSCROLL)));
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	SetSelectionBackground(clrs->Get(ColourScheme::HIGHLIGHT));
	CalcSizes();

}

LogWindow::~LogWindow()
{
	Clear();
}

void LogWindow::SetVScrollBar(wxScrollBar *barv)
{
	m_vScrollBar = barv;
}

void LogWindow::SetHScrollBar(wxScrollBar *bar)
{
	m_hScrollBar = bar;
}

void LogWindow::OnScroll(wxScrollEvent& evt) 
{
	if ( evt.GetOrientation() == wxVERTICAL )
		this->DoScrollToUnit( evt.GetPosition() );
	//else
		//m_swx->DoHScroll(evt.GetEventType(), evt.GetPosition());	
}

void LogWindow::Append(MsgStatusLevel lvl, const wchar_t *str, int linen, bool update )
{
	wxString label;
	if (linen > 0)
	{
		label += ::wxString::Format(_("Line %d: "), linen);
	}
	switch (lvl)
	{
		case MSLError: label += _(" Error! "); break;
		case MSLWarning: label += _(" Warning! "); break;
	}
	label += str;	
	LogClientData *data = new LogClientData(linen, lvl);
	BaseLogClass::Append(label,data);
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
		BaseLogClass::SetScrollbar(orient, pos, thumbvisible, range, refresh);
}
void LogWindow::SetScrollPos(int orient, int pos, bool refresh)
{
	if (m_vScrollBar && orient != wxHORIZONTAL)
		m_vScrollBar->SetThumbPosition(pos);
	else if (m_hScrollBar && orient == wxHORIZONTAL)
		m_hScrollBar->SetThumbPosition(pos);
	else
		BaseLogClass::SetScrollPos(orient, pos,refresh);
}
int LogWindow::GetScrollPos(int orient) const
{
	if (m_vScrollBar && orient != wxHORIZONTAL)
		return m_vScrollBar->GetThumbPosition();
	else if (m_hScrollBar && orient == wxHORIZONTAL)
		return m_hScrollBar->GetThumbPosition();
	else
		return BaseLogClass::GetScrollPos(orient);
}
int LogWindow::GetScrollThumb(int orient) const
{
	if (m_vScrollBar && orient != wxHORIZONTAL)
		return m_vScrollBar->GetThumbSize();
	else if (m_hScrollBar && orient == wxHORIZONTAL)
		return m_hScrollBar->GetThumbSize();
	else
		return BaseLogClass::GetScrollThumb(orient);
}
int LogWindow::GetScrollRange(int orient) const
{
	if (m_vScrollBar && orient != wxHORIZONTAL)
		return m_vScrollBar->GetRange();
	else if (m_hScrollBar && orient == wxHORIZONTAL)
		return m_hScrollBar->GetRange();
	else
		return BaseLogClass::GetScrollRange(orient);
}
// scroll window to the specified position
void LogWindow::ScrollWindow(int dx, int dy, const wxRect* rect)
{
	BaseLogClass::ScrollWindow(dx, dy, rect);
}





void LogWindow::OnLboxSelect(wxCommandEvent& event)
{
	//BaseLogClass::Append(L"OnLboxSelect");
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
	LogClientData *data = dynamic_cast<LogClientData *>(GetClientObject(n));
	if (data == NULL || data->GetLine() <= 0 )
		return;

	LogClientData *dataCmd = data;// new IntClientData(data->GetData());
	wxCommandEvent *ev = new wxCommandEvent(wxEVT_MENU,ID_SELECTLINE);
	ev->SetClientObject(dataCmd);
	wxQueueEvent(handler, ev);
}


void LogWindow::Clear()
{
	wxItemContainer::Clear();
}


void LogWindow::DoClear()
{
	wxASSERT(m_items.GetCount() == m_clientData.GetCount());
	m_items.Clear();
	m_clientData.Clear();
	SetClientDataType(wxClientData_Object);
	UpdateCount();
}

void LogWindow::OnKeyDown(wxKeyEvent &event)
{
	if (event.GetKeyCode() == WXK_RETURN )
		DoSinchronize();	
	event.Skip();
}

void LogWindow::OnDrawItem(wxDC& dc, const wxRect& rect, size_t n) const
{

	wxVListBox::OnDrawBackground(dc, rect, n);
	
	wxString label = this->GetString(n);
	LogClientData *data = dynamic_cast<LogClientData *>(GetClientObject(n));
	//wxCoord w, h;
	//dc.GetTextExtent(label, &w, &h);

	//int x = rect.x ;
//	int y = rect.y + rect.height;
	
	ColourScheme::StdColour color_index;
	switch ( data->GetType() )
	{
		case MSLError:		color_index = ColourScheme::MSG_LOG_ERROR; break;
		case MSLInfo:		color_index = ColourScheme::MSG_LOG_INFO; break;
		case MSLWarning:	color_index = ColourScheme::MSG_LOG_WARNING; break;

		//case MSLFileStatus: color_index = MSG_LOG_FILESTATUS; break;
		//case MSLUndefened: label += L"#000000>"; break;

		default:
			color_index = ColourScheme::MSG_LOG_INFO; break;
	}

	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	dc.SetTextForeground(clrs->Get(color_index));
	dc.DrawLabel(label, rect, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

}


void LogWindow::CalcSizes()
{
	wxClientDC dc(this);
	wxFont font(GetFont());
	if (!font.IsOk())
		font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);

	int width, height;
	dc.SetFont(font);
	dc.GetMultiLineTextExtent(L"WhK1", &width, &height);
	m_height = height + 2 * MARGIN_ITEM_HEIGHT;
}

wxCoord LogWindow::OnMeasureItem(size_t n) const
{
	return m_height;
}


void LogWindow::DoDeleteOneItem(unsigned int n)
{
	m_items.RemoveAt(n);

	m_clientData.RemoveAt(n);

	UpdateCount();
}

int LogWindow::DoInsertItems(const wxArrayStringsAdapter& items,
	unsigned int pos,
	void **clientData,
	wxClientDataType type)
{
	const unsigned int count = items.GetCount();

	m_items.Insert(wxEmptyString, pos, count);
	m_clientData.Insert(NULL, pos, count);

	for (unsigned int i = 0; i < count; ++i, ++pos)
	{
		m_items[pos] = items[i];
		AssignNewItemClientData(pos, clientData, i, type);
	}

	UpdateCount();

	return pos - 1;
}

void LogWindow::SetString(unsigned int n, const wxString& s)
{
	wxCHECK_RET(IsValid(n),
		wxT("invalid index in LogWindow::SetString"));

	m_items[n] = s;
	RefreshRow(n);
}

wxString LogWindow::GetString(unsigned int n) const
{
	wxCHECK_MSG(IsValid(n), wxEmptyString,
		wxT("invalid index in LogWindow::GetString"));

	return m_items[n];
}

void LogWindow::UpdateCount()
{
	//wxASSERT(m_items.GetCount() == m_clientData.GetCount());
	wxVListBox::SetItemCount(m_items.GetCount());

	// very small optimization: if you need to add lot of items to
	// a wxSimpleHtmlListBox be sure to use the
	// wxSimpleHtmlListBox::Append(const wxArrayString&) method instead!
	if (!this->IsFrozen())
		RefreshAll();
}
