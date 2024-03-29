#pragma once

#include <map>

#define FB_LABEL_LEFT   0x000000
#define FB_LABEL_RIGHT  0x000001
#define FB_LABEL_CENTER 0x000002
#define FB_BITMAP_LEFT	0x000004
#define FB_BITMAP_RIGHT 0x000008
#define FB_TRANSPARENT	0x000010
#define FB_CHECKED		0x000020


class FlatButton :
	public wxWindow
{
	enum { statusNone, statusHover, statusPressed };
public:
	enum ColourIndex {	BackgroundColour = 0, HoverBackgroundColour, PressBackgroundColour, 
						ForegroundColour, HoverForegroundColour, PressForegroundColour, 
						BackgroundColourActive, HoverBackgroundColourActive, PressBackgroundColourActive, 
						ForegroundColourActive, HoverForegroundColourActive, PressForegroundColourActive,
						BorderColour, ColourNum };

public:
	FlatButton(wxWindow *parent, int Id, const wxString &text, int style = FB_BITMAP_RIGHT| FB_LABEL_LEFT, const wxString& idArt = wxEmptyString );
	~FlatButton();
public:
	void SetBitmap(const wxBitmap& bitmap, int spacer = 0);
	void SetBitmap(const wxBitmap& bitmap, const wxBitmap& bitmaphover, int spacer = 0);
	void SetBitmap(const wxString& id, int spacer = 0);
	void paintEvent(wxPaintEvent & evt);
	void paintNow();
	void render(wxDC& dc);
	// some useful events
	void OnSize(wxSizeEvent& event);
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
	void UpdateSize() { SetBestClientSize(); }
	void SetChecked(bool checked);
	void UpdateThemeColor();
	
private:
	void Init();
	void SetBestClientSize();
	void CalcGeometry(const wxRect &rcIn, wxRect &rcLabel, wxPoint &ptButmap);
	void DrawBackground(wxDC&  dc, const wxRect &rc);
	void DrawLabel(wxDC&  dc, const wxRect &rc);
	void DrawBitmap(wxDC&  dc, const wxPoint &pt);
	void DoEnable(bool enable);

private:
	int  m_status;
	wxString m_text;
	wxBitmap m_bitmap;
	wxBitmap m_bitmap_hover;
	wxBitmap m_bitmap_disabled;
	int m_marginX;
	int m_marginY;
	int m_cmd;
	int m_spacer;
	int m_style;
	wxString m_idArt;

	bool m_captured;
	std::vector<wxColor>  m_colors;
	
	DECLARE_EVENT_TABLE()
};

