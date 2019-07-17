#pragma once

#include <wx/wx.h>
#include <wx/sashwin.h>



class FlatSashWindow : public wxWindow
{
public:
    // Default constructor
	FlatSashWindow()
    {
        Init();
    }

    // Normal constructor
	FlatSashWindow(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = wxSW_3D|wxCLIP_CHILDREN, const wxString& name = wxT("sashWindow"))
    {
        Init();
        Create(parent, id, pos, size, style, name);
    }

    virtual ~FlatSashWindow();

    bool Create(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = wxSW_3D|wxCLIP_CHILDREN, const wxString& name = wxT("sashWindow"));

    // Set whether there's a sash in this position
    void SetSashVisible(wxSashEdgePosition edge, bool sash);

    // Get whether there's a sash in this position
    bool GetSashVisible(wxSashEdgePosition edge) const { return m_sashes[edge].m_show; }

    // Get border size
    int GetEdgeMargin(wxSashEdgePosition edge) const { return m_sashes[edge].m_margin; }

    // Sets the default sash border size
    void SetDefaultBorderSize(int width) { m_borderSize = width; }

    // Gets the default sash border size
    int GetDefaultBorderSize() const { return m_borderSize; }

    // Sets the addition border size between child and sash window
    void SetExtraBorderSize(int width) { m_extraBorderSize = width; }

    // Gets the addition border size between child and sash window
    int GetExtraBorderSize() const { return m_extraBorderSize; }

    virtual void SetMinimumSizeX(int min) { m_minimumPaneSizeX = min; }
    virtual void SetMinimumSizeY(int min) { m_minimumPaneSizeY = min; }
    virtual int GetMinimumSizeX() const { return m_minimumPaneSizeX; }
    virtual int GetMinimumSizeY() const { return m_minimumPaneSizeY; }

    virtual void SetMaximumSizeX(int max) { m_maximumPaneSizeX = max; }
    virtual void SetMaximumSizeY(int max) { m_maximumPaneSizeY = max; }
    virtual int GetMaximumSizeX() const { return m_maximumPaneSizeX; }
    virtual int GetMaximumSizeY() const { return m_maximumPaneSizeY; }

////////////////////////////////////////////////////////////////////////////
// Implementation

    // Paints the border and sash
    void OnPaint(wxPaintEvent& event);

    // Handles mouse events
    void OnMouseEvent(wxMouseEvent& ev);

    // Adjusts the panes
    void OnSize(wxSizeEvent& event);

#if defined(__WXMSW__) || defined(__WXMAC__)
    // Handle cursor correctly
    void OnSetCursor(wxSetCursorEvent& event);
#endif // wxMSW

    // Draws borders
    void DrawBorders(wxDC& dc);

    // Draws the sashes
    void DrawSash(wxSashEdgePosition edge, wxDC& dc);

    // Draws the sashes
    void DrawSashes(wxDC& dc);

    // Draws the sash tracker (for whilst moving the sash)
    void DrawSashTracker(wxSashEdgePosition edge, int x, int y);

    // Tests for x, y over sash
    wxSashEdgePosition SashHitTest(int x, int y, int tolerance = 2);

    // Resizes subwindows
    void SizeWindows();

    // Initialize colours
    void InitColours();

private:
    void Init();

    wxSashEdge  m_sashes[4];
    int         m_dragMode;
    wxSashEdgePosition m_draggingEdge;
    int         m_oldX;
    int         m_oldY;
    int         m_borderSize;
    int         m_extraBorderSize;
    int         m_firstX;
    int         m_firstY;
    int         m_minimumPaneSizeX;
    int         m_minimumPaneSizeY;
    int         m_maximumPaneSizeX;
    int         m_maximumPaneSizeY;
    wxCursor*   m_sashCursorWE;
    wxCursor*   m_sashCursorNS;
    wxColour    m_faceColour;
    bool        m_mouseCaptured;
    wxCursor*   m_currentCursor;

private:
    wxDECLARE_DYNAMIC_CLASS(FlatSashWindow);
    wxDECLARE_EVENT_TABLE();
    wxDECLARE_NO_COPY_CLASS(FlatSashWindow);
};

