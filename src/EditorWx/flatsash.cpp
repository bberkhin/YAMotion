#include "flatsash.h"
/*
#ifndef WX_PRECOMP
    #include "wx/dialog.h"
    #include "wx/frame.h"
    #include "wx/settings.h"
    #include "wx/dcclient.h"
    #include "wx/dcscreen.h"
    #include "wx/math.h"
#endif

#include <stdlib.h>
*/

#include "wx/laywin.h"
#include "prefs.h"

wxIMPLEMENT_DYNAMIC_CLASS(FlatSashWindow, wxWindow);

wxBEGIN_EVENT_TABLE(FlatSashWindow, wxWindow)
    EVT_PAINT(FlatSashWindow::OnPaint)
    EVT_SIZE(FlatSashWindow::OnSize)
    EVT_MOUSE_EVENTS(FlatSashWindow::OnMouseEvent)
#if defined( __WXMSW__ ) || defined( __WXMAC__)
    EVT_SET_CURSOR(FlatSashWindow::OnSetCursor)
#endif // __WXMSW__ || __WXMAC__

wxEND_EVENT_TABLE()

bool FlatSashWindow::Create(wxWindow *parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style, const wxString& name)
{
    return wxWindow::Create(parent, id, pos, size, style, name);
}

FlatSashWindow::~FlatSashWindow()
{
    delete m_sashCursorWE;
    delete m_sashCursorNS;
}

void FlatSashWindow::Init()
{
    m_draggingEdge = wxSASH_NONE;
    m_dragMode = wxSASH_DRAG_NONE;
    m_oldX = 0;
    m_oldY = 0;
    m_firstX = 0;
    m_firstY = 0;
    m_borderSize = 3;
    m_extraBorderSize = 0;
    m_minimumPaneSizeX = 0;
    m_minimumPaneSizeY = 0;
    m_maximumPaneSizeX = 10000;
    m_maximumPaneSizeY = 10000;
    m_sashCursorWE = new wxCursor(wxCURSOR_SIZEWE);
    m_sashCursorNS = new wxCursor(wxCURSOR_SIZENS);
    m_mouseCaptured = false;
    m_currentCursor = NULL;

    // Eventually, we'll respond to colour change messages
    InitColours();
}

void FlatSashWindow::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);

    DrawBorders(dc);
    DrawSashes(dc);
}

wxRect FlatSashWindow::CalcDragRect(wxSashEdgePosition edge, int x, int y, wxSashDragStatus *pstatus)
{
	wxRect dragRect;
	int w, h;
	GetSize(&w, &h);
	int xp, yp;
	GetPosition(&xp, &yp);


	wxSashDragStatus status = wxSASH_STATUS_OK;

	// the new height and width of the window - if -1, it didn't change
	int newHeight = wxDefaultCoord,
	newWidth = wxDefaultCoord;

	// NB: x and y may be negative and they're relative to the sash window
	//     upper left corner, while xp and yp are expressed in the parent
	//     window system of coordinates, so adjust them! After this
	//     adjustment, all coordinates are relative to the parent window.
	y += yp;
	x += xp;

	switch (edge)
	{
	case wxSASH_TOP:
		if (y > yp + h)
		{
			// top sash shouldn't get below the bottom one
			status = wxSASH_STATUS_OUT_OF_RANGE;
		}
		else
		{
			newHeight = h - (y - yp);
		}
		break;

	case wxSASH_BOTTOM:
		if (y < yp)
		{
			// bottom sash shouldn't get above the top one
			status = wxSASH_STATUS_OUT_OF_RANGE;
		}
		else
		{
			newHeight = y - yp;
		}
		break;

	case wxSASH_LEFT:
		if (x > xp + w)
		{
			// left sash shouldn't get beyond the right one
			status = wxSASH_STATUS_OUT_OF_RANGE;
		}
		else
		{
			newWidth = w - (x - xp);
		}
		break;

	case wxSASH_RIGHT:
		if (x < xp)
		{
			// and the right sash, finally, shouldn't be beyond the
			// left one
			status = wxSASH_STATUS_OUT_OF_RANGE;
		}
		else
		{
			newWidth = x - xp;
		}
		break;

	case wxSASH_NONE:
		// can this happen at all?
		break;
	}

	if (newHeight == wxDefaultCoord)
	{
		// didn't change
		newHeight = h;
	}
	else
	{
		// make sure it's in m_minimumPaneSizeY..m_maximumPaneSizeY range
		newHeight = wxMax(newHeight, m_minimumPaneSizeY);
		newHeight = wxMin(newHeight, m_maximumPaneSizeY);
	}

	if (newWidth == wxDefaultCoord)
	{
		// didn't change
		newWidth = w;
	}
	else
	{
		// make sure it's in m_minimumPaneSizeY..m_maximumPaneSizeY range
		newWidth = wxMax(newWidth, m_minimumPaneSizeX);
		newWidth = wxMin(newWidth, m_maximumPaneSizeX);
	}

	dragRect = wxRect(x, y, newWidth, newHeight);
	if (pstatus)
		*pstatus = status;
	return dragRect;
}

void FlatSashWindow::OnMouseEvent(wxMouseEvent& event)
{
    wxCoord x = 0, y = 0;
    event.GetPosition(&x, &y);

    wxSashEdgePosition sashHit = SashHitTest(x, y);

    if (event.LeftDown())
    {
        CaptureMouse();
        m_mouseCaptured = true;

        if ( sashHit != wxSASH_NONE )
        {
            // Required for X to specify that
            // that we wish to draw on top of all windows
            // - and we optimise by specifying the area
            // for creating the overlap window.
            // Find the first frame or dialog and use this to specify
            // the area to draw on.
            wxWindow* parent = this;

            while (parent && !wxDynamicCast(parent, wxDialog) &&
                             !wxDynamicCast(parent, wxFrame))
              parent = parent->GetParent();

            wxScreenDC::StartDrawingOnTop(parent);

            // We don't say we're dragging yet; we leave that
            // decision for the Dragging() branch, to ensure
            // the user has dragged a little bit.
            m_dragMode = wxSASH_DRAG_LEFT_DOWN;
            m_draggingEdge = sashHit;
            m_firstX = x;
            m_firstY = y;

            if ( (sashHit == wxSASH_LEFT) || (sashHit == wxSASH_RIGHT) )
            {
                if (m_currentCursor != m_sashCursorWE)
                {
                    SetCursor(*m_sashCursorWE);
                }
                m_currentCursor = m_sashCursorWE;
            }
            else
            {
                if (m_currentCursor != m_sashCursorNS)
                {
                    SetCursor(*m_sashCursorNS);
                }
                m_currentCursor = m_sashCursorNS;
            }
        }
    }
    else if ( event.LeftUp() && m_dragMode == wxSASH_DRAG_LEFT_DOWN )
    {
        // Wasn't a proper drag
        if (m_mouseCaptured)
            ReleaseMouse();
        m_mouseCaptured = false;

        wxScreenDC::EndDrawingOnTop();
        m_dragMode = wxSASH_DRAG_NONE;
        m_draggingEdge = wxSASH_NONE;
    }
    else if (event.LeftUp() && m_dragMode == wxSASH_DRAG_DRAGGING)
    {
        // We can stop dragging now and see what we've got.
        m_dragMode = wxSASH_DRAG_NONE;
        if (m_mouseCaptured)
            ReleaseMouse();
        m_mouseCaptured = false;

        // Erase old tracker
        DrawSashTracker(m_draggingEdge, m_oldX, m_oldY);

        // End drawing on top (frees the window used for drawing
        // over the screen)
        wxScreenDC::EndDrawingOnTop();
        wxSashEdgePosition edge = m_draggingEdge;
		m_draggingEdge = wxSASH_NONE;
		wxSashDragStatus status;
        wxRect dragRect = CalcDragRect(edge, x, y, &status);
		

        wxSashEvent eventSash(GetId(), edge);
        eventSash.SetEventObject(this);
        eventSash.SetDragStatus(status);
        eventSash.SetDragRect(dragRect);
        GetEventHandler()->ProcessEvent(eventSash);
    }
    else if ( event.LeftUp() )
    {
        if (m_mouseCaptured)
           ReleaseMouse();
        m_mouseCaptured = false;
    }
    else if ((event.Moving() || event.Leaving()) && !event.Dragging())
    {
        // Just change the cursor if required
        if ( sashHit != wxSASH_NONE )
        {
            if ( (sashHit == wxSASH_LEFT) || (sashHit == wxSASH_RIGHT) )
            {
                if (m_currentCursor != m_sashCursorWE)
                {
                    SetCursor(*m_sashCursorWE);
                }
                m_currentCursor = m_sashCursorWE;
            }
            else
            {
                if (m_currentCursor != m_sashCursorNS)
                {
                    SetCursor(*m_sashCursorNS);
                }
                m_currentCursor = m_sashCursorNS;
            }
        }
        else
        {
            SetCursor(wxNullCursor);
            m_currentCursor = NULL;
        }
    }
    else if ( event.Dragging() &&
              ((m_dragMode == wxSASH_DRAG_DRAGGING) ||
               (m_dragMode == wxSASH_DRAG_LEFT_DOWN)) )
    {
        if ( (m_draggingEdge == wxSASH_LEFT) || (m_draggingEdge == wxSASH_RIGHT) )
        {
            if (m_currentCursor != m_sashCursorWE)
            {
                SetCursor(*m_sashCursorWE);
            }
            m_currentCursor = m_sashCursorWE;
        }
        else
        {
            if (m_currentCursor != m_sashCursorNS)
            {
                SetCursor(*m_sashCursorNS);
            }
            m_currentCursor = m_sashCursorNS;
        }

        if (m_dragMode == wxSASH_DRAG_LEFT_DOWN)
        {
            m_dragMode = wxSASH_DRAG_DRAGGING;
            DrawSashTracker(m_draggingEdge, x, y);
        }
        else
        {
            if ( m_dragMode == wxSASH_DRAG_DRAGGING )
            {
                // Erase old tracker
                DrawSashTracker(m_draggingEdge, m_oldX, m_oldY);

                // Draw new one
                DrawSashTracker(m_draggingEdge, x, y);
/*
				wxSashDragStatus status;
				wxRect dragRect = CalcDragRect(m_draggingEdge, x, y, &status);
				wxSashEvent eventSash(GetId(), m_draggingEdge);
				eventSash.SetEventObject(this);
				eventSash.SetDragStatus(status);
				eventSash.SetDragRect(dragRect);
				GetEventHandler()->ProcessEvent(eventSash);
*/
            }
        }
        m_oldX = x;
        m_oldY = y;
    }
    else if ( event.LeftDClick() )
    {
        // Nothing
    }
    else
    {
    }
}

void FlatSashWindow::OnSize(wxSizeEvent& WXUNUSED(event))
{
    SizeWindows();
}

wxSashEdgePosition FlatSashWindow::SashHitTest(int x, int y, int WXUNUSED(tolerance))
{
    int cx, cy;
    GetClientSize(& cx, & cy);

    int i;
    for (i = 0; i < 4; i++)
    {
        wxSashEdge& edge = m_sashes[i];
        wxSashEdgePosition position = (wxSashEdgePosition) i ;

        if (edge.m_show)
        {
            switch (position)
            {
                case wxSASH_TOP:
                {
                    if (y >= 0 && y <= GetEdgeMargin(position))
                        return wxSASH_TOP;
                    break;
                }
                case wxSASH_RIGHT:
                {
                    if ((x >= cx - GetEdgeMargin(position)) && (x <= cx))
                        return wxSASH_RIGHT;
                    break;
                }
                case wxSASH_BOTTOM:
                {
                    if ((y >= cy - GetEdgeMargin(position)) && (y <= cy))
                        return wxSASH_BOTTOM;
                    break;
                }
                case wxSASH_LEFT:
                {
                    if ((x <= GetEdgeMargin(position)) && (x >= 0))
                        return wxSASH_LEFT;
                    break;
                }
                case wxSASH_NONE:
                {
                    break;
                }
            }
        }
    }
    return wxSASH_NONE;
}

// Draw 3D effect borders
void FlatSashWindow::DrawBorders(wxDC& dc)
{
    int w, h;
    GetClientSize(&w, &h);

    if ( GetWindowStyleFlag() & wxSW_BORDER )
    {
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.SetPen(*wxBLACK_PEN);
        dc.DrawRectangle(0, 0, w-1, h-1);
    }

    dc.SetPen(wxNullPen);
    dc.SetBrush(wxNullBrush);
}

void FlatSashWindow::DrawSashes(wxDC& dc)
{
    int i;
    for (i = 0; i < 4; i++)
        if (m_sashes[i].m_show)
            DrawSash((wxSashEdgePosition) i, dc);
}

// Draw the sash
void FlatSashWindow::DrawSash(wxSashEdgePosition edge, wxDC& dc)
{
    int w, h;
    GetClientSize(&w, &h);

    wxPen facePen(m_faceColour, 1, wxPENSTYLE_SOLID);
    wxBrush faceBrush(m_faceColour, wxBRUSHSTYLE_SOLID);

    if ( edge == wxSASH_LEFT || edge == wxSASH_RIGHT )
    {
        int sashPosition = (edge == wxSASH_LEFT) ? 0 : ( w - GetEdgeMargin(edge) );

        dc.SetPen(facePen);
        dc.SetBrush(faceBrush);
        dc.DrawRectangle(sashPosition, 0, GetEdgeMargin(edge), h);
      
    }
    else // top or bottom
    {
        int sashPosition = (edge == wxSASH_TOP) ? 0 : ( h - GetEdgeMargin(edge) );

        dc.SetPen(facePen);
        dc.SetBrush(faceBrush);
        dc.DrawRectangle(0, sashPosition, w, GetEdgeMargin(edge));
    }

    dc.SetPen(wxNullPen);
    dc.SetBrush(wxNullBrush);
}

// Draw the sash tracker (for whilst moving the sash)
void FlatSashWindow::DrawSashTracker(wxSashEdgePosition edge, int x, int y)
{

    int w, h;
    GetClientSize(&w, &h);

    wxScreenDC screenDC;
    int x1, y1;
    int x2, y2;

    if ( edge == wxSASH_LEFT || edge == wxSASH_RIGHT )
    {
        x1 = x; y1 = 2;
        x2 = x; y2 = h-2;

        if ( (edge == wxSASH_LEFT) && (x1 > w) )
        {
            x1 = w; x2 = w;
        }
        else if ( (edge == wxSASH_RIGHT) && (x1 < 0) )
        {
            x1 = 0; x2 = 0;
        }
    }
    else
    {
        x1 = 2; y1 = y;
        x2 = w-2; y2 = y;

        if ( (edge == wxSASH_TOP) && (y1 > h) )
        {
            y1 = h;
            y2 = h;
        }
        else if ( (edge == wxSASH_BOTTOM) && (y1 < 0) )
        {
            y1 = 0;
            y2 = 0;
        }
    }

    ClientToScreen(&x1, &y1);
    ClientToScreen(&x2, &y2);

    wxPen sashTrackerPen(*wxBLACK, 2, wxPENSTYLE_SOLID);

    screenDC.SetLogicalFunction(wxINVERT);
    screenDC.SetPen(sashTrackerPen);
    screenDC.SetBrush(*wxTRANSPARENT_BRUSH);

    screenDC.DrawLine(x1, y1, x2, y2);

    screenDC.SetLogicalFunction(wxCOPY);

    screenDC.SetPen(wxNullPen);
    screenDC.SetBrush(wxNullBrush);
	
}

// Position and size subwindows.
// Note that the border size applies to each subwindow, not
// including the edges next to the sash.
void FlatSashWindow::SizeWindows()
{
	wxClientDC dc(this);
    DrawBorders(dc);
    DrawSashes(dc);
}

// Initialize colours
void FlatSashWindow::InitColours()
{
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	m_faceColour = clrs->Get(ColourScheme::STATIC_LINE);
}

void FlatSashWindow::SetSashVisible(wxSashEdgePosition edge, bool sash)
{
     m_sashes[edge].m_show = sash;
     if (sash)
        m_sashes[edge].m_margin = m_borderSize;
     else
        m_sashes[edge].m_margin = 0;
}

#if defined( __WXMSW__ ) || defined( __WXMAC__)

// this is currently called (and needed) under MSW only...
void FlatSashWindow::OnSetCursor(wxSetCursorEvent& event)
{
    // if we don't do it, the resizing cursor might be set for child window:
    // and like this we explicitly say that our cursor should not be used for
    // children windows which overlap us

    if ( SashHitTest(event.GetX(), event.GetY()) != wxSASH_NONE)
    {
        // default processing is ok
        event.Skip();
    }
    //else: do nothing, in particular, don't call Skip()
}

#endif // __WXMSW__ || __WXMAC__

