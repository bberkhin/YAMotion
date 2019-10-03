#include "wx/wx.h"
#include "about.h"
#include "appdefs.h"
#include "defsext.h"
#include "prefs.h"



//----------------------------------------------------------------------------
// AppAbout
//----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(AppAbout, wxDialog)
EVT_TIMER(ID_ABOUTTIMER, AppAbout::OnTimerEvent)
wxEND_EVENT_TABLE()

AppAbout::AppAbout(wxWindow *parent,
	int milliseconds,
	long style)
	: wxDialog(parent, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize,
		style | wxBORDER_NONE | wxDEFAULT_DIALOG_STYLE
		) {

	// set timer if any
	m_timer = NULL;
	if (milliseconds > 0) {
		m_timer = new wxTimer(this, ID_ABOUTTIMER);
		m_timer->Start(milliseconds, wxTIMER_ONE_SHOT);
	}

	// sets the application title
	SetTitle(_("About .."));

	// about icontitle//info
	wxBoxSizer *aboutpane = new wxBoxSizer(wxVERTICAL);
	//wxBitmap bitmap = wxBitmap(wxICON(app_icon));
	wxBitmap bitmap(L"IDB_BIGLOGO", wxBITMAP_TYPE_PNG_RESOURCE);
	if (!bitmap.IsOk())
		bitmap = wxBitmap(wxICON(app_icon));

	//aboutpane->AddSpacer(20);

	aboutpane->Add(new wxStaticBitmap(this, wxID_ANY, bitmap),
		0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 20);

	aboutpane->AddSpacer(20);

	wxStaticText *appname = new wxStaticText(this, wxID_ANY, APP_NAME);
	appname->SetFont(wxFontInfo(14).Bold());
	aboutpane->Add(appname, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 40);
	aboutpane->AddSpacer(20);

	// about info
	wxGridSizer *aboutinfo = new wxGridSizer(2, 10, 10);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("Version: ")),//wxDefaultPosition,wxDefaultSize, wxALIGN_RIGHT),
		0, wxALIGN_RIGHT);

	aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_VERSION),
		1, wxEXPAND | wxALIGN_LEFT);

	aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("Build date: ")),
		0, wxALIGN_RIGHT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_BUILD),
		1, wxEXPAND | wxALIGN_LEFT);

	aboutinfo->Add(new wxStaticText(this, wxID_ANY, _(" ")),
		0, wxALIGN_RIGHT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, _(" ")),
		1, wxEXPAND | wxALIGN_LEFT);

	aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("Author: ")),
		0, wxALIGN_RIGHT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_MAINT),
		1, wxEXPAND | wxALIGN_LEFT);

	aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("Home Page: ")),
		0, wxALIGN_RIGHT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_WEBSITE),
		1, wxEXPAND | wxALIGN_LEFT);
	
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("E-mail: ")),
		0, wxALIGN_RIGHT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_EMAILTEXT),
		1, wxEXPAND | wxALIGN_LEFT);
	
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("Licence type: ")),
		0, wxALIGN_RIGHT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_LICENCE),
		1, wxEXPAND | wxALIGN_LEFT);

	aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("G-Code Meta Compiler: ")),
		0, wxALIGN_RIGHT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_GCMCAUTHOR),
		1, wxEXPAND | wxALIGN_LEFT);

	aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("")),
		0, wxALIGN_RIGHT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_GCMCHOMEPAGE),
		1, wxEXPAND | wxALIGN_LEFT);


	aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("Copyright: ")),
		0, wxALIGN_RIGHT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_COPYRIGTH),
		1, wxEXPAND | wxALIGN_LEFT);

	aboutpane->Add(aboutinfo, 1, wxEXPAND);
//	aboutpane->AddSpacer(20);

//	// about complete
	wxBoxSizer *totalpane = new wxBoxSizer(wxHORIZONTAL);
	//totalpane->AddSpacer(20);
	totalpane->Add(aboutpane, 0, wxEXPAND | wxALL, 30);
	//totalpane->AddSpacer(20);


//	totalpane->AddSpacer(20);
////	wxStaticText *appname = new wxStaticText(this, wxID_ANY, APP_NAME);
////	appname->SetFont(wxFontInfo(14).Bold());
////	totalpane->Add(appname, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 40);
//	totalpane->Add(aboutpane, 0, wxEXPAND | wxALL, 4);
////	totalpane->Add(new wxStaticText(this, wxID_ANY, APP_MAIL),
//	//	0, wxALIGN_CENTER | wxALL, 10);
//	wxButton *okButton = new wxButton(this, wxID_OK, _("OK"));
//	okButton->SetDefault();
//	totalpane->AddSpacer(20);
//	totalpane->Add(okButton, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxBOTTOM, 10);

	SetSizerAndFit(totalpane);

	UpdateThemeColor();
	CenterOnScreen();
	ShowModal();
}

AppAbout::~AppAbout() {
	wxDELETE(m_timer);
}

//----------------------------------------------------------------------------
// event handlers
void AppAbout::OnTimerEvent(wxTimerEvent &WXUNUSED(event)) {
	wxDELETE(m_timer);
	EndModal(wxID_OK);
}



void AppAbout::UpdateThemeColor()
{
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	wxColor bgColor = clrs->Get(ColourScheme::WINDOW);
	wxColor fgColor = clrs->Get(ColourScheme::WINDOW_TEXT);

	SetBackgroundColour(bgColor);
	SetForegroundColour(fgColor);

	wxWindowList::compatibility_iterator node = GetChildren().GetFirst();
	while (node)
	{
		wxWindow* child = node->GetData();
		/*		FlatButton *fbt = dynamic_cast<FlatButton *>(child);
				if (fbt)
					fbt->UpdateThemeColor();
				else
				*/
		{
			child->SetBackgroundColour(bgColor);
			child->SetForegroundColour(fgColor);
		}
		node = node->GetNext();
	}
}