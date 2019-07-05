#include "wx/wx.h"
#include "flatbuttom.h"
#include "prefs.h"
#include "app.h"
#include "appframe.h"



FlatButton::FlatButton(wxWindow *parent, int id, const wxString &text, const wxBitmap &bmp, bool setwndcolor)
	:  wxWindow(parent, id, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
	SetLabel(text);
	Init(setwndcolor);
	if (bmp.IsOk())
		SetBitmap(bmp);
	
}

#define DO_SET_COLOUR( index, indexClr)  m_colors[index] = clrs->Get(indexClr)
	
void FlatButton::Init(bool setwndcolor)
{
	m_cmd = -1;
	m_marginX = 6;
	m_marginY = 4;
	m_status = statusNone;
	m_captured = false;
	m_spacer = 0; // spacer between bmp and text
	m_right = false;
	m_colors.resize(ColourNum);
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();

	DO_SET_COLOUR(ForegroundColour, ColourScheme::CONTROL_TEXT);
	DO_SET_COLOUR(HoverForegroundColour, ColourScheme::CONTROL_TEXT);
	DO_SET_COLOUR(PressForegroundColour, ColourScheme::CONTROL_TEXT);
	DO_SET_COLOUR(BorderColour, ColourScheme::BORDER);

	if (setwndcolor)
	{
		DO_SET_COLOUR(BackgroundColour, ColourScheme::WINDOW);
		DO_SET_COLOUR(HoverBackgroundColour, ColourScheme::FRAME);
		DO_SET_COLOUR(PressBackgroundColour, ColourScheme::FRAME);
	}
	else
	{
		DO_SET_COLOUR(BackgroundColour, ColourScheme::CONTROL);
		DO_SET_COLOUR(HoverBackgroundColour, ColourScheme::CONTROL_HOVER);
		DO_SET_COLOUR(PressBackgroundColour, ColourScheme::CONTROL_PRESSED);

	}

	SetBestClientSize();
}


void FlatButton::SetBitmap(const wxBitmap& bitmap, int spacer, bool placetoright)
{
	m_bitmap = bitmap;
	m_spacer = spacer;
	m_right = placetoright;
	SetBestClientSize();
}

void FlatButton::SetMargins(int marginX, int marginY)
{
	if ( marginX>= 0 )
		m_marginX = marginX;
	if (marginY >= 0)
		m_marginY = marginY;
	SetBestClientSize();
}

FlatButton::~FlatButton()
{
}

BEGIN_EVENT_TABLE(FlatButton, wxWindow)
	EVT_MOTION(FlatButton::mouseMoved)
	EVT_LEFT_DOWN(FlatButton::mouseDown)
	EVT_LEFT_UP(FlatButton::mouseReleased)
	EVT_RIGHT_DOWN(FlatButton::rightClick)
	EVT_ENTER_WINDOW(FlatButton::mouseEnterWindow)
	EVT_LEAVE_WINDOW(FlatButton::mouseLeftWindow)
	EVT_KEY_DOWN(FlatButton::keyPressed)
	EVT_KEY_UP(FlatButton::keyReleased)
	EVT_MOUSEWHEEL(FlatButton::mouseWheelMoved)
	// catch paint events
	EVT_PAINT(FlatButton::paintEvent)
END_EVENT_TABLE()


/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void FlatButton::paintEvent(wxPaintEvent & evt)
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
void FlatButton::paintNow()
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
void FlatButton::render(wxDC&  dc)
{
	wxRect rc = GetClientRect();
	DrawBackground(dc, rc);
	DrawLabel(dc, rc);
	DrawBitmap(dc, rc);
	
}

void FlatButton::DrawBackground(wxDC&  dc, const wxRect &rc)
{
	wxColor clr; 
	if (m_status == statusHover)
		clr = GetColour(HoverBackgroundColour);
	else if (m_status == statusPressed)
		clr = GetColour(PressBackgroundColour);
	else
		clr = GetColour(BackgroundColour);

	dc.SetBrush(wxBrush(clr));

	if (this->GetWindowStyle() & wxBORDER_NONE)
		dc.SetPen(*wxTRANSPARENT_PEN);
	else
	{
		dc.SetPen(GetColour(BorderColour));
	}
	
	dc.DrawRectangle(rc);
}

void FlatButton::DrawLabel(wxDC&  dc, const wxRect &rc)
{

	wxColor clr;
	if (m_status == statusHover)
		clr = GetColour(HoverForegroundColour);
	else if(m_status == statusPressed)
		clr = GetColour(PressForegroundColour);
	else
		clr = GetColour(ForegroundColour);
	
	dc.SetTextBackground(wxColor());
	dc.SetTextForeground(clr);
	wxRect rcLabel(rc);
	int align = 0;
	if (m_right)
	{
		if (m_bitmap.IsOk())
		{
			int move = (m_bitmap.GetWidth() + m_spacer + m_marginX);
			rcLabel.x += move;
			rcLabel.width -= move;
		}
		else 
			align |= wxALIGN_RIGHT;
	}

	if ( !m_bitmap.IsOk() )
		align |= wxALIGN_CENTER_HORIZONTAL;
	else
		align |=  wxALIGN_LEFT;
	
	align |= wxALIGN_CENTER_VERTICAL;

	rcLabel.Deflate(m_marginX, m_marginY);
	dc.DrawLabel(GetLabel(), rcLabel, align );
};

void FlatButton::DrawBitmap(wxDC&  dc, const wxRect &rc)
{
	if (!m_bitmap.IsOk())
		return;

	wxPoint pt;
	int marginX;
	if ( m_right )
		marginX = m_marginX;
	else
		marginX = rc.GetWidth() - m_bitmap.GetWidth() - m_marginX;
	int marginY = (rc.GetHeight() - m_bitmap.GetHeight())/2;
	dc.DrawBitmap(m_bitmap, rc.GetLeft() + marginX, rc.GetTop() + marginY, true );
}


void FlatButton::mouseDown(wxMouseEvent& event)
{
	m_status = statusPressed;
	CaptureMouse();
	m_captured = true;

	paintNow();
}
void FlatButton::mouseReleased(wxMouseEvent& event)
{
	m_status = statusNone;
	if (m_captured)
	{
		ReleaseMouse();
		m_captured = false;
	}

	paintNow();
	
	wxPoint pt = event.GetPosition();
	wxRect rc = GetClientRect();
	if ( rc.Contains(pt) )
		DoClick();
}

void FlatButton::mouseLeftWindow(wxMouseEvent& event)
{
	if (m_status != statusPressed)
	{
		m_status = statusNone;
		paintNow();
	}
}

void FlatButton::mouseEnterWindow(wxMouseEvent& event)
{
	if (m_status != statusPressed)
	{
		m_status = statusHover;
		paintNow();
	}
}



// currently unused events
void FlatButton::mouseMoved(wxMouseEvent& event) {}
void FlatButton::mouseWheelMoved(wxMouseEvent& event) {}
void FlatButton::rightClick(wxMouseEvent& event) {}
void FlatButton::keyPressed(wxKeyEvent& event) {}
void FlatButton::keyReleased(wxKeyEvent& event) {}



void FlatButton::SetBestClientSize() 
{

	wxClientDC dc(wxConstCast(this, FlatButton));
	wxCoord width, height;
	wxFont font(GetFont());
	if (!font.IsOk())
		font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);

	dc.SetFont(font);

	dc.GetMultiLineTextExtent(GetLabel(), &width, &height);
	if (m_bitmap.IsOk())
	{
		// allocate extra space for the bitmap
		wxCoord heightBmp = m_bitmap.GetHeight();
		if (height < heightBmp)
			height = heightBmp;

		width += m_bitmap.GetWidth() + m_marginX;
		width += m_spacer;
	}
	
	height += 2 * m_marginY;
	width += 2* m_marginX;

	SetMinSize(wxSize(width, height));
}

void FlatButton::DoClick()
{
	
	wxCommandEvent event(wxEVT_BUTTON, GetId());
	event.SetEventObject(this);
	ProcessWindowEvent(event);

	if (m_cmd > 0)
	{
		wxCommandEvent *ev = new wxCommandEvent(wxEVT_MENU, m_cmd);
		wxQueueEvent( wxGetApp().GetFrame(), ev);
	}
}