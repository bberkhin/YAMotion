#pragma once

#include "wx/aui/framemanager.h"
#include "wx/aui/dockart.h"
#include "wx/univ/theme.h"
#include "wx/aui/tabart.h"




class ThemArtProvider : public wxAuiDefaultDockArt
{
public:
	ThemArtProvider();
	~ThemArtProvider();
	virtual void UpdateColoursFromSystem() wxOVERRIDE;
};


class  EditorTabArt : public wxAuiGenericTabArt
{

public:

	EditorTabArt();
	virtual ~EditorTabArt();

	EditorTabArt * Clone() wxOVERRIDE;
//	void SetSizingInfo(const wxSize& tabCtrlSize, size_t tabCount) wxOVERRIDE;
	void DrawBorder(wxDC& dc, wxWindow* wnd, const wxRect& rect) wxOVERRIDE;
	void DrawBackground(wxDC& dc, wxWindow* wnd, const wxRect& rect) wxOVERRIDE;
	void DrawTab(wxDC& dc, wxWindow* wnd, const wxAuiNotebookPage& pane, const wxRect& inRect, int closeButtonState,
		wxRect* outTabRect,	wxRect* outButtonRect,	int* xExtent) wxOVERRIDE;
	void DrawButton( wxDC& dc, wxWindow* wnd, const wxRect& inRect,	int bitmapId, int buttonState, int orientation,	wxRect* outRect) wxOVERRIDE;
//	int GetIndentSize() wxOVERRIDE;
	int GetBorderWidth(	wxWindow* wnd) wxOVERRIDE;
//	int GetAdditionalBorderSpace(wxWindow* wnd) wxOVERRIDE;
	wxSize GetTabSize( wxDC& dc, wxWindow* wnd, const wxString& caption, const wxBitmap& bitmap,
		bool active, int closeButtonState, int* xExtent) wxOVERRIDE;
//	int ShowDropDown( wxWindow* wnd, const wxAuiNotebookPageArray& items, int activeIdx) wxOVERRIDE;
	int GetBestTabCtrlSize(wxWindow* wnd, const wxAuiNotebookPageArray& pages, const wxSize& requiredBmpSize) wxOVERRIDE;
protected:
	virtual void UpdateColoursFromSystem() wxOVERRIDE;
private:
	
};


class ColourScheme
{
public:
	enum StdColour
	{
		// wxFrame's background colour
		FRAME,
		// the background colour for a window
		WINDOW,
		WINDOW_TEXT,

		LINENUMBER,
		LINENUMBER_TEXT,

		CALLTIP,
		CALLTIP_TEXT,

		// the different background and text colours for the control
		CONTROL,
		CONTROL_PRESSED,
		CONTROL_HOVER,
		// the label text for the normal and the disabled state
		CONTROL_TEXT,
		CONTROL_TEXT_DISABLED,
		// the scrollbar background colour for the normal and pressed states
		SCROLLBAR,
		SCROLLBAR_TUMB,		
		SCROLLBAR_TUMB_HOVER,
		// the background and text colour for the highlighted item
		HIGHLIGHT,
		HIGHLIGHT_TEXT,
		
		// the titlebar background colours for the normal and focused states
		TITLEBAR,
		TITLEBAR_ACTIVE,
		// the titlebar text colours
		TITLEBAR_TEXT,
		TITLEBAR_ACTIVE_TEXT,		
		// border
		BORDER,
		MAX
	};
	
public:
	ColourScheme();
	~ColourScheme();
	const wxColour &Get(ColourScheme::StdColour col);
	void SetFileName(const wxString &filename);
private:
	void Read();
	void InitDef();
private:
	std::vector<wxColour> m_colors;
	wxString m_filename;
	bool m_inited;
};




//WX_USE_THEME(Win32);