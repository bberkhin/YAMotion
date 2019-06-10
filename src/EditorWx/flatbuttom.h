#pragma once

#include <map>

class FlatButton :
	public wxWindow
{
	enum { statusNone, statusHover, statusPressed };
public:
	FlatButton(wxWindow *parent, int Id, wxString text, int cmd = -1);
	~FlatButton();
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
	void SetCustomColor(int clrIn, int clOut);
private:
	void SetBestClientSize();
	void DrawBackground(wxDC&  dc, const wxRect &rc);
	void DrawLabel(wxDC&  dc, const wxRect &rc);
	void DrawBitmap(wxDC&  dc, const wxRect &rc);
	wxColor GetButtonColor(int clr);

private:
	int  m_status;
	wxString m_text;
	wxBitmap m_bitmap;
	int m_marginBmpX;
	int m_marginBmpY;
	int m_cmd;
	bool m_captured;
	std::map< int, int> m_colors;
	DECLARE_EVENT_TABLE()
};

