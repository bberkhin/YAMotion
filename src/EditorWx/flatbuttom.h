#pragma once

#include <map>

class FlatButton :
	public wxWindow
{
	enum { statusNone, statusHover, statusPressed };
public:
	enum ColourIndex { BackgroundColour = 0, HoverBackgroundColour, PressBackgroundColour, ForegroundColour, HoverForegroundColour, PressForegroundColour, BorderColour, ColourNum };
public:
	FlatButton(wxWindow *parent, int Id, const wxString &text, const wxBitmap &bmp = wxBitmap(), bool setwndcolor = false);
	//FlatButton(wxWindow *parent, int Id, const wxBitmap &bmp, bool setwndcolor = false);
	~FlatButton();
public:
	void SetBitmap(const wxBitmap& bitmap, int spacer = 0, bool placetoright = false);
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
	void SetColour(ColourIndex index, const wxColor &clr) { m_colors[index] = clr; }
	const wxColor &GetColour(ColourIndex index) { return m_colors[index]; }
	void SetSpacer(int sp) { m_spacer = sp; }
	void SetCommand(int cmd) { m_cmd = cmd; }
	void SetMargins(int marginX, int marginY);
private:
	void Init(bool setwndcolor);
	void SetBestClientSize();
	void DrawBackground(wxDC&  dc, const wxRect &rc);
	void DrawLabel(wxDC&  dc, const wxRect &rc);
	void DrawBitmap(wxDC&  dc, const wxRect &rc);

	

private:
	int  m_status;
	wxString m_text;
	wxBitmap m_bitmap;
	int m_marginX;
	int m_marginY;
	int m_cmd;
	int m_spacer;
	bool m_right;

	bool m_captured;
	std::vector<wxColor>  m_colors;
	
	DECLARE_EVENT_TABLE()
};

