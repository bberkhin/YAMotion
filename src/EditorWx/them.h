#pragma once

#include "wx/aui/framemanager.h"
#include "wx/aui/dockart.h"
#include "wx/univ/theme.h"
#include "wx/aui/tabart.h"
#include "wx/artprov.h"

#define ART_MENUHOVER 				    wxART_MAKE_CLIENT_ID(ART_MENUHOVER)
#define ART_MENUDISABLED				wxART_MAKE_CLIENT_ID(ART_MENUDISABLED)
#define ART_PREFERENCES                 wxART_MAKE_CLIENT_ID(ART_PREFERENCES)
#define ART_MAIL						wxART_MAKE_CLIENT_ID(ART_MAIL)
#define ART_UPDATE						wxART_MAKE_CLIENT_ID(ART_UPDATE)
#define ART_VERIFY						wxART_MAKE_CLIENT_ID(ART_VERIFY)
#define ART_CLOSE						wxART_MAKE_CLIENT_ID(ART_CLOSE)
#define ART_CONVERT						wxART_MAKE_CLIENT_ID(ART_CONVERT)
#define ART_DRAW3D						wxART_MAKE_CLIENT_ID(ART_DRAW3D)

#define ART_PAUSE						wxART_MAKE_CLIENT_ID(ART_PAUSE)
#define ART_PLAY						wxART_MAKE_CLIENT_ID(ART_PLAY)
#define ART_STOP						wxART_MAKE_CLIENT_ID(ART_STOP)
#define ART_ADD							wxART_MAKE_CLIENT_ID(ART_ADD)




class ExArtProvider : public wxArtProvider
{
public:
	ExArtProvider() : wxArtProvider() { }
	~ExArtProvider() { }
protected:
	virtual wxBitmap CreateBitmap(const wxArtID& id, const wxArtClient& client, const wxSize& size) wxOVERRIDE;

};


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
		WINDOW_HOVER,
		WINDOW_TEXT,
		WINDOW_TEXT_HOVER,
		WINDOW_TEXT_DISABLE,
		WINDOW_3DVIEW,

		LINENUMBER,
		LINENUMBER_TEXT,

		CALLTIP,
		CALLTIP_TEXT,
		
		BITMAP_CMD, //close button for example
		BITMAP_CMD_HOVER, //close button
		BITMAP_CMD_DISABLED,
		// the different background and text colours for the control
		CONTROL,
		CONTROL_PRESSED,
		CONTROL_HOVER,
		// the label text for the normal and the disabled state
		CONTROL_TEXT,
		CONTROL_TEXT_HOVER,
		CONTROL_TEXT_DISABLED,
		// the scrollbar background colour for the normal and pressed states

		BUTTON_FEEDBACK,
		BUTTON_FEEDBACK_HOVER,
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
		
		SLIDER_SHAFT,
		SLIDER_SHAFT_COLORED,

		BITMAP_NEW_LIST,
		STATIC_LINE,
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