#include "wx/wx.h"
#include "about.h"
#include "appdefs.h"
#include "defsext.h"


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
		style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {

	// set timer if any
	m_timer = NULL;
	if (milliseconds > 0) {
		m_timer = new wxTimer(this, ID_ABOUTTIMER);
		m_timer->Start(milliseconds, wxTIMER_ONE_SHOT);
	}

	// sets the application title
	SetTitle(_("About .."));

	// about info
	wxGridSizer *aboutinfo = new wxGridSizer(2, 0, 2);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("Written by: ")),
		0, wxALIGN_LEFT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_MAINT),
		1, wxEXPAND | wxALIGN_LEFT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("Version: ")),
		0, wxALIGN_LEFT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY,  APP_VERSION),
		1, wxEXPAND | wxALIGN_LEFT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("Licence type: ")),
		0, wxALIGN_LEFT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_LICENCE),
		1, wxEXPAND | wxALIGN_LEFT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("Copyright: ")),
		0, wxALIGN_LEFT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_COPYRIGTH),
		1, wxEXPAND | wxALIGN_LEFT);

	// about icontitle//info
	wxBoxSizer *aboutpane = new wxBoxSizer(wxHORIZONTAL);
	wxBitmap bitmap = wxBitmap(wxICON(sample));
	aboutpane->Add(new wxStaticBitmap(this, wxID_ANY, bitmap),
		0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 20);
	aboutpane->Add(aboutinfo, 1, wxEXPAND);
	aboutpane->Add(60, 0);

	// about complete
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	totalpane->Add(0, 20);
	wxStaticText *appname = new wxStaticText(this, wxID_ANY, APP_NAME);
	appname->SetFont(wxFontInfo(14).Bold());
	totalpane->Add(appname, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 40);
	totalpane->Add(0, 10);
	totalpane->Add(aboutpane, 0, wxEXPAND | wxALL, 4);
	totalpane->Add(new wxStaticText(this, wxID_ANY, APP_DESCR),
		0, wxALIGN_CENTER | wxALL, 10);
	wxButton *okButton = new wxButton(this, wxID_OK, _("OK"));
	okButton->SetDefault();
	totalpane->Add(okButton, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxBOTTOM, 10);

	SetSizerAndFit(totalpane);

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


