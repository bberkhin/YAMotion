#pragma once

class FlatScrollBar :
	public wxWindow
{
public:
	enum { statusNone, statusHover, statusPressed };
	enum { typeVertical, typeHorisontal };
	enum { Element_None, Element_Thumb, Element_Bar_1, Element_Bar_2 };
	
public:
	FlatScrollBar(wxWindow *parent, int id, int type = typeVertical);
	virtual ~FlatScrollBar();

	int GetThumbPosition() const;
	int GetThumbSize() const { return m_thumbSize; }
	int GetPageSize() const { return m_pageSize; }
	int GetRange() const { return m_range; }

	virtual void SetThumbPosition(int viewStart) ;
	virtual void SetScrollbar(int position, int thumbSize, int range, int pageSize,	bool refresh = true);
	bool IsVertical() const {	return (m_type == typeVertical);	}

	void paintEvent(wxPaintEvent & evt);
	void paintNow();
	void render(wxDC& dc);

	// some useful events
	void mouseMoved(wxMouseEvent& event);
	void mouseDown(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	void rightClick(wxMouseEvent& event);
	void mouseLeftWindow(wxMouseEvent& event);
	void mouseEnterWindow(wxMouseEvent& event);

protected:
	//virtual wxSize DoGetBestSize() const wxOVERRIDE;
	void SetBestClientSize();
	wxRect  GetScrollbarRect(int elem = Element_Thumb, int thumbPos = -1 );
	void DoSetThumb(int pos);
	int HitTestBar(const wxPoint& pt);
	wxCoord GetMouseCoord(const wxMouseEvent& event) const;
	int PixelToScrollbar(wxCoord coord);
	wxCoord ScrollbarToPixel(int thumbPos = -1);
	wxCoord GetScrollbarSize() const;
	bool PerformAction(const wxString& action, long numArg = 0, const wxString& strArg = wxEmptyString);
protected:
	int m_status;
	int m_type;

	int m_pageSize;
	int m_thumbPos;
	int m_range;
	int m_thumbSize;
	int m_thumbPosOld;
	bool m_dirty;
	int m_htLast;
	int m_ofsMouse;

	DECLARE_EVENT_TABLE()
};

