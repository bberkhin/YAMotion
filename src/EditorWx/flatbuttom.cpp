#include "wx/wx.h"
#include "flatbuttom.h"
#include "prefs.h"



FlatButtom::FlatButtom(wxWindow *parent, int id,  wxString text )
	: m_text(text),m_marginBmpX(6), m_marginBmpY(4),  wxWindow(parent, id)
{
	m_status = statusNone;
	SetBestClientSize();
	
//	m_winCapture = NULL;
//	m_winHasMouse = false;
}


void FlatButtom::SetBitmap(const wxBitmap& bitmap)
{
	m_bitmap = bitmap;
	SetBestClientSize();
}

FlatButtom::~FlatButtom()
{
}

BEGIN_EVENT_TABLE(FlatButtom, wxWindow)
	EVT_MOTION(FlatButtom::mouseMoved)
	EVT_LEFT_DOWN(FlatButtom::mouseDown)
	EVT_LEFT_UP(FlatButtom::mouseReleased)
	EVT_RIGHT_DOWN(FlatButtom::rightClick)
	EVT_ENTER_WINDOW(FlatButtom::mouseEnterWindow)
	EVT_LEAVE_WINDOW(FlatButtom::mouseLeftWindow)
	EVT_KEY_DOWN(FlatButtom::keyPressed)
	EVT_KEY_UP(FlatButtom::keyReleased)
	EVT_MOUSEWHEEL(FlatButtom::mouseWheelMoved)
	// catch paint events
	EVT_PAINT(FlatButtom::paintEvent)
END_EVENT_TABLE()


/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void FlatButtom::paintEvent(wxPaintEvent & evt)
{
	// depending on your system you may need to look at double-buffered dcs
	wxPaintDC dc(this);
	render(dc);
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 */
void FlatButtom::paintNow()
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
void FlatButtom::render(wxDC&  dc)
{
	wxRect rc = GetClientRect();
	DrawBackground(dc, rc);
	DrawLabel(dc, rc);
	DrawBitmap(dc, rc);
	
}

void FlatButtom::DrawBackground(wxDC&  dc, const wxRect &rc)
{
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	wxColor clr; 
	if ( m_status == statusHover )
		clr = clrs->Get(ColourScheme::CONTROL_HOVER);
	else if(m_status == statusPressed)
		clr = clrs->Get(ColourScheme::CONTROL_PRESSED);
	else
		clr = clrs->Get(ColourScheme::CONTROL);

	dc.SetBrush(wxBrush(clr));

	if (this->GetWindowStyle() & wxBORDER_NONE)
		dc.SetPen(*wxTRANSPARENT_PEN);
	else
	{
		dc.SetPen(clrs->Get(ColourScheme::BORDER));
	}
	
	dc.DrawRectangle(rc);
}

void FlatButtom::DrawLabel(wxDC&  dc, const wxRect &rc)
{

	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	wxColor clr;
	if (m_status == statusHover)
		clr = clrs->Get(ColourScheme::CONTROL_TEXT);
	else if(m_status == statusPressed)
		clr = clrs->Get(ColourScheme::CONTROL_TEXT);
	else
		clr = clrs->Get(ColourScheme::CONTROL_TEXT);
	
	dc.SetTextBackground(wxColor());
	dc.SetTextForeground(clr);
	wxRect rcLabel(rc);
	rcLabel.Deflate(m_marginBmpX, m_marginBmpY);
	dc.DrawLabel(m_text, rcLabel, wxALIGN_LEFT| wxALIGN_CENTER_VERTICAL);
};

void FlatButtom::DrawBitmap(wxDC&  dc, const wxRect &rc)
{
	if (!m_bitmap.IsOk())
		return;

	wxPoint pt;
	int marginX = rc.GetWidth() - m_bitmap.GetWidth() - m_marginBmpX;
	int marginY = (rc.GetHeight() - m_bitmap.GetHeight())/2;
	dc.DrawBitmap(m_bitmap, rc.GetLeft() + marginX, rc.GetTop() + marginY );
}


void FlatButtom::mouseDown(wxMouseEvent& event)
{
	m_status = statusPressed;
	CaptureMouse();

	paintNow();
}
void FlatButtom::mouseReleased(wxMouseEvent& event)
{
	m_status = statusNone;
	ReleaseMouse();
	paintNow();
	
	wxPoint pt = event.GetPosition();
	wxRect rc = GetClientRect();
	if ( rc.Contains(pt) )
		DoClick();
}

void FlatButtom::mouseLeftWindow(wxMouseEvent& event)
{
	if (m_status != statusPressed)
	{
		m_status = statusNone;
		paintNow();
	}
}

void FlatButtom::mouseEnterWindow(wxMouseEvent& event)
{
	if (m_status != statusPressed)
	{
		m_status = statusHover;
		paintNow();
	}
}



// currently unused events
void FlatButtom::mouseMoved(wxMouseEvent& event) {}
void FlatButtom::mouseWheelMoved(wxMouseEvent& event) {}
void FlatButtom::rightClick(wxMouseEvent& event) {}
void FlatButtom::keyPressed(wxKeyEvent& event) {}
void FlatButtom::keyReleased(wxKeyEvent& event) {}



void FlatButtom::SetBestClientSize() 
{
	wxClientDC dc(wxConstCast(this, FlatButtom));
	wxCoord width, height;
	dc.GetMultiLineTextExtent(m_text, &width, &height);

	if (m_bitmap.IsOk())
	{
		// allocate extra space for the bitmap
		wxCoord heightBmp = m_bitmap.GetHeight() + 2 * m_marginBmpY;
		if (height < heightBmp)
			height = heightBmp;

		width += m_bitmap.GetWidth() + 3 * m_marginBmpX;
	}

	SetMinSize(wxSize(width, height));
}

void FlatButtom::DoClick()
{
	wxCommandEvent event(wxEVT_BUTTON, GetId());
	event.SetEventObject(this);
	ProcessWindowEvent(event);
}