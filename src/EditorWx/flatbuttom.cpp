#include "wx/wx.h"
#include "flatbuttom.h"



FlatButtom::FlatButtom(wxWindow *parent, int id, wxString text )
	: wxWindow(parent, id)
{
	SetMinSize(wxSize(buttonWidth, buttonHeight));
	m_text = text;
	m_pressedDown = false;
}


FlatButtom::~FlatButtom()
{
}

BEGIN_EVENT_TABLE(FlatButtom, wxWindow)
	EVT_MOTION(FlatButtom::mouseMoved)
	EVT_LEFT_DOWN(FlatButtom::mouseDown)
	EVT_LEFT_UP(FlatButtom::mouseReleased)
	EVT_RIGHT_DOWN(FlatButtom::rightClick)
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
	if (m_pressedDown)
		dc.SetBrush(*wxRED_BRUSH);
	else
		dc.SetBrush(*wxGREY_BRUSH);

	dc.DrawRectangle(0, 0, buttonWidth, buttonHeight);
	dc.DrawText(m_text, 20, 15);
}

void FlatButtom::mouseDown(wxMouseEvent& event)
{
	m_pressedDown = true;
	paintNow();
}
void FlatButtom::mouseReleased(wxMouseEvent& event)
{
	m_pressedDown = false;
	paintNow();

	wxMessageBox(wxT("You pressed a custom button"));
}
void FlatButtom::mouseLeftWindow(wxMouseEvent& event)
{
	if (m_pressedDown)
	{
		m_pressedDown = false;
		paintNow();
	}
}

// currently unused events
void FlatButtom::mouseMoved(wxMouseEvent& event) {}
void FlatButtom::mouseWheelMoved(wxMouseEvent& event) {}
void FlatButtom::rightClick(wxMouseEvent& event) {}
void FlatButtom::keyPressed(wxKeyEvent& event) {}
void FlatButtom::keyReleased(wxKeyEvent& event) {}

