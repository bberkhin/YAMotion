#include "wx/wx.h"
#include "them.h"
#include "wx\univ\colschem.h"

//#include "wx/aui/auibook.h"
//#include "wx/aui/tabart.h"
//#include "wx/settings.h"
//#include "wx/dcclient.h"
//#include "wx/image.h"


//WX_USE_THEME_IMPL(Win32);  


ThemArtProvider::ThemArtProvider() : wxAuiDefaultDockArt() 
{ 
	UpdateColoursFromSystem();
}

ThemArtProvider::~ThemArtProvider() 
{ 
}


void ThemArtProvider::UpdateColoursFromSystem()
{
	wxColor baseColour = wxColor(0, 0, 0);

	// the baseColour is too pale to use as our base colour,
	// so darken it a bit --
	if ((255 - baseColour.Red()) +
		(255 - baseColour.Green()) +
		(255 - baseColour.Blue()) < 60)
	{
		baseColour = baseColour.ChangeLightness(92);
	}

	m_baseColour = baseColour;
	wxColor darker1Colour = baseColour.ChangeLightness(85);
	wxColor darker2Colour = baseColour.ChangeLightness(75);
	wxColor darker3Colour = baseColour.ChangeLightness(60);
	//wxColor darker4Colour = baseColour.ChangeLightness(50);
	wxColor darker5Colour = baseColour.ChangeLightness(40);

	m_activeCaptionColour = *wxBLACK;;
	m_activeCaptionGradientColour = m_activeCaptionColour;
	m_activeCaptionTextColour = *wxWHITE;;
	m_inactiveCaptionColour = *wxBLACK;
	m_inactiveCaptionGradientColour = baseColour.ChangeLightness(97);
	m_inactiveCaptionTextColour = *wxWHITE;;

	m_sashBrush = wxBrush(baseColour);
	m_backgroundBrush = wxBrush(baseColour);
	m_gripperBrush = wxBrush(baseColour);

	//m_borderPen = wxPen(wxColor(128,128,128));
	m_borderPen = wxPen(wxColor(255, 0, 0));
	int pen_width = wxWindow::FromDIP(1, NULL);
	m_gripperPen1 = wxPen(darker5Colour, pen_width);
	m_gripperPen2 = wxPen(darker3Colour, pen_width);
	m_gripperPen3 = wxPen(*wxStockGDI::GetColour(wxStockGDI::COLOUR_WHITE), pen_width);
	InitBitmaps();
}



// ----------------------------------------------------------------------------
// wxWin32ColourScheme: uses (default) Win32 colours
// ----------------------------------------------------------------------------

class YAColourScheme : public wxColourScheme
{
public:
	virtual wxColour Get(StdColour col) const;
	virtual wxColour GetBackground(wxWindow *win) const;
};



// ============================================================================
// wxWin32ColourScheme
// ============================================================================

wxColour YAColourScheme::GetBackground(wxWindow *win) const
{
	wxColour col(*wxBLACK);
//	if (win->UseBgCol())
//	{
//		// use the user specified colour
//		col = win->GetBackgroundColour();
//	}
//
//	if (!win->ShouldInheritColours())
//	{
//#if wxUSE_TEXTCTRL
//		wxTextCtrl *text = wxDynamicCast(win, wxTextCtrl);
//#endif // wxUSE_TEXTCTRL
//#if wxUSE_LISTBOX
//		wxListBox* listBox = wxDynamicCast(win, wxListBox);
//#endif // wxUSE_LISTBOX
//
//#if wxUSE_TEXTCTRL
//		if (text
//#if wxUSE_LISTBOX
//			|| listBox
//#endif
//			)
//		{
//			if (!win->IsEnabled()) // not IsEditable()
//				col = Get(CONTROL);
//			else
//			{
//				if (!col.IsOk())
//				{
//					// doesn't depend on the state
//					col = Get(WINDOW);
//				}
//			}
//		}
//#endif // wxUSE_TEXTCTRL
//
//		if (!col.IsOk())
//			col = Get(CONTROL); // Most controls should be this colour, not WINDOW
//	}
//	else
//	{
//		int flags = win->GetStateFlags();
//
//		// the colour set by the user should be used for the normal state
//		// and for the states for which we don't have any specific colours
//		if (!col.IsOk() || (flags & wxCONTROL_PRESSED) != 0)
//		{
//#if wxUSE_SCROLLBAR
//			if (wxDynamicCast(win, wxScrollBar))
//				col = Get(flags & wxCONTROL_PRESSED ? SCROLLBAR_PRESSED
//					: SCROLLBAR);
//			else
//#endif // wxUSE_SCROLLBAR
//				col = Get(CONTROL);
//		}
//	}
//
	return col;
}

wxColour YAColourScheme::Get(YAColourScheme::StdColour col) const
{
	switch (col)
	{
		// use the system colours under Windows
		// use the standard Windows colours elsewhere
	case WINDOW:            return *wxBLACK; //*wxWHITE;

	case CONTROL_PRESSED:    return wxColour(0x00FF00); //wxColour(0xc0c0c0);
	case CONTROL_CURRENT:    return wxColour(0xFF0000);
	case CONTROL:           return wxColour(0x0000FF); //wxColour(0xc0c0c0);

	case CONTROL_TEXT:      return *wxWHITE;

	case SCROLLBAR:         return *wxYELLOW; //wxColour(0xe0e0e0);
	case SCROLLBAR_PRESSED: return *wxRED; //*wxBLACK;

	case HIGHLIGHT:         return wxColour(0xe0e0e0);// wxColour(0x800000);
	case HIGHLIGHT_TEXT:    return  *wxBLACK; //wxColour(0x000000);

	case SHADOW_DARK:       return *wxBLACK;

	case CONTROL_TEXT_DISABLED:return wxColour(0xe0e0e0);
	case SHADOW_HIGHLIGHT:  return wxColour(0xffffff);

	case SHADOW_IN:         return wxColour(0xc0c0c0);

	case CONTROL_TEXT_DISABLED_SHADOW:
	case SHADOW_OUT:        return wxColour(0x7f7f7f);

	case TITLEBAR:          return wxColour(0xaeaaae);
	case TITLEBAR_ACTIVE:   return wxColour(0x820300);
	case TITLEBAR_TEXT:     return wxColour(0xc0c0c0);
	case TITLEBAR_ACTIVE_TEXT:return *wxWHITE;

	case DESKTOP:           return wxColour(0x808000);
	case FRAME:             return wxColour(0x808080);
	case GAUGE:             return Get(HIGHLIGHT);
	case MAX:
	default:
		wxFAIL_MSG(wxT("invalid standard colour"));
		return *wxBLACK;
	}
}


/*
class  YATheme : public wxDelegateTheme
{
public:
	YATheme();
	~YATheme();
	virtual wxColourScheme *GetColourScheme();
private:
	wxColourScheme *m_scheme;
};


YATheme::YATheme() 
	: m_scheme(0), wxDelegateTheme("win32")
{
}
YATheme::~YATheme() 
{ 
	delete m_scheme;
}




wxColourScheme *YATheme::GetColourScheme()
{
	if (!m_scheme)
	{
		m_scheme = new YAColourScheme;
	}
	return m_scheme;

}
*/