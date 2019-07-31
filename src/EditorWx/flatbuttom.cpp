#include "wx/wx.h"
#include "flatbuttom.h"
#include "prefs.h"
#include "app.h"
#include "appframe.h"



FlatButton::FlatButton(wxWindow *parent, int id, const wxString &text, int style, const wxArtID& idArt)
	:  wxWindow(parent, id, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
	SetLabel(text);
	m_style = style;
	Init();
	SetBitmap(idArt, m_spacer);
}

#define DO_SET_COLOUR( index, indexClr)  m_colors[index] = clrs->Get(indexClr)
	
void FlatButton::Init()
{
	m_cmd = -1;
	m_marginX = 6;
	m_marginY = 4;
	m_status = statusNone;
	m_captured = false;
	m_spacer = 0; // spacer between bmp and text
	m_colors.resize(ColourNum);
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();

	DO_SET_COLOUR(ForegroundColour, ColourScheme::CONTROL_TEXT);
	DO_SET_COLOUR(HoverForegroundColour, ColourScheme::CONTROL_TEXT_HOVER);
	DO_SET_COLOUR(PressForegroundColour, ColourScheme::CONTROL_TEXT_HOVER);
	DO_SET_COLOUR(BorderColour, ColourScheme::BORDER);
	DO_SET_COLOUR(BackgroundColour, ColourScheme::CONTROL);
	DO_SET_COLOUR(HoverBackgroundColour, ColourScheme::CONTROL_HOVER);
	DO_SET_COLOUR(PressBackgroundColour, ColourScheme::CONTROL_PRESSED);


	DO_SET_COLOUR(BackgroundColourActive, ColourScheme::CONTROL_ACTIVE);
	DO_SET_COLOUR(HoverBackgroundColourActive, ColourScheme::CONTROL_ACTIVE_HOVER);
	DO_SET_COLOUR(PressBackgroundColourActive, ColourScheme::CONTROL_ACTIVE_PRESSED);
	DO_SET_COLOUR(ForegroundColourActive, ColourScheme::CONTROL_ACTIVE_TEXT);
	DO_SET_COLOUR(HoverForegroundColourActive, ColourScheme::CONTROL_ACTIVE_TEXT_HOVER);
	DO_SET_COLOUR(PressForegroundColourActive, ColourScheme::CONTROL_ACTIVE_TEXT_HOVER);

	SetBestClientSize();
}


void FlatButton::SetBitmap(const wxBitmap& bitmap, int spacer)
{
	m_bitmap = bitmap;
	m_bitmap_hover = m_bitmap;
	m_spacer = spacer;
	SetBestClientSize();
}

void FlatButton::SetBitmap(const wxBitmap& bitmap, const wxBitmap& bitmaphover, int spacer)
{
	m_bitmap = bitmap;
	m_bitmap_hover = bitmaphover;
	m_spacer = spacer;
	SetBestClientSize();
}

void FlatButton::SetBitmap(const wxString& idArt, int spacer)
{
	if (idArt.IsEmpty())
		return;
	m_bitmap = wxArtProvider::GetBitmap(idArt, wxART_MENU);
	m_bitmap_hover = wxArtProvider::GetBitmap(idArt, ART_MENUHOVER);
	m_bitmap_disabled = wxArtProvider::GetBitmap(idArt, ART_MENUDISABLED);
	m_spacer = spacer;
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
	EVT_SIZE(FlatButton::OnSize)

END_EVENT_TABLE()



void FlatButton::DoEnable(bool enable)
{
	wxWindow::DoEnable(enable);
	Refresh();
}


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
void FlatButton::OnSize(wxSizeEvent& event)
{
	if (m_style & FB_LABEL_CENTER)
		Refresh();
}


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
	wxRect rcLabel;
	wxPoint ptButmap;
	CalcGeometry(rc, rcLabel, ptButmap);
	DrawLabel(dc, rcLabel);
	DrawBitmap(dc, ptButmap);
	
}

void FlatButton::DrawBackground(wxDC&  dc, const wxRect &rc)
{
	if (m_style & FB_TRANSPARENT)
		return;

	wxColor clr; 
	bool checked = ((m_style & FB_CHECKED) != 0);
	if (m_status == statusHover)
		clr = GetColour(checked ? HoverBackgroundColourActive : HoverBackgroundColour);
	else if (m_status == statusPressed)
		clr = GetColour(checked ? PressBackgroundColourActive : PressBackgroundColour);
	else
		clr = GetColour(checked ? BackgroundColourActive : BackgroundColour);
		
	dc.SetBrush(wxBrush(clr));

	if (this->GetWindowStyle() & wxBORDER_NONE)
		dc.SetPen(*wxTRANSPARENT_PEN);
	else
	{
		dc.SetPen(GetColour(BorderColour));
	}
	

	dc.DrawRectangle(rc);
}

void FlatButton::CalcGeometry(const wxRect &rcIn, wxRect &rcLabel, wxPoint &ptButmap)
{
	rcLabel = rcIn;
	if (m_bitmap.IsOk())
	{
		int move = (m_bitmap.GetWidth() + m_spacer + m_marginX);
		if (m_style & FB_BITMAP_LEFT)
		{
			rcLabel.x += move;
			rcLabel.width -= move;
		}
		else if (m_style & FB_BITMAP_RIGHT)
		{

			rcLabel.width -= move;
		}
		else
		{
			rcLabel.width -= move;
		}
	}
	rcLabel.Deflate(m_marginX, m_marginY);


	if (m_bitmap.IsOk())
	{
		if (m_style & FB_BITMAP_LEFT)
			ptButmap.x = rcIn.GetLeft() + m_marginX;
		else if (m_style & FB_BITMAP_RIGHT)
			ptButmap.x = rcIn.GetLeft() + rcIn.GetWidth() - m_bitmap.GetWidth() - m_marginX;
		else
		{
			// just after label			
			if (m_style & FB_LABEL_CENTER)
			{
				wxSize minSize = GetMinSize();
				rcLabel.width = minSize.x - m_bitmap.GetWidth() - m_spacer - (3 * m_marginX);
				if (rcIn.width > minSize.x)
				{
					rcLabel.x = rcIn.x + (rcIn.width - minSize.x) / 2;
				}
				else
				{
					rcLabel.x = rcIn.x;
				}
			}
			ptButmap.x = rcLabel.x + rcLabel.width + m_spacer + m_marginX;
			
		}		
		ptButmap.y = rcIn.GetTop() + (rcIn.GetHeight() - m_bitmap.GetHeight()) / 2;
	}
}

void FlatButton::DrawLabel(wxDC&  dc, const wxRect &rc)
{

	wxColor clr;
	bool checked = ((m_style & FB_CHECKED) != 0);
	if (m_status == statusHover)
		clr = GetColour(checked ? HoverForegroundColourActive : HoverForegroundColour);
	else if(m_status == statusPressed)
		clr = GetColour(checked ? PressForegroundColourActive : PressForegroundColour);
	else
		clr = GetColour(checked ? ForegroundColourActive : ForegroundColour);
	
	dc.SetTextBackground(wxColor());
	dc.SetTextForeground(clr);
	
	int align = 0;

	

	if (m_style & FB_LABEL_RIGHT)
	{
		align |= wxALIGN_RIGHT;
	}
	else if (m_style & FB_LABEL_CENTER)
	{
		align |= wxALIGN_CENTER_HORIZONTAL;
	}
	else
		align |= wxALIGN_LEFT;

	// in any casees
	align |= wxALIGN_CENTER_VERTICAL;
	
	dc.DrawLabel(GetLabel(), rc, align );
};

void FlatButton::DrawBitmap(wxDC&  dc, const wxPoint &pt)
{
	if (!m_bitmap.IsOk())
		return;
	if ( !IsEnabled() && m_bitmap_disabled.IsOk() )
		dc.DrawBitmap(m_bitmap_disabled, pt, true);
	else if ( ((m_status == statusHover) || (m_status == statusPressed)) && m_bitmap_hover.IsOk() )
		dc.DrawBitmap(m_bitmap_hover, pt, true);
	else
		dc.DrawBitmap(m_bitmap, pt, true );
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


	wxCoord width=0, height = 0;
	wxString label = GetLabel();
	if (!label.IsEmpty())
	{
		wxClientDC dc(wxConstCast(this, FlatButton));
		wxFont font(GetFont());
		if (!font.IsOk())
			font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);

		dc.SetFont(font);

		dc.GetMultiLineTextExtent(label, &width, &height);
	}

	if (m_bitmap.IsOk())
	{
		// allocate extra space for the bitmap
		wxCoord heightBmp = m_bitmap.GetHeight();
		if (height < heightBmp)
			height = heightBmp;

		if (!label.IsEmpty())
		{
			width += m_marginX;
			width += m_spacer;
		}
		width += m_bitmap.GetWidth();
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

void FlatButton::SetChecked(bool checked)
{
	if ( checked )
		m_style |= FB_CHECKED; 
	else
		m_style &= ~FB_CHECKED;
		
}