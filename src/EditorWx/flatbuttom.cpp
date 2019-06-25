#include "wx/wx.h"
#include "flatbuttom.h"
#include "prefs.h"
#include "app.h"
#include "appframe.h"



FlatButton::FlatButton(wxWindow *parent, int id, const wxString &text, const wxBitmap &bmp, bool setwndcolor)
	:  m_text(text), wxWindow(parent, id)
{

	SetLabel(m_text);
	if (bmp.IsOk())
		SetBitmap(bmp);
	Init(setwndcolor);
	
}

/*
FlatButton::FlatButton(wxWindow *parent, int id, const wxBitmap &bmp, bool setwndcolor) 
	: wxWindow(parent, id)
{
	SetBitmap(bmp);
	Init(setwndcolor);
}
*/

void FlatButton::Init(bool setwndcolor)
{
	m_cmd = -1;
	m_marginBmpX = 6;
	m_marginBmpY = 4;
	m_status = statusNone;
	m_captured = false;

	if (setwndcolor)
	{
		SetCustomColor(ColourScheme::CONTROL, ColourScheme::WINDOW);
		SetCustomColor(ColourScheme::CONTROL_HOVER, ColourScheme::FRAME);
		SetCustomColor(ColourScheme::CONTROL_PRESSED, ColourScheme::FRAME);
	}
	SetBestClientSize();
}


void FlatButton::SetBitmap(const wxBitmap& bitmap)
{
	m_bitmap = bitmap;
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
wxColor FlatButton::GetButtonColor(int clr)
{
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	auto it = m_colors.find(clr);
	return (it != m_colors.end()) ? clrs->Get(static_cast<ColourScheme::StdColour>(it->second)) : clrs->Get(static_cast<ColourScheme::StdColour>(clr));
}

void FlatButton::SetCustomColor(int clrIn, int clOut)
{
	m_colors[clrIn] = clOut;
}

void FlatButton::DrawBackground(wxDC&  dc, const wxRect &rc)
{
	wxColor clr; 
	if (m_status == statusHover)
		clr = GetButtonColor(ColourScheme::CONTROL_HOVER);
	else if (m_status == statusPressed)
		clr = GetButtonColor(ColourScheme::CONTROL_PRESSED);	
	else
		clr = GetButtonColor(ColourScheme::CONTROL);

	dc.SetBrush(wxBrush(clr));

	if (this->GetWindowStyle() & wxBORDER_NONE)
		dc.SetPen(*wxTRANSPARENT_PEN);
	else
	{
		dc.SetPen(GetButtonColor(ColourScheme::BORDER));
	}
	
	dc.DrawRectangle(rc);
}

void FlatButton::DrawLabel(wxDC&  dc, const wxRect &rc)
{

	wxColor clr;
	if (m_status == statusHover)
		clr = GetButtonColor(ColourScheme::CONTROL_TEXT);
	else if(m_status == statusPressed)
		clr = GetButtonColor(ColourScheme::CONTROL_TEXT);
	else
		clr = GetButtonColor(ColourScheme::CONTROL_TEXT);
	
	dc.SetTextBackground(wxColor());
	dc.SetTextForeground(clr);
	wxRect rcLabel(rc);
	rcLabel.Deflate(m_marginBmpX, m_marginBmpY);
	dc.DrawLabel(m_text, rcLabel, wxALIGN_LEFT| wxALIGN_CENTER_VERTICAL);
};

void FlatButton::DrawBitmap(wxDC&  dc, const wxRect &rc)
{
	if (!m_bitmap.IsOk())
		return;

	wxPoint pt;
	int marginX = rc.GetWidth() - m_bitmap.GetWidth() - m_marginBmpX;
	int marginY = (rc.GetHeight() - m_bitmap.GetHeight())/2;
	dc.DrawBitmap(m_bitmap, rc.GetLeft() + marginX, rc.GetTop() + marginY );
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

	dc.GetMultiLineTextExtent(m_text, &width, &height);
	if (m_bitmap.IsOk())
	{
		// allocate extra space for the bitmap
		wxCoord heightBmp = m_bitmap.GetHeight() + 2 * m_marginBmpY;
		if (height < heightBmp)
			height = heightBmp;

		width += m_bitmap.GetWidth() + m_marginBmpX;
	}
	
	width += 2* m_marginBmpX;

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