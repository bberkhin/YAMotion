#include "wx/wx.h"
#include "prefs.h"
#include "FlatScrollBar.h"

// scroll the bar
#define wxACTION_SCROLL_START       wxT("start")     // to the beginning
#define wxACTION_SCROLL_END         wxT("end")       // to the end
#define wxACTION_SCROLL_LINE_UP     wxT("lineup")    // one line up/left
#define wxACTION_SCROLL_PAGE_UP     wxT("pageup")    // one page up/left
#define wxACTION_SCROLL_LINE_DOWN   wxT("linedown")  // one line down/right
#define wxACTION_SCROLL_PAGE_DOWN   wxT("pagedown")  // one page down/right
#define wxACTION_SCROLL_THUMB_DRAG      wxT("thumbdrag")
#define wxACTION_SCROLL_THUMB_MOVE      wxT("thumbmove")
#define wxACTION_SCROLL_THUMB_RELEASE   wxT("thumbrelease")

#define TUMB_SIZE 10
#define DRAW_TUMB_SIZE 6
#define DEFLATE_TUMB_TODRAW 2// ((TUMB_SIZE-DRAW_TUMB_SIZE)/2)



FlatScrollBar::FlatScrollBar(wxWindow *parent, wxEvtHandler *handler, int id,  int type)
	: m_handler(handler), m_status(statusNone),m_type(type),
	wxScrollBar()
{
	m_pageSize = 0;
	m_thumbPos = 0;
	m_range = 0;
	m_thumbSize = 0;
	m_thumbPosOld = 0;
	m_dirty = false;
	m_htLast = -1;
	m_ofsMouse = -1;
	m_capture = false;

	SetBestClientSize();
	wxWindow::Create(parent, id);
	if (IsVertical())
		SetWindowStyle(GetWindowStyle() | wxVERTICAL);

}


FlatScrollBar::~FlatScrollBar()
{
}

BEGIN_EVENT_TABLE(FlatScrollBar, wxWindow)
	EVT_MOTION(FlatScrollBar::mouseMoved)
	EVT_LEFT_DOWN(FlatScrollBar::mouseDown)
	EVT_LEFT_UP(FlatScrollBar::mouseReleased)
	EVT_RIGHT_DOWN(FlatScrollBar::rightClick)
	EVT_ENTER_WINDOW(FlatScrollBar::mouseEnterWindow)
	EVT_LEAVE_WINDOW(FlatScrollBar::mouseLeftWindow)
	EVT_MOUSEWHEEL(FlatScrollBar::mouseWheelMoved)
	// catch paint events
	EVT_PAINT(FlatScrollBar::paintEvent)
END_EVENT_TABLE()


bool FlatScrollBar::IsStandalone() const
{	
	wxWindow *parent = dynamic_cast<wxWindow *>(m_handler);
	if (!parent)
	{
		return true;
	}
	return true;
	//return ( (parent->GetWindowStyleFlag()&wxHSCROLL) && (parent->GetWindowStyleFlag()&wxVSCROLL) );
}


void FlatScrollBar::paintEvent(wxPaintEvent & evt)
{
	// depending on your system you may need to look at double-buffered dcs
	wxPaintDC dc(this);
	render(dc);
}

void FlatScrollBar::paintNow()
{
	// depending on your system you may need to look at double-buffered dcs
	wxClientDC dc(this);
	render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void FlatScrollBar::render(wxDC&  dc)
{
	wxRect rc = GetClientRect();
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	wxColor clr;
	//Draw background
	dc.SetBrush(wxBrush(clrs->Get(ColourScheme::SCROLLBAR)));
	dc.SetPen(*wxTRANSPARENT_PEN);
	dc.DrawRectangle(rc);
	//Draw Tumb

	wxRect rcTumb = GetScrollbarRect();
	if (IsVertical())
		rcTumb.Deflate(DEFLATE_TUMB_TODRAW, 0); 
	else
		rcTumb.Deflate(0, DEFLATE_TUMB_TODRAW);
		


	if (m_status == statusHover)
		clr = clrs->Get(ColourScheme::ColourScheme::SCROLLBAR_TUMB_HOVER);
	else if (m_status == statusPressed)
		clr = clrs->Get(ColourScheme::SCROLLBAR_TUMB_HOVER);
	else
		clr = clrs->Get(ColourScheme::SCROLLBAR_TUMB);

	dc.SetBrush(wxBrush(clr));
	dc.DrawRoundedRectangle(rcTumb,3);
}

wxCoord FlatScrollBar::GetMouseCoord( const wxMouseEvent& event) const
{
	wxPoint pt = event.GetPosition();
	return IsVertical() ? pt.y : pt.x;
}

void FlatScrollBar::mouseDown(wxMouseEvent& event)
{
	CaptureMouse();
	m_capture = true;
	int ht = HitTestBar( event.GetPosition() );
	 
	if (ht == Element_Thumb)
	{
		m_ofsMouse = GetMouseCoord(event) - ScrollbarToPixel();
	}
	else if (ht == Element_Bar_1)  //UP
	{
		PerformAction(wxACTION_SCROLL_PAGE_UP);

	}
	else if (ht == Element_Bar_2) //Dawn
	{
		PerformAction(wxACTION_SCROLL_PAGE_DOWN);
	}

	m_htLast = ht;
	
	m_status = statusPressed;
	paintNow();
}

void FlatScrollBar::mouseReleased(wxMouseEvent& event) 
{
	m_status = statusNone;
	if (m_capture)
	{
		ReleaseMouse();
		m_capture = false;
	}
	paintNow();
}


void FlatScrollBar::mouseMoved(wxMouseEvent& event) 
{
	if (m_status == statusPressed)
	{
		if (m_htLast == Element_Thumb)
		{
			int thumbPos = GetMouseCoord(event) - m_ofsMouse;
			thumbPos = PixelToScrollbar(thumbPos);
			PerformAction(wxACTION_SCROLL_THUMB_MOVE, thumbPos);
		}
		return;
	}
	
	int ht = HitTestBar(event.GetPosition());
	int newstatus = statusNone;
	if (ht == Element_Thumb)
		newstatus = statusHover;

	if (newstatus != m_status )
	{
		m_status = newstatus;
		paintNow();
	}
}


// currently unused events

void FlatScrollBar::mouseLeftWindow(wxMouseEvent& event) 
{
	if (m_status == statusPressed)
		return;
	m_status = statusNone;
	paintNow();
}

void FlatScrollBar::mouseEnterWindow(wxMouseEvent& event) 
{
	mouseMoved(event);
}
void FlatScrollBar::mouseWheelMoved(wxMouseEvent& event) {}
void FlatScrollBar::rightClick(wxMouseEvent& event) {}


void FlatScrollBar::SetBestClientSize()
{
	if( IsVertical() )
		SetMinSize(FromDIP(wxSize(TUMB_SIZE, 100)));
	else
		SetMinSize(FromDIP(wxSize(100, TUMB_SIZE)));
}



static void GetScrollBarThumbSize(wxCoord length,
	int thumbPos,
	int thumbSize,
	int range,
	wxCoord *thumbStart,
	wxCoord *thumbEnd)
{
	// the thumb can't be made less than this number of pixels
	static const wxCoord thumbMinWidth = 8; // FIXME: should be configurable

	*thumbStart = (length*thumbPos) / range;
	*thumbEnd = (length*(thumbPos + thumbSize)) / range;

	if (*thumbEnd - *thumbStart < thumbMinWidth)
	{
		// adjust the end if possible
		if (*thumbStart <= length - thumbMinWidth)
		{
			// yes, just make it wider
			*thumbEnd = *thumbStart + thumbMinWidth;
		}
		else // it is at the bottom of the scrollbar
		{
			// so move it a bit up
			*thumbStart = length - thumbMinWidth;
			*thumbEnd = length;
		}
	}
}


wxRect  FlatScrollBar::GetScrollbarRect( int elem, int thumbPos )
{
	if (thumbPos == -1)
	{
		thumbPos = GetThumbPosition();
	}
	
	wxSize sizeArrow(0, 0);
	wxSize sizeTotal = GetClientSize();
	wxCoord *start, *width;
	wxCoord length, arrow;
	wxRect rect;
	if ( IsVertical() )
	{
		rect.x = 0;
		rect.width = sizeTotal.x;
		length = sizeTotal.y;
		start = &rect.y;
		width = &rect.height;
		arrow = sizeArrow.y;
	}
	else // horizontal
	{
		rect.y = 0;
		rect.height = sizeTotal.y;
		length = sizeTotal.x;
		start = &rect.x;
		width = &rect.width;
		arrow = sizeArrow.x;
	}

	length -= 2 * arrow;
	wxCoord thumbStart, thumbEnd;
	int range = GetRange();
	if (!range)
	{
		thumbStart  = thumbEnd = 0;
	}
	else
	{
		GetScrollBarThumbSize(length,
			thumbPos,
			GetThumbSize(),
			range,
			&thumbStart,
			&thumbEnd);
	}

	if (elem == Element_Thumb)
	{
		*start = thumbStart;
		*width = thumbEnd - thumbStart;
	}
	else if (elem == Element_Bar_1)
	{
		*start = 0;
		*width = thumbStart;
	}
	else // elem == wxScrollBar::Element_Bar_2
	{
		*start = thumbEnd;
		*width = length - thumbEnd;
	}

	// everything is relative to the start of the shaft so far
	*start += arrow;
	return rect;
}


int  FlatScrollBar::HitTestBar(const wxPoint& pt)
{
	// we only need to work with either x or y coord depending on the
	// orientation, choose one (but still check the other one to verify if the
	// mouse is in the window at all)
	const wxSize sizeArrowSB(0,0);

	wxCoord coord, sizeArrow, sizeTotal;
	wxSize size = GetSize();
	if ( IsVertical() )
	{
		if (pt.x < 0 || pt.x > size.x)
			return Element_None;

		coord = pt.y;
		sizeArrow = sizeArrowSB.y;
		sizeTotal = size.y;
	}
	else // horizontal
	{
		if (pt.y < 0 || pt.y > size.y)
			return Element_None;

		coord = pt.x;
		sizeArrow = sizeArrowSB.x;
		sizeTotal = size.x;
	}

	// test for the arrows first as it's faster
	if (coord < 0 || coord > sizeTotal)
	{
		return Element_None;
	}
	else if (coord < sizeArrow)
	{
		return Element_None;//wxHT_SCROLLBAR_ARROW_LINE_1;
	}
	else if (coord > sizeTotal - sizeArrow)
	{
		return Element_None;// wxHT_SCROLLBAR_ARROW_LINE_2;
	}
	else
	{
		// calculate the thumb position in pixels
		sizeTotal -= 2 * sizeArrow;
		wxCoord thumbStart, thumbEnd;
		int range = GetRange();
		if (!range)
		{
			// clicking the scrollbar without range has no effect
			return Element_None;
		}
		else
		{
			GetScrollBarThumbSize(sizeTotal,
				GetThumbPosition(),
				GetThumbSize(),
				range,
				&thumbStart,
				&thumbEnd);
		}

		// now compare with the thumb position
		coord -= sizeArrow;
		if (coord < thumbStart)
			return Element_Bar_1;
		else if (coord > thumbEnd)
			return Element_Bar_2;
		else
			return Element_Thumb;
	}
}


wxCoord FlatScrollBar::ScrollbarToPixel(int thumbPos)
{
	int range = GetRange();
	if (!range)
	{
		// the only valid position anyhow
		return 0;
	}

	if (thumbPos == -1)
	{
		// by default use the current thumb position
		thumbPos = GetThumbPosition();
	}

	const wxSize sizeArrow(0, 0);
	return (thumbPos * GetScrollbarSize()) / range
		+ (IsVertical() ? sizeArrow.y : sizeArrow.x);
}

int FlatScrollBar::PixelToScrollbar(wxCoord coord)
{
	const wxSize sizeArrow(0, 0);
	return ((coord - (IsVertical() ? sizeArrow.y : sizeArrow.x)) *
		GetRange()) / GetScrollbarSize();
}

wxCoord FlatScrollBar::GetScrollbarSize() const
{
	const wxSize sizeArrowSB(0,0);

	wxCoord sizeArrow, sizeTotal;
	if (IsVertical())
	{
		sizeArrow = sizeArrowSB.y;
		sizeTotal = GetSize().y;
	}
	else // horizontal
	{
		sizeArrow = sizeArrowSB.x;
		sizeTotal = GetSize().x;
	}

	return sizeTotal - 2 * sizeArrow;
}


int FlatScrollBar::GetThumbPosition() const
{
	return m_thumbPos;
}
void FlatScrollBar::SetThumbPosition(int pos)
{
	//wxCHECK_RET(pos >= 0 && pos <= m_range, wxT("thumb position out of range"));
	DoSetThumb(pos);
}

void FlatScrollBar::SetScrollbar(int position, int thumbSize, int range, int pageSize, bool refresh)
{
	// we only refresh everything when the range changes, thumb position
	// changes are handled in OnIdle
	bool needsRefresh = (range != m_range) ||
		(thumbSize != m_thumbSize) ||
		(pageSize != m_pageSize);

	if (!IsVertical())
	{
		//temp
		m_range = range;
	}
	// set all parameters
	m_range = range;
	m_thumbSize = thumbSize;
	SetThumbPosition(position);
	m_pageSize = pageSize;

	
	// Hide or show bar if needed
	bool wasvisible = IsShown();
	Show(m_range > m_pageSize);

	if (wasvisible != IsShown())
	{
		GetParent()->Layout();
	}


	if (refresh && needsRefresh && IsShown() )
	{
		paintNow();
	}
}


void FlatScrollBar::DoSetThumb(int pos)
{
	// don't assert hecks here, we're a private function which is meant to be
	// called with any args at all
	if (pos < 0)
	{
		pos = 0;
	}
	else if (pos > m_range - m_thumbSize)
	{
		pos = m_range - m_thumbSize;
	}

	if (m_thumbPos == pos)
	{
		// nothing changed, avoid refreshes which would provoke flicker
		return;
	}

	if (m_thumbPosOld == -1)
	{
		// remember the old thumb position
		m_thumbPosOld = m_thumbPos;
	}

	m_thumbPos = pos;
	m_dirty = true;
	// Orginally thay use virtual m_dirty and void OnInternalIdle(); for redrawing
	paintNow();
}




bool FlatScrollBar::PerformAction(const wxString& action,long numArg,const wxString& strArg)
{
	int thumbOld = m_thumbPos;
	bool notify = false; // send an event about the change?
	wxEventType scrollType;

	// test for thumb move first as these events happen in quick succession
	if (action == wxACTION_SCROLL_THUMB_MOVE)
	{
		DoSetThumb(numArg);
	   // VS: we have to force redraw here, otherwise the thumb will lack
		//     behind mouse cursor
		//UpdateThumb();
		//this->paintNow();
		scrollType = wxEVT_SCROLLWIN_THUMBTRACK;
	}
	else if (action == wxACTION_SCROLL_LINE_UP)
	{
		scrollType = wxEVT_SCROLLWIN_LINEUP;
		DoSetThumb(m_thumbPos - 1);		
	}
	else if (action == wxACTION_SCROLL_LINE_DOWN)
	{
		scrollType = wxEVT_SCROLLWIN_LINEDOWN;
		DoSetThumb(m_thumbPos + 1);
	}
	else if (action == wxACTION_SCROLL_PAGE_UP)
	{
		scrollType = wxEVT_SCROLLWIN_PAGEUP;
		DoSetThumb(m_thumbPos - m_pageSize);
	}
	else if (action == wxACTION_SCROLL_PAGE_DOWN)
	{
		scrollType = wxEVT_SCROLLWIN_PAGEDOWN;
		DoSetThumb(m_thumbPos + m_pageSize);
	}
	else if (action == wxACTION_SCROLL_START)
	{
		scrollType = wxEVT_SCROLLWIN_THUMBRELEASE; // anything better?
		DoSetThumb(0);
	}
	else if (action == wxACTION_SCROLL_END)
	{
		scrollType = wxEVT_SCROLLWIN_THUMBRELEASE; // anything better?
		DoSetThumb(m_range - m_thumbSize);
	}
	else if (action == wxACTION_SCROLL_THUMB_DRAG)
	{
		// we won't use it but this line suppresses the compiler
		// warning about "variable may be used without having been
		// initialized"
		scrollType = wxEVT_NULL;
	}
	else if (action == wxACTION_SCROLL_THUMB_RELEASE)
	{
		// always notify about this
		notify = true;
		scrollType = wxEVT_SCROLLWIN_THUMBRELEASE;
	}

	// has scrollbar position changed?
	bool changed = m_thumbPos != thumbOld;
	if (notify || changed)
	{
		if ( IsStandalone() )
		{
			// we should generate EVT_SCROLL events for the standalone
			// scrollbars and not the EVT_SCROLLWIN ones
			//
			// NB: we assume that scrollbar events are sequentially numbered
			//     but this should be ok as other code relies on this as well
			scrollType += wxEVT_SCROLL_TOP - wxEVT_SCROLLWIN_TOP;
			wxScrollEvent event(scrollType, this->GetId(), m_thumbPos,
				IsVertical() ? wxVERTICAL : wxHORIZONTAL);
			event.SetEventObject(this);
			//GetEventHandler()->ProcessEvent(event);
			m_handler->ProcessEvent(event);
		}
		else // part of the window
		{
			wxScrollWinEvent event(scrollType, m_thumbPos,
				IsVertical() ? wxVERTICAL : wxHORIZONTAL);
			event.SetEventObject(this);
			GetParent()->GetEventHandler()->ProcessEvent(event);
		}
	}

	return true;
}