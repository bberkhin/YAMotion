#include "wx/wx.h"
#include "flatstaticline.h"

#include "appdefs.h"
#include "welcomewnd.h"
#include "standartpaths.h"
#include "configdata.h"
#include "app.h"
#include "prefs.h"
#include "defsext.h"
#include "flatbuttom.h"

#define WELCOME_MARGIN 10
#define MARGIN_TOP 20
#define MARGIN_BOTTOM 8
#define MARGIN_LEFT_RIGHT 20

enum
{
	ID_STATICTEXTFG = 5000,
	ID_STATICTEXDISABLE
};




wxIMPLEMENT_ABSTRACT_CLASS(WelcomeWnd, wxPanel);

wxBEGIN_EVENT_TABLE(WelcomeWnd, wxPanel)

wxEND_EVENT_TABLE()



WelcomeWnd::WelcomeWnd(wxWindow *parent) : wxPanel(parent)
{


	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	//Top Margin
	totalpane->AddSpacer(MARGIN_TOP);	
	// Header
	wxStaticText *ptxt = new wxStaticText(this, ID_STATICTEXTFG, APP_NAME );
	//ptxt->SetForegroundColour(m_fgColor);
	ptxt->SetFont(wxFontInfo(28).Bold());
	wxBoxSizer *phor = new wxBoxSizer(wxHORIZONTAL);
	phor->AddSpacer(MARGIN_LEFT_RIGHT);
	phor->Add(ptxt, 0, wxEXPAND);
	totalpane->Add(phor, 0, wxEXPAND);
	totalpane->AddSpacer(MARGIN_TOP);

	wxBoxSizer *panemain = new wxBoxSizer(wxHORIZONTAL);
	panemain->Add(CreateCommand(), 0, wxLEFT);
	panemain->AddSpacer(WELCOME_MARGIN);
	FlatStaticLine *pGripper = new FlatStaticLine(this,wxID_ANY,wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	panemain->Add(pGripper, 0, wxGROW | wxLEFT | wxRIGHT, 5);
	panemain->AddSpacer(WELCOME_MARGIN);
	
	panemain->Add(CreateRecentFilesList(), 0, wxEXPAND, wxBORDER);
	panemain->AddSpacer(WELCOME_MARGIN);
	pGripper = new FlatStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
	panemain->Add(pGripper, 0, wxGROW | wxLEFT | wxRIGHT, 5);
	panemain->AddSpacer(WELCOME_MARGIN);
	panemain->Add(CreateDoc(), 0, wxRIGHT);


	phor = new wxBoxSizer(wxHORIZONTAL);
	phor->AddSpacer(MARGIN_LEFT_RIGHT);
	phor->Add(panemain, wxEXPAND, wxEXPAND);
	totalpane->Add(phor, wxEXPAND, wxEXPAND);
	
	phor = new wxBoxSizer(wxHORIZONTAL);
	phor->AddSpacer(MARGIN_LEFT_RIGHT);
	phor->Add(CreateFooter(), wxEXPAND, wxEXPAND);
	phor->AddSpacer(MARGIN_LEFT_RIGHT);
	totalpane->Add(phor, 0, wxEXPAND);
	totalpane->AddSpacer(MARGIN_BOTTOM);
	
	UpdateThemeColor();
	SetSizerAndFit(totalpane);
}

void WelcomeWnd::UpdateThemeColor()
{
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	
	wxColor m_bgColor; //clrs->Get(ColourScheme::WINDOW);
	wxColor m_bghColor; 
	wxColor m_fgColor; //clrs->Get(ColourScheme::WINDOW_TEXT);
	wxColor m_fghColor;

	m_fgColor = clrs->Get(ColourScheme::WINDOW_TEXT);
	m_fghColor = clrs->Get(ColourScheme::WINDOW_TEXT_HOVER);
	m_bgColor = clrs->Get(ColourScheme::WINDOW);
	m_bghColor = clrs->Get(ColourScheme::WINDOW_HOVER); //wxColor(0x4d4d4d); 

	SetBackgroundColour(m_bgColor);
	SetForegroundColour(m_fgColor);

	wxWindowList::compatibility_iterator node = GetChildren().GetFirst();
	while (node)
	{
		wxWindow* child = node->GetData();
		child->SetBackgroundColour(m_bgColor);
		FlatButton *ph = dynamic_cast<FlatButton *>(child);
		wxWindowID id = child->GetId();
		switch (id)
		{
		case ID_STATICTEXTFG: 
			child->SetForegroundColour(m_fgColor); 
			break;
		case ID_STATICTEXDISABLE:
			child->SetForegroundColour(clrs->Get(ColourScheme::WINDOW_TEXT_DISABLE)); 
			break;
		// main cmd
		case ID_OPENFILE:
		case ID_NEWNC:
		case ID_NEWGCMC:
			wxASSERT(ph);
			ph->SetForegroundColour(m_fgColor);
			ph->SetColour(FlatButton::BackgroundColour, m_bgColor);
			ph->SetColour(FlatButton::HoverBackgroundColour, m_bghColor);
			ph->SetColour(FlatButton::PressBackgroundColour, m_bghColor);
			ph->SetColour(FlatButton::ForegroundColour, m_fgColor);
			ph->SetColour(FlatButton::HoverForegroundColour, m_fghColor);
			ph->SetColour(FlatButton::PressForegroundColour, m_fghColor);

			break;
		//footer cmd
		case ID_GLOBALPREFS:
		case ID_CHECKUPDATE:
			wxASSERT(ph);
			ph->SetForegroundColour(m_fgColor);
			ph->SetColour(FlatButton::BackgroundColour, m_bgColor);
			ph->SetColour(FlatButton::HoverBackgroundColour, m_bghColor);
			ph->SetColour(FlatButton::PressBackgroundColour, m_bghColor);
			ph->SetColour(FlatButton::ForegroundColour, clrs->Get(ColourScheme::CONTROL_TEXT));
			ph->SetColour(FlatButton::HoverForegroundColour, clrs->Get(ColourScheme::CONTROL_TEXT_HOVER));
			ph->SetColour(FlatButton::PressForegroundColour, clrs->Get(ColourScheme::CONTROL_TEXT_HOVER));
			break;
		// help linl
		case ID_HELPGCMC:
		case ID_HELPNC:
		case ID_WHATNEWS:
			wxASSERT(ph);
			ph->SetForegroundColour(m_fgColor);
			ph->SetColour(FlatButton::BackgroundColour, m_bgColor);
			ph->SetColour(FlatButton::HoverBackgroundColour, m_bghColor);
			ph->SetColour(FlatButton::PressBackgroundColour, m_bghColor);
			ph->SetColour(FlatButton::ForegroundColour, m_fgColor);
			ph->SetColour(FlatButton::HoverForegroundColour, m_fghColor);
			ph->SetColour(FlatButton::PressForegroundColour, m_fghColor);
			break;
		case ID_WRITEFEEDBACK:
		{
			wxASSERT(ph);
			wxColor clrbg = clrs->Get(ColourScheme::BUTTON_FEEDBACK);// ("#cc8830");
			wxColor clrbghv = clrs->Get(ColourScheme::BUTTON_FEEDBACK_HOVER);//("#bb6600");
			ph->SetForegroundColour(m_fgColor);
			ph->SetColour(FlatButton::BackgroundColour, clrbg);
			ph->SetColour(FlatButton::HoverBackgroundColour, clrbghv);
			ph->SetColour(FlatButton::PressBackgroundColour, clrbghv);
			ph->SetColour(FlatButton::ForegroundColour, m_fgColor);
			ph->SetColour(FlatButton::HoverForegroundColour, m_fgColor);
			ph->SetColour(FlatButton::PressForegroundColour, m_fgColor);
		}
			break;

		default:
			if (ph && id >= 100 && id <= 110) //recenrt files
			{
				ph->SetForegroundColour(m_fgColor);
				ph->SetColour(FlatButton::BackgroundColour, m_bgColor);
				ph->SetColour(FlatButton::HoverBackgroundColour, m_bghColor);
				ph->SetColour(FlatButton::PressBackgroundColour, m_bghColor);
				ph->SetColour(FlatButton::ForegroundColour, m_fgColor);
				ph->SetColour(FlatButton::HoverForegroundColour, m_fghColor);
				ph->SetColour(FlatButton::PressForegroundColour, m_fghColor);
			}
			break;

		};
		node = node->GetNext();
	}
	
}

void WelcomeWnd::AddColumnHeader(wxBoxSizer *pane, const wxString &text)
{
	wxStaticText *ph = new wxStaticText(this, ID_STATICTEXTFG, text);
	ph->SetFont(wxFontInfo(10).Bold()); 
	pane->Add(ph, 0, 0); 
	pane->AddSpacer(WELCOME_MARGIN );
}

void WelcomeWnd::AddCommand(wxBoxSizer *pane, const wxString &text, int cmd, bool footer)
{
	FlatButton *ph = new FlatButton(this, cmd, text, footer ? (FB_BITMAP_LEFT | FB_LABEL_LEFT) : (FB_BITMAP_RIGHT | FB_LABEL_LEFT));	
	ph->SetCommand(cmd);
	ph->SetFont(wxFontInfo(10));
	
	wxArtID idArt;
	switch (cmd)
	{
		case ID_OPENFILE:		idArt = wxART_FILE_OPEN; break;
		case ID_NEWNC:
		case ID_NEWGCMC:		idArt = wxART_NEW; break;
		case ID_GLOBALPREFS:	idArt = ART_PREFERENCES; break;
		case ID_CHECKUPDATE:	idArt = ART_UPDATE; break;
	}

	wxBitmap bmp = wxArtProvider::GetBitmap(idArt, wxART_MENU);
	wxBitmap bmphover = wxArtProvider::GetBitmap(idArt, ART_MENUHOVER);

	if (footer)
	{
		ph->SetBitmap(bmp, bmphover, 3);
		pane->Add(ph, 0, wxALIGN_CENTER_VERTICAL);//wxALIGN_BOTTOM);
	}
	else
	{
		ph->SetBitmap(bmp, bmphover, 30);
		pane->Add(ph, 0, wxEXPAND);
	}
}

void WelcomeWnd::AddRecentFile(wxBoxSizer *pane, const wxFileName &p, int n)
{	
	int cmd = wxID_FILE + n;
	FlatButton *ph = new FlatButton(this,100+n, p.GetFullName(), FB_BITMAP_LEFT);
	ph->SetCommand(cmd);
	ph->SetFont(wxFontInfo(10));

	wxBitmap bmp = wxArtProvider::GetBitmap(wxART_NEW, wxART_LIST);
	ph->SetBitmap(bmp, 10 );
	ph->SetToolTip(p.GetFullPath() );
	pane->Add(ph, 0, wxEXPAND);
}

wxBoxSizer *WelcomeWnd::CreateCommand()
{
	wxBoxSizer *pane = new wxBoxSizer(wxVERTICAL);
	AddColumnHeader(pane, _("Files"));
	AddCommand(pane, _("Open"), ID_OPENFILE);
	pane->AddSpacer(WELCOME_MARGIN/2);
	AddCommand(pane, _("New G-Code"), ID_NEWNC );
	AddCommand(pane, _("New GCMC"), ID_NEWGCMC);
	return pane;
}


void WelcomeWnd::AddHelpLink(wxBoxSizer *pane, const wxString &text, int cmd )
{
	FlatButton *ph = new FlatButton(this, cmd, text, FB_LABEL_LEFT);
	ph->SetCommand(cmd);
	ph->SetFont(wxFontInfo(10));
	ph->UpdateSize();
	pane->Add(ph, 0, wxEXPAND);

}


wxBoxSizer *WelcomeWnd::CreateDoc()
{
	wxBoxSizer *pane = new wxBoxSizer(wxVERTICAL);
	AddColumnHeader(pane, _("Help"));
	AddHelpLink(pane, _("Matilda website"), ID_WHATNEWS);
	//AddHelpLink(pane, _("Editor documentation"), ID_HELPEDITOR);
	AddHelpLink(pane, _("GCMC documentation"), ID_HELPGCMC);
	AddHelpLink(pane, _("G-Code reference"), ID_HELPNC);	
	return pane;
}

void WelcomeWnd::AddLastFilesToMenu(bool update)
{
	
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	if (!config)
		return;

	size_t n;
	const FileNamesList &files = config->GetFiles();
	size_t files_count = files.size();
	size_t menuitem_count = m_LastFiles->GetItemCount() - 2; // -2 becouse of header
	if (menuitem_count > files_count) // remove not needed  menuitem
	{
		n = menuitem_count - files_count;
		for (size_t i = 0; i < n; i++)
		{
			wxSizerItem *sizeritem = m_LastFiles->GetItem(menuitem_count);
			if (sizeritem && sizeritem->IsWindow())
			{
				sizeritem->DeleteWindows();
				m_LastFiles->Remove(menuitem_count);
				menuitem_count--;
			}
		}
	}

	// set new label
	n = 0;
	for (auto it = files.begin(); it != files.end(); ++it, ++n)
	{
		if (n >= 10)
			break;
		if (n < menuitem_count)
		{
			wxSizerItem *sizeritem = m_LastFiles->GetItem(n+2);
			if ( sizeritem && sizeritem->IsWindow() )
				sizeritem->GetWindow()->SetLabel(it->GetFullName());
		}
		else
			AddRecentFile(m_LastFiles, *it, n);
	}
	if (update)
		Layout();
}

wxBoxSizer *WelcomeWnd::CreateRecentFilesList( )
{
	m_LastFiles = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *pane = m_LastFiles;
	AddColumnHeader(pane, _("Recent Files"));
	AddLastFilesToMenu(false);
	return pane;
}


wxBoxSizer *WelcomeWnd::CreateFooter()
{

	ColourScheme *clrs = Preferences::Get()->GetColorScheme();

	wxBoxSizer *pane = new wxBoxSizer(wxHORIZONTAL);
	pane->AddSpacer(WELCOME_MARGIN);
	wxString ver = APP_VERSION;
	//ver += L" ";
	//ver += WXSTRINGCOPYRIGHT; //be more modest

	wxBoxSizer *paneCmd = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *pTxt = new wxStaticText(this, ID_STATICTEXDISABLE, ver);
	pTxt->SetFont(wxFontInfo(10));
	
	
	paneCmd->Add(pTxt, 0, wxALIGN_CENTER_VERTICAL);
	paneCmd->AddSpacer(WELCOME_MARGIN);
	
	AddCommand(paneCmd, _("Preferences"), ID_GLOBALPREFS, true);

	paneCmd->AddSpacer(WELCOME_MARGIN);
	AddCommand(paneCmd, _("Check for Update"), ID_CHECKUPDATE, true);
	pane->Add( paneCmd, 0, wxALIGN_BOTTOM);
	pane->AddStretchSpacer();
	
	wxBoxSizer *pane1 = new wxBoxSizer(wxVERTICAL);
	/*
	pTxt = new wxStaticText(this, ID_STATICTEXTFG, _("Help us become better"));
	pTxt->SetFont(wxFontInfo(10).Bold());
	pane1->Add(pTxt, 0, wxALIGN_CENTER_HORIZONTAL);
	*/
	pTxt = new wxStaticText(this, ID_STATICTEXTFG, _("Help me to make the app better"));
	pTxt->SetFont(wxFontInfo(10));
	pane1->Add(pTxt, 0, wxALIGN_CENTER_HORIZONTAL);
	
	FlatButton *ph = new FlatButton(this, ID_WRITEFEEDBACK, _("FEEDBACK"), FB_LABEL_CENTER);
	ph->SetCommand(ID_WRITEFEEDBACK);
	ph->SetFont(wxFontInfo(11).Bold() );
	ph->SetMargins(15, 8);
	wxBitmap bmp = wxArtProvider::GetBitmap(ART_MAIL, wxART_OTHER);
	ph->SetBitmap(bmp, 8);
	pane1->Add(ph, 0, wxEXPAND );

	pane->Add(pane1, 0, wxRIGHT | wxALIGN_BOTTOM);
	return pane;
}

WelcomeWnd::~WelcomeWnd()
{

}

