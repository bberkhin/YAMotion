#pragma once
#include "C:\wxWidgets\include\wx\motif\window.h"
class FlatButtom :
	public wxWindow
{
public:
	FlatButtom(wxWindow *parent, int Id, wxString text);
	~FlatButtom();
public:
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
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);
private:
		bool m_pressedDown;
		wxString m_text;

		static const int buttonWidth = 200;
		static const int buttonHeight = 50;

DECLARE_EVENT_TABLE()
};

