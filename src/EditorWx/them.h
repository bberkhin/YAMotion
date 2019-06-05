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
//	void DrawButton( wxDC& dc, wxWindow* wnd, const wxRect& inRect,	int bitmapId, int buttonState, int orientation,	wxRect* outRect) wxOVERRIDE;
//	int GetIndentSize() wxOVERRIDE;
	int GetBorderWidth(	wxWindow* wnd) wxOVERRIDE;
//	int GetAdditionalBorderSpace(wxWindow* wnd) wxOVERRIDE;
	wxSize GetTabSize( wxDC& dc, wxWindow* wnd, const wxString& caption, const wxBitmap& bitmap,
		bool active, int closeButtonState, int* xExtent) wxOVERRIDE;
//	int ShowDropDown( wxWindow* wnd, const wxAuiNotebookPageArray& items, int activeIdx) wxOVERRIDE;
//	int GetBestTabCtrlSize(wxWindow* wnd, const wxAuiNotebookPageArray& pages,	const wxSize& requiredBmpSize) wxOVERRIDE;
protected:
	virtual void UpdateColoursFromSystem() wxOVERRIDE;
private:
	int m_maxTabHeight_;


};


//WX_USE_THEME(Win32);