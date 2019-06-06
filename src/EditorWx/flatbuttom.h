#pragma once

class FlatButtom :
	public wxWindow
{
	enum { statusNone, statusHover, statusPressed };
public:
	FlatButtom(wxWindow *parent, int Id, wxString text);
	~FlatButtom();
public:
	void SetBitmap(const wxBitmap& bitmap);

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
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);
	virtual void DoClick();
private:
	void SetBestClientSize();
	void DrawBorder(wxDC&  dc, const wxRect &rc);
	void DrawBackground(wxDC&  dc, const wxRect &rc);
	void DrawLabel(wxDC&  dc, const wxRect &rc);
	void DrawBitmap(wxDC&  dc, const wxRect &rc);
private:
	int  m_status;
	wxString m_text;
	wxBitmap m_bitmap;
	int m_marginBmpX;
	int m_marginBmpY;
	DECLARE_EVENT_TABLE()
};

