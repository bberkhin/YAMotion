#include "wx/wx.h"
#include "them.h"
#include "prefs.h"
#include "wx\univ\colschem.h"
#include "wx/aui/auibook.h"
#include "wx/jsonreader.h"
#include "standartpaths.h"
#include <wx/wfstream.h>

#include "bitmaps/file_new.xpm"
#include "bitmaps/open.xpm"
#include "bitmaps/preferences.xpm"
#include "bitmaps/mail.xpm"
#include "bitmaps/update.xpm"
#include "bitmaps/close.xpm"
#include "bitmaps/verify.xpm"
#include "bitmaps/play.xpm"
#include "bitmaps/pause.xpm"
#include "bitmaps/stop.xpm"
#include "bitmaps/view3d.xpm"
#include "bitmaps/convert.xpm"
#include "bitmaps/add.xpm"
#include "bitmaps/folder.xpm"
#include "bitmaps/save.xpm"

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




wxBitmap wxAuiBitmapFromBits(const unsigned char bits[], int w, int h,	const wxColour& color);


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

	sprintf(pp, "  c %s", clr.GetAsString(wxC2S_HTML_SYNTAX).c_str().AsChar());
	
	
	for(int i = 0; i < n; i++ )
		xpmData1[i] = (char *)(xpm_data[i]);

	xpmData1[1] = pp;
	return xpmData1;
}

#define CHECK_ART_ID(idArt,client,filename) \
	else if (id == idArt) \
	{\
		if ( client == ART_MENUHOVER) \
			clr = clrs->Get(ColourScheme::BITMAP_CMD_HOVER); \
		else if (client == ART_MENUDISABLED) \
			clr = clrs->Get(ColourScheme::BITMAP_CMD_DISABLED); \
		else\
			clr = clrs->Get(ColourScheme::BITMAP_CMD);\
		if (clr.IsOk())\
			return wxBitmap(GetBitmapColor(filename, clr));\
		else\
			return wxBitmap(filename);\
	}

#define CHECK_ART_ID0(idArt,filename) \
	else if (id == idArt) \
	{\
		return wxBitmap(filename);\
	}

wxBitmap ExArtProvider::CreateBitmap(const wxArtID& id, const wxArtClient& client, const wxSize& size)
{

	ColourScheme *clrs = Preferences::Get()->GetColorScheme();	

	wxColor clr;
	if (id == wxART_NEW)
	{
		if (client == wxART_MENU)
		{
			clr = clrs->Get(ColourScheme::BITMAP_CMD);
		}
		else if (client == wxART_LIST)
		{
			clr = clrs->Get(ColourScheme::BITMAP_NEW_LIST);
		}
		else if (client == ART_MENUHOVER)
		{
			clr = clrs->Get(ColourScheme::BITMAP_CMD_HOVER);
		}
		if ( clr.IsOk() )
			return wxBitmap(GetBitmapColor(file_new_xpm, clr));
		else
			return wxBitmap(file_new_xpm);
	}
	else if(id == wxART_FOLDER)
	{
		clr = clrs->Get(ColourScheme::BITMAP_FOLDER_LIST);
		if (clr.IsOk())
			return wxBitmap(GetBitmapColor(folder_xpm, clr));
		else
			return wxBitmap(folder_xpm);
	}

	CHECK_ART_ID(ART_SAVE, client, file_save_xpm)
	CHECK_ART_ID(wxART_FILE_OPEN, client, file_open_xpm)
	CHECK_ART_ID(ART_PREFERENCES, client, preferences_xpm)
	CHECK_ART_ID(ART_UPDATE, client, update_xpm)
	CHECK_ART_ID(ART_VERIFY, client, verify_xpm)
	CHECK_ART_ID(ART_PAUSE, client, pause_xpm)
	CHECK_ART_ID(ART_PLAY, client, play_xpm)
	CHECK_ART_ID(ART_STOP, client, stop_xpm)
	CHECK_ART_ID(ART_CLOSE, client, close_xpm)
	CHECK_ART_ID(ART_CONVERT, client, convert_xpm)
	CHECK_ART_ID(ART_DRAW3D, client, view3d_xpm)
	CHECK_ART_ID(ART_ADD, client, add_xpm)
	CHECK_ART_ID0(ART_MAIL, mail_xpm)
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

	m_activeCaptionColour = clrs->Get(ColourScheme::WINDOW);
	m_activeCaptionGradientColour = clrs->Get(ColourScheme::WINDOW);
	m_activeCaptionTextColour = clrs->Get(ColourScheme::WINDOW_TEXT);// TITLEBAR_ACTIVE_TEXT);
	m_inactiveCaptionColour = clrs->Get(ColourScheme::FRAME);// TITLEBAR);
	m_inactiveCaptionGradientColour = clrs->Get(ColourScheme::FRAME);
	m_inactiveCaptionTextColour = clrs->Get(ColourScheme::WINDOW_TEXT);

	m_sashBrush = wxBrush(clrs->Get(ColourScheme::BORDER));
	m_backgroundBrush = wxBrush(baseColour);
	m_gripperBrush = wxBrush(*wxGREEN);

	m_borderPen = wxPen(clrs->Get(ColourScheme::BORDER));
	int pen_width = wxWindow::FromDIP(1, NULL);
	m_gripperPen1 = wxPen(darker5Colour, pen_width);
	m_gripperPen2 = wxPen(darker3Colour, pen_width);
	m_gripperPen3 = wxPen(*wxStockGDI::GetColour(wxStockGDI::COLOUR_WHITE), pen_width);
	//InitBitmaps();


	wxColor clrBtn = clrs->Get(ColourScheme::BITMAP_CMD);//wxColor(0x999999);
	wxColor clrBtnActive = clrs->Get(ColourScheme::BITMAP_CMD_HOVER);//wxColor(0xe6e6e6);

	m_activeCloseBitmap = wxBitmap(GetBitmapColor(close_xpm, clrBtnActive));
	m_inactiveCloseBitmap = wxBitmap(GetBitmapColor(close_xpm, clrBtn));
	m_captionFont.Bold();
	m_captionFont.SetPointSize(10);
	m_captionSize = m_captionFont.GetPixelSize().y + 10;
	m_borderSize = 1;
	m_sashSize = 4;
	m_buttonSize = 12;
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
}


wxSize EditorTabArt::GetTabSize(wxDC& dc, wxWindow* wnd, const wxString& caption, const wxBitmap& bitmap, bool active, int closeButtonState, int* xExtent)
{
	wxSize sz = wxAuiGenericTabArt::GetTabSize(dc, wnd, caption, bitmap, active, closeButtonState, xExtent);
	sz.y += 6;	
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
	

	m_baseColourBrush = wxBrush(m_activeColour);
	m_baseColourPen = wxPen(m_activeColour);

	wxColor clrBtn = clrs->Get(ColourScheme::BITMAP_CMD);//wxColor(0x999999);
	wxColor clrBtnActive = clrs->Get(ColourScheme::BITMAP_CMD_HOVER);//wxColor(0xe6e6e6);
	m_activeCloseBmp = wxBitmap(GetBitmapColor(close_xpm, clrBtnActive));
	m_disabledCloseBmp = wxBitmap(GetBitmapColor(close_xpm, clrBtn));
	
	m_activeLeftBmp = wxAuiBitmapFromBits(left_bits, 16, 16, clrBtnActive);
	m_disabledLeftBmp = wxAuiBitmapFromBits(left_bits, 16, 16, clrBtn);
	m_activeRightBmp = wxAuiBitmapFromBits(right_bits, 16, 16, clrBtnActive);
	m_disabledRightBmp = wxAuiBitmapFromBits(right_bits, 16, 16, clrBtn);
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

	ReadColor(root["frame"], m_colors[FRAME]);
	ReadColor(root["window"],m_colors[WINDOW]);
	ReadColor(root["window_3dview"], m_colors[WINDOW_3DVIEW]);	
	ReadColor(root["window_hover"], m_colors[WINDOW_HOVER]);
	ReadColor(root["window_txt"], m_colors[WINDOW_TEXT]);
	ReadColor(root["window_txt_hover"], m_colors[WINDOW_TEXT_HOVER]);
	ReadColor(root["window_txt_disable"], m_colors[WINDOW_TEXT_DISABLE]);
	ReadColor(root["bitmap_cmd"], m_colors[BITMAP_CMD]);
	ReadColor(root["bitmap_cmd_hover"], m_colors[BITMAP_CMD_HOVER]);		
	ReadColor(root["bitmap_cmd_disable"], m_colors[BITMAP_CMD_DISABLED]);
	ReadColor(root["linenumber"], m_colors[LINENUMBER]);
	ReadColor(root["linenumber_txt"], m_colors[LINENUMBER_TEXT]);
	ReadColor(root["calltip"], m_colors[CALLTIP]);
	ReadColor(root["calltip_txt"], m_colors[CALLTIP_TEXT]);
	ReadColor(root["ctrl"],m_colors[CONTROL]);
	ReadColor(root["ctrl_pressed"],m_colors[CONTROL_PRESSED]);
	ReadColor(root["ctrl_hover"],m_colors[CONTROL_HOVER]);
	ReadColor(root["ctrl_text"],m_colors[CONTROL_TEXT]);
	ReadColor(root["ctrl_text_hover"], m_colors[CONTROL_TEXT_HOVER]);
	ReadColor(root["ctrl_text_dis"], m_colors[CONTROL_TEXT_DISABLED]);
	ReadColor(root["ctrl_active"], m_colors[CONTROL_ACTIVE]);
	ReadColor(root["ctrl_active_pressed"], m_colors[CONTROL_ACTIVE_PRESSED]);
	ReadColor(root["ctrl_active_hover"], m_colors[CONTROL_ACTIVE_HOVER]);
	ReadColor(root["ctrl_active_text"], m_colors[CONTROL_ACTIVE_TEXT]);
	ReadColor(root["control_active_text_hover"], m_colors[CONTROL_ACTIVE_TEXT_HOVER]);
	ReadColor(root["button_feedback"], m_colors[BUTTON_FEEDBACK]);
	ReadColor(root["button_feedback_hover"], m_colors[BUTTON_FEEDBACK_HOVER]);
	ReadColor(root["scrollbar"],m_colors[SCROLLBAR]);
	ReadColor(root["scrollbar_tubm"],m_colors[SCROLLBAR_TUMB]);
	ReadColor(root["scrollbar_tumb_hvr"], m_colors[SCROLLBAR_TUMB_HOVER]);	
	ReadColor(root["highlight"],m_colors[HIGHLIGHT]);
	ReadColor(root["highlight_txt"],m_colors[HIGHLIGHT_TEXT]);
	ReadColor(root["hyperlink_txt"], m_colors[HYPERLINK_TEXT]);
	ReadColor(root["titlebar_txt"],m_colors[TITLEBAR_TEXT]);
	ReadColor(root["titlebar_txt_active"],m_colors[TITLEBAR_ACTIVE_TEXT]);
	ReadColor(root["slider_shaft"], m_colors[SLIDER_SHAFT]);
	ReadColor(root["slider_shaft_colored"],m_colors[SLIDER_SHAFT_COLORED]);	
	ReadColor(root["bitmap_new_list"], m_colors[BITMAP_NEW_LIST]);
	ReadColor(root["bitmap_folder_list"], m_colors[BITMAP_FOLDER_LIST]);
	ReadColor(root["static_line"], m_colors[STATIC_LINE]);
	ReadColor(root["msg_log_error"], m_colors[MSG_LOG_ERROR]);
	ReadColor(root["msg_log_info"], m_colors[MSG_LOG_INFO]);
	ReadColor(root["msg_log_warning"], m_colors[MSG_LOG_WARNING]);	
	ReadColor(root["border"],m_colors[BORDER]);

	ReadColor(root["view3d_box"], m_colors[VIEW3D_BOX]);
	ReadColor(root["view3d_g0"], m_colors[VIEW3D_G0]);
	ReadColor(root["view3d_g1"], m_colors[VIEW3D_G1]);
	ReadColor(root["view3d_xaxis"], m_colors[VIEW3D_XAXIS]);
	ReadColor(root["view3d_yaxis"], m_colors[VIEW3D_YAXIS]);
	ReadColor(root["view3d_zaxis"], m_colors[VIEW3D_ZAXIS]);

}


void ColourScheme::InitDef()
{
	m_colors.resize(StdColour::MAX);
	m_colors[FRAME] = wxColor(0x3d3d3d);
	// the background colour for a window
	m_colors[WINDOW] = wxColor(0x111111);
	m_colors[WINDOW_3DVIEW] = wxColor(0x222222);
	m_colors[WINDOW_HOVER] = wxColor(0x4d4d4d); 
	m_colors[WINDOW_TEXT] = wxColor(0xeeeeee);
	m_colors[WINDOW_TEXT_HOVER] = wxColor(0xFFFFFF);
	m_colors[WINDOW_TEXT_DISABLE] = wxColor(0x666666);
	m_colors[BITMAP_CMD] = wxColor(0x999999);
	m_colors[BITMAP_CMD_HOVER] = wxColor(0xe6e6e6);
	m_colors[BITMAP_CMD_DISABLED] = wxColor(0x555555);
	
	m_colors[LINENUMBER] = wxColor(0x111111);
	m_colors[LINENUMBER_TEXT] = wxColor(0x666666);
	m_colors[CALLTIP] = wxColor(0x333333);
	m_colors[CALLTIP_TEXT]= wxColor(0xeeeeee);
		// the different background and text colours for the control
	m_colors[CONTROL] = wxColour(0x3d3d3d);
	m_colors[CONTROL_PRESSED] = wxColour(0x4d4d4d);
	m_colors[CONTROL_HOVER] = wxColour(0x4d4d4d);
	m_colors[CONTROL_ACTIVE] = wxColour(0xbbbbbb);
	m_colors[CONTROL_ACTIVE_PRESSED] = wxColour(0x999999);
	m_colors[CONTROL_ACTIVE_HOVER] = wxColour(0x999999);

	// the label text for the normal and the disabled state
	m_colors[CONTROL_TEXT] = wxColour(0xeeeeee);
	m_colors[CONTROL_TEXT_HOVER] = wxColour(0xFFFFFF);//wxColour(0xFFFFFF);
	m_colors[CONTROL_TEXT_DISABLED] = wxColour(0x3C3C3C);
	m_colors[CONTROL_ACTIVE_TEXT] = wxColour(0,0,0);
	m_colors[CONTROL_ACTIVE_TEXT_HOVER] = wxColour(0,0,0);
	m_colors[BUTTON_FEEDBACK] = wxColour(0x3088cc);
	m_colors[BUTTON_FEEDBACK_HOVER] = wxColour(0x0066bb);
		// the scrollbar background colour for the normal and pressed states
	m_colors[SCROLLBAR] = wxColour(0x111111);
	m_colors[SCROLLBAR_TUMB] = wxColour(0x4d4d4d);
	m_colors[SCROLLBAR_TUMB_HOVER] = wxColour(0x3d3d3d);
	// the background and text colour for the highlighted item
	m_colors[HIGHLIGHT] = wxColour(0x576573);
	m_colors[HIGHLIGHT_TEXT] = wxColour(0xffffff);
	m_colors[HYPERLINK_TEXT] = wxColour(0xddaa55);

		// the titlebar text colours
	m_colors[TITLEBAR_TEXT] = wxColour(0xFFFFFF);
	m_colors[TITLEBAR_ACTIVE_TEXT] = wxColour(0xFFFFFF);

	m_colors[SLIDER_SHAFT] = wxColour(0x4d4d4d);
	m_colors[SLIDER_SHAFT_COLORED] = wxColour(0x44bbff);
	m_colors[BITMAP_NEW_LIST] = wxColour(0xddaa55);
	m_colors[BITMAP_FOLDER_LIST] = wxColour(0x44bbff);

	m_colors[STATIC_LINE] = wxColour(0x4d4d4d);

	m_colors[MSG_LOG_ERROR] = wxColour(0x7766ee);
	m_colors[MSG_LOG_INFO] = wxColour(0x84e484);
	m_colors[MSG_LOG_WARNING] = wxColour(0x44bbff);

	// border
	m_colors[BORDER] = wxColour(0x3C3C3C);

	m_colors[VIEW3D_BOX] = wxColour(0x00FF00);
	m_colors[VIEW3D_G0] = wxColour(0x0000FF);
	m_colors[VIEW3D_G1] = wxColour(0xFFFFFF);
	m_colors[VIEW3D_XAXIS] = wxColour(0x0000FF);
	m_colors[VIEW3D_YAXIS] = wxColour(0x00FF00);
	m_colors[VIEW3D_ZAXIS] = wxColour(0xFF0000);
}
