#include "wx/wx.h"
#include "them.h"
#include "prefs.h"
#include "wx\univ\colschem.h"
#include "wx/aui/auibook.h"
#include "wx/jsonreader.h"
#include "standartpaths.h"
#include <wx/wfstream.h>

#include "bitmaps/file_new.xpm"


static const unsigned char close_bits[] = {
	 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xFE, 0x03, 0xF8, 0x01, 0xF0, 0x19, 0xF3,
	 0xB8, 0xE3, 0xF0, 0xE1, 0xE0, 0xE0, 0xF0, 0xE1, 0xB8, 0xE3, 0x19, 0xF3,
	 0x01, 0xF0, 0x03, 0xF8, 0x0F, 0xFE, 0xFF, 0xFF };

static const unsigned char left_bits[] = {
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xfe, 0x3f, 0xfe,
   0x1f, 0xfe, 0x0f, 0xfe, 0x1f, 0xfe, 0x3f, 0xfe, 0x7f, 0xfe, 0xff, 0xfe,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

static const unsigned char right_bits[] = {
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0x9f, 0xff, 0x1f, 0xff,
   0x1f, 0xfe, 0x1f, 0xfc, 0x1f, 0xfe, 0x1f, 0xff, 0x9f, 0xff, 0xdf, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

static const unsigned char list_bits[] = {
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x0f, 0xf8, 0xff, 0xff, 0x0f, 0xf8, 0x1f, 0xfc, 0x3f, 0xfe, 0x7f, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };


#include "bitmaps/stop.xpm"

wxBitmap wxAuiBitmapFromBits(const unsigned char bits[], int w, int h,	const wxColour& color);

//const char *const stop_xpm[];

const char* const *GetBitmapColor(const char* const* xpm_data, const wxColor &clr)
{
	static char *xpmData1[124];
	static  char pp[32];// = "  c #FF0000";
	int count;
	unsigned width, height, colors_cnt, chars_per_pixel;
	count = sscanf(xpm_data[0], "%u %u %u %u",
		&width, &height, &colors_cnt, &chars_per_pixel);
	if (count != 4 || width * height * colors_cnt == 0)
	{
		return xpm_data;
	}
	int n = height + colors_cnt + 1;
	if (n  >= 124 ) // very big
		return xpm_data;

	sprintf(pp, "  c %s", clr.GetAsString().c_str().AsChar());
	
	
	for(unsigned i = 0; i < n; i++ )
		xpmData1[i] = (char *)(xpm_data[i]);

	xpmData1[1] = pp;
	return xpmData1;
}

wxBitmap ExArtProvider::CreateBitmap(const wxArtID& id, const wxArtClient& client, const wxSize& size)
{

	ColourScheme *clrs = Preferences::Get()->GetColorScheme();	
	
		
#define wxART_MENU                 wxART_MAKE_CLIENT_ID(wxART_MENU)
#define wxART_FRAME_ICON           wxART_MAKE_CLIENT_ID(wxART_FRAME_ICON)

#define wxART_CMN_DIALOG           wxART_MAKE_CLIENT_ID(wxART_CMN_DIALOG)
#define wxART_HELP_BROWSER         wxART_MAKE_CLIENT_ID(wxART_HELP_BROWSER)
#define wxART_MESSAGE_BOX          wxART_MAKE_CLIENT_ID(wxART_MESSAGE_BOX)
#define wxART_BUTTON               wxART_MAKE_CLIENT_ID(wxART_BUTTON)
#define wxART_LIST                 wxART_MAKE_CLIENT_ID(wxART_LIST)

	if (id == wxART_NEW)
	{
		wxColor clr;
		
		if (client == wxART_MENU)
		{
			clr = *wxRED;
		}
		else if (client == wxART_LIST)
		{
			clr = *wxYELLOW;
		}
		if ( clr.IsOk() )
			return wxBitmap(GetBitmapColor(file_new_xpm, clr));
		else
			return wxBitmap(file_new_xpm);

	}
	else
		return wxArtProvider::CreateBitmap(id, client, size);
}



ThemArtProvider::ThemArtProvider() : wxAuiDefaultDockArt() 
{ 
	UpdateColoursFromSystem();
}

ThemArtProvider::~ThemArtProvider() 
{ 
}


void ThemArtProvider::UpdateColoursFromSystem()
{

	ColourScheme *clrs = Preferences::Get()->GetColorScheme();

	wxColor baseColour = clrs->Get(ColourScheme::FRAME);

	// the baseColour is too pale to use as our base colour,
	// so darken it a bit --
	if ((255 - baseColour.Red()) +
		(255 - baseColour.Green()) +
		(255 - baseColour.Blue()) < 60)
	{
		baseColour = baseColour.ChangeLightness(92);
	}

	m_baseColour = clrs->Get(ColourScheme::FRAME);;
	wxColor darker1Colour = baseColour.ChangeLightness(85);
	wxColor darker2Colour = baseColour.ChangeLightness(75);
	wxColor darker3Colour = baseColour.ChangeLightness(60);
	//wxColor darker4Colour = baseColour.ChangeLightness(50);
	wxColor darker5Colour = baseColour.ChangeLightness(40);

	m_activeCaptionColour = clrs->Get(ColourScheme::TITLEBAR_ACTIVE);
	m_activeCaptionGradientColour = clrs->Get(ColourScheme::TITLEBAR_ACTIVE);
	m_activeCaptionTextColour = clrs->Get(ColourScheme::TITLEBAR_ACTIVE_TEXT);
	m_inactiveCaptionColour = clrs->Get(ColourScheme::TITLEBAR);
	m_inactiveCaptionGradientColour = clrs->Get(ColourScheme::TITLEBAR);
	m_inactiveCaptionTextColour = clrs->Get(ColourScheme::TITLEBAR_TEXT);

	m_sashBrush = wxBrush(baseColour);
	m_backgroundBrush = wxBrush(baseColour);
	m_gripperBrush = wxBrush(baseColour);

	m_borderPen = wxPen(clrs->Get(ColourScheme::BORDER));
	int pen_width = wxWindow::FromDIP(1, NULL);
	m_gripperPen1 = wxPen(darker5Colour, pen_width);
	m_gripperPen2 = wxPen(darker3Colour, pen_width);
	m_gripperPen3 = wxPen(*wxStockGDI::GetColour(wxStockGDI::COLOUR_WHITE), pen_width);
	InitBitmaps();
}


EditorTabArt::EditorTabArt() 	
{
	UpdateColoursFromSystem();
}
EditorTabArt::~EditorTabArt()
{
}

EditorTabArt *EditorTabArt::Clone()
{
	return new EditorTabArt(*this);
}

int EditorTabArt::GetBorderWidth(wxWindow* )
{
	return 1;
}



void EditorTabArt::DrawTab(wxDC& dc, wxWindow* wnd,
	const wxAuiNotebookPage& page,
	const wxRect& in_rect,
	int close_button_state,
	wxRect* out_tab_rect,
	wxRect* out_button_rect,
	int* x_extent)

{
	if (page.active)
	{
		dc.SetTextForeground(Preferences::Get()->GetStdColor(ColourScheme::TITLEBAR_ACTIVE_TEXT));
	}
	else
	{
		dc.SetTextForeground(Preferences::Get()->GetStdColor(ColourScheme::TITLEBAR_TEXT));
	}

	wxAuiGenericTabArt::DrawTab(dc, wnd, page, in_rect, close_button_state,
		out_tab_rect, out_button_rect, x_extent);

}

void EditorTabArt::DrawBackground(wxDC& dc, wxWindow* wnd, const wxRect& rect)
{
	wxAuiGenericTabArt::DrawBackground(dc, wnd, rect);
}

int  EditorTabArt::GetBestTabCtrlSize(wxWindow* wnd, const wxAuiNotebookPageArray& pages, const wxSize& requiredBmpSize) 
{
	return  wxAuiGenericTabArt::GetBestTabCtrlSize(wnd, pages, requiredBmpSize);
}

void EditorTabArt::DrawButton(wxDC& dc, wxWindow* wnd, const wxRect& inRect, int bitmapId, int buttonState, int orientation, wxRect* outRect)
{
	wxAuiGenericTabArt::DrawButton(dc, wnd, inRect, bitmapId, buttonState, orientation, outRect);	
	/*
	wxRect rc(inRect);
	rc.width /= 2;
	wxColor clr(*wxYELLOW);
	//Draw background
	dc.SetBrush(wxBrush(clr));
	dc.SetPen(*wxTRANSPARENT_PEN);
	dc.DrawRectangle(rc);
	*/
}


wxSize EditorTabArt::GetTabSize(wxDC& dc, wxWindow* wnd, const wxString& caption, const wxBitmap& bitmap, bool active, int closeButtonState, int* xExtent)
{
	wxSize sz = wxAuiGenericTabArt::GetTabSize(dc, wnd, caption, bitmap, active, closeButtonState, xExtent);
	return sz;
}

void EditorTabArt::DrawBorder(wxDC& dc, wxWindow* wnd, const wxRect& rect)
{
	wxAuiGenericTabArt::DrawBorder(dc, wnd, rect);
}


void EditorTabArt::UpdateColoursFromSystem()
{

	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	m_baseColour = clrs->Get(ColourScheme::FRAME);
	m_activeColour = clrs->Get(ColourScheme::WINDOW);
	m_borderPen = wxPen(clrs->Get(ColourScheme::WINDOW));
	
	//m_baseColourPen = wxPen(m_baseColour);
	//m_baseColourBrush = wxBrush(m_baseColour);
	m_baseColourBrush = wxBrush(m_activeColour);
	m_baseColourPen = wxPen(m_activeColour);

	wxColor clrBtn(clrs->Get(ColourScheme::WINDOW_TEXT));

	m_activeCloseBmp = wxAuiBitmapFromBits(close_bits, 16, 16, clrBtn);
	m_disabledCloseBmp = wxAuiBitmapFromBits(close_bits, 16, 16, wxColour(128, 128, 128));

	m_activeLeftBmp = wxAuiBitmapFromBits(left_bits, 16, 16, clrBtn);
	m_activeRightBmp = wxAuiBitmapFromBits(right_bits, 16, 16, clrBtn);
	m_activeWindowListBmp = wxAuiBitmapFromBits(list_bits, 16, 16, clrBtn);
	
}




ColourScheme::ColourScheme()
	:m_inited(false)
{}

ColourScheme::~ColourScheme()
{}

const wxColour &ColourScheme::Get(ColourScheme::StdColour col)
{
	if (!m_inited)
	{
		InitDef();
		Read();
		m_inited = true;
	}
	return m_colors[col];
}

void ColourScheme::SetFileName(const wxString &filename)
{
	m_filename = filename;
	m_inited = false;
	m_colors.clear();
}

inline  void ReadColor(wxJSONValue  &val, wxColor &clr)
{
	if (val.IsString())
	{
		clr = val.AsString();
	}
}

void ColourScheme::Read()
{

	if (m_filename.empty())
		return;

	wxString fileName(StandartPaths::Get()->GetPreferencesPath(m_filename).c_str());

	wxLogNull logNo;
	wxFFileInputStream  file_stream(fileName);
	if (!file_stream.IsOk())
	{
		wxString msg = wxString::Format(_("Can not open file %s"), fileName);
		wxMessageBox(msg, _("Error opening file"));
		return;
	}

	wxJSONReader reader;
	wxJSONValue root;
	// now read the JSON text and store it in the 'root' structure
  // check for errors before retreiving values...
	int numErrors = reader.Parse(file_stream, &root);
	if (numErrors > 0)
	{
		const wxArrayString& errors = reader.GetErrors();
		wxString msg = wxString::Format(_("Error parsing file %s\n"), fileName);
		for (auto p = errors.begin(); p != errors.end(); ++p)
		{
			msg += *p;
			msg += L"\n";
		}
		wxMessageBox(msg, _("Error parsing file"));
		return;
	}

	ReadColor( root["frame"], m_colors[FRAME]);
	ReadColor(root["window"],m_colors[WINDOW]);
	ReadColor(root["window_txt"], m_colors[WINDOW_TEXT]);
	ReadColor(root["linenumber"], m_colors[LINENUMBER]);
	ReadColor(root["linenumber_txt"], m_colors[LINENUMBER_TEXT]);
	ReadColor(root["calltip"], m_colors[CALLTIP]);
	ReadColor(root["calltip_txt"], m_colors[CALLTIP_TEXT]);
	ReadColor(root["ctrl"],m_colors[CONTROL]);
	ReadColor(root["ctrl_pressed"],m_colors[CONTROL_PRESSED]);
	ReadColor(root["ctrl_hover"],m_colors[CONTROL_HOVER]);
	ReadColor(root["ctrl_text"],m_colors[CONTROL_TEXT]);
	ReadColor(root["ctrl_text_dis"],m_colors[CONTROL_TEXT_DISABLED]);
	ReadColor(root["scrollbar"],m_colors[SCROLLBAR]);
	ReadColor(root["scrollbar_tubm"],m_colors[SCROLLBAR_TUMB]);
	ReadColor(root["scrollbar_tumb_hvr"], m_colors[SCROLLBAR_TUMB_HOVER]);	
	ReadColor(root["highlight"],m_colors[HIGHLIGHT]);
	ReadColor(root["highlight_txt"],m_colors[HIGHLIGHT_TEXT]);
	ReadColor(root["titlebar"],m_colors[TITLEBAR]);
	ReadColor(root["titlebar_active"],m_colors[TITLEBAR_ACTIVE]);
	ReadColor(root["titlebar_txt"],m_colors[TITLEBAR_TEXT]);
	ReadColor(root["titlebar_txt_active"],m_colors[TITLEBAR_ACTIVE_TEXT]);
	ReadColor(root["slider_shaft"], m_colors[SLIDER_SHAFT]);
	ReadColor(root["slider_shaft_colored"],m_colors[SLIDER_SHAFT_COLORED]);
	ReadColor(root["border"],m_colors[BORDER]);
}


void ColourScheme::InitDef()
{
	m_colors.resize(StdColour::MAX);
	m_colors[FRAME] = wxColor(0,0,0);
	// the background colour for a window
	m_colors[WINDOW] = wxColor(0, 0, 0);
	m_colors[WINDOW_TEXT] = wxColor(0xFFFFFF);
	m_colors[LINENUMBER] = wxColor(32, 32, 32);
	m_colors[LINENUMBER_TEXT] = wxColor(192, 192, 192);
	m_colors[CALLTIP] = wxColor(0, 255, 255);
	m_colors[CALLTIP_TEXT]= wxColor(192, 192, 192);
		// the different background and text colours for the control
	m_colors[CONTROL] = wxColour(0xe0e0e0);
	m_colors[CONTROL_PRESSED] = wxColour(0xe0e000);
	m_colors[CONTROL_HOVER] = wxColour(0x00e000);
	// the label text for the normal and the disabled state
	m_colors[CONTROL_TEXT] = wxColour(0xFFFFFF);
	m_colors[CONTROL_TEXT_DISABLED] = m_colors[CONTROL_TEXT].MakeDisabled();	
		// the scrollbar background colour for the normal and pressed states
	m_colors[SCROLLBAR] = m_colors[WINDOW].ChangeLightness(25);
	m_colors[SCROLLBAR_TUMB] = m_colors[WINDOW].ChangeLightness(50);
	m_colors[SCROLLBAR_TUMB_HOVER] = m_colors[WINDOW].ChangeLightness(80);
	// the background and text colour for the highlighted item
	m_colors[HIGHLIGHT] = m_colors[WINDOW].ChangeLightness(25);;
	m_colors[HIGHLIGHT_TEXT] = m_colors[CONTROL_TEXT];

		// the titlebar background colours for the normal and focused states
	m_colors[TITLEBAR] = wxColour(0xe0e0e0); 
	m_colors[TITLEBAR_ACTIVE] = wxColour(0xe00000);
		// the titlebar text colours
	m_colors[TITLEBAR_TEXT] = m_colors[CONTROL_TEXT];
	m_colors[TITLEBAR_ACTIVE_TEXT] = m_colors[CONTROL_TEXT];

	m_colors[SLIDER_SHAFT] = wxColour(0xdddddd);
	m_colors[SLIDER_SHAFT_COLORED] = wxColour(0xcc8830);

		// border
	m_colors[BORDER] = wxColour(0xFF0000);
}
