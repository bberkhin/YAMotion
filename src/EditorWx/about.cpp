#include "wx/wx.h"
#include <wx/hyperlink.h>
#include "about.h"
#include "appdefs.h"
#include "defsext.h"
#include "prefs.h"

#define ID_DIABLEANY 100

//----------------------------------------------------------------------------
// AppAbout
//----------------------------------------------------------------------------

class NoFocusLink : public wxHyperlinkCtrl
{
public:
	NoFocusLink(wxWindow *parent, wxWindowID id, const wxString& label, const wxString& url) :
		wxHyperlinkCtrl() 
	{
	(void)Create(parent, id, label, url, wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE, wxHyperlinkCtrlNameStr);
	}

protected:
	virtual bool AcceptsFocus() const { return false; }

	/*
	virtual bool AcceptsFocusFromKeyboard() const { return false; }
	virtual WXDWORD MSWGetStyle(long style, WXDWORD *exstyle) const wxOVERRIDE
	{
		WXDWORD msStyle = wxHyperlinkCtrl::MSWGetStyle(style, exstyle);
		msStyle &= (~WS_TABSTOP);
		return msStyle;
	}
	*/
};


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

	SetWindowStyle(GetWindowStyle() &(~wxTAB_TRAVERSAL));
	//wxBORDER_NONE
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
	wxBitmap bitmap(L"IDB_LOGOSIGN", wxBITMAP_TYPE_PNG_RESOURCE);
	if (!bitmap.IsOk())
		bitmap = wxBitmap(wxICON(app_icon));

	//aboutpane->AddSpacer(20);

	aboutpane->Add(new wxStaticBitmap(this, wxID_ANY, bitmap),
		0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 20);

	aboutpane->AddSpacer(20);

	wxStaticText *appname = new wxStaticText(this, wxID_ANY, APP_NAME);
	appname->SetFont(wxFontInfo(16).Bold());
	aboutpane->Add(appname, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 40);
	aboutpane->AddSpacer(20);

	// about info
	wxGridSizer *aboutinfo = new wxGridSizer(2, 10, 10);
	aboutinfo->Add(new wxStaticText(this, ID_DIABLEANY, wxString::Format(_T("Version: %s"), APP_VERSION)), 0, wxALIGN_RIGHT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_BUILD), 1, wxEXPAND | wxALIGN_LEFT);

	aboutinfo->AddSpacer(1);
	aboutinfo->AddSpacer(1);
	//aboutinfo->Add(new wxStaticText(this, wxID_ANY, _(" ")), 0, wxALIGN_RIGHT);
	//aboutinfo->Add(new wxStaticText(this, wxID_ANY, _(" ")), 1, wxEXPAND | wxALIGN_LEFT);

	aboutinfo->Add(new wxStaticText(this, ID_DIABLEANY, _("Author ")), 0, wxALIGN_RIGHT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_MAINT), 1, wxEXPAND | wxALIGN_LEFT);

	aboutinfo->Add(new wxStaticText(this, ID_DIABLEANY, _("Home Page ")), 0, wxALIGN_RIGHT);
	aboutinfo->Add(new NoFocusLink(this, wxID_ANY, APP_WEBSITETEXT, APP_WEBSITEURL), 1, wxEXPAND | wxALIGN_LEFT);
	
	aboutinfo->Add(new wxStaticText(this, ID_DIABLEANY, _("E-mail ")), 0, wxALIGN_RIGHT);
	aboutinfo->Add(new NoFocusLink(this, wxID_ANY, APP_EMAILTEXT, APP_EMAILURL), 1, wxEXPAND | wxALIGN_LEFT);
	
	aboutinfo->Add(new wxStaticText(this, ID_DIABLEANY, _("Licence type ")),0, wxALIGN_RIGHT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_LICENCE),1, wxEXPAND | wxALIGN_LEFT);

	aboutinfo->Add(new wxStaticText(this, ID_DIABLEANY, _("G-Code Meta Compiler ")),0, wxALIGN_RIGHT);
	aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_GCMCAUTHOR),1, wxEXPAND | wxALIGN_LEFT);

	aboutinfo->Add(new wxStaticText(this, ID_DIABLEANY, _("")), 0, wxALIGN_RIGHT);
	aboutinfo->Add(new NoFocusLink(this, wxID_ANY, APP_GCMCHOMEPAGE, APP_GCMCHOMEPAGEURL), 1, wxEXPAND | wxALIGN_LEFT);
	aboutinfo->AddSpacer(1);
	aboutinfo->AddSpacer(1);

	aboutpane->Add(aboutinfo, 1, wxEXPAND);
	aboutpane->Add(new wxStaticText(this, ID_DIABLEANY, WXSTRINGCOPYRIGHT), 0, wxALIGN_CENTER);

	wxBoxSizer *totalpane = new wxBoxSizer(wxHORIZONTAL);
	totalpane->Add(aboutpane, 0, wxEXPAND | wxALL, 30);

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
	wxColor fgColor_dis = clrs->Get(ColourScheme::WINDOW_TEXT_DISABLE);
	wxColor fghp = clrs->Get(ColourScheme::HYPERLINK_TEXT);


	SetBackgroundColour(bgColor);
	SetForegroundColour(fgColor);

	wxWindowList::compatibility_iterator node = GetChildren().GetFirst();
	while (node)
	{
		wxWindow* child = node->GetData();
		child->SetBackgroundColour(bgColor);		
		if (child->GetId() == ID_DIABLEANY)
			child->SetForegroundColour(fgColor_dis);
		else
		{
			child->SetForegroundColour(fgColor);
			/*
			wxHyperlinkCtrl *p = dynamic_cast<wxHyperlinkCtrl *>(child);
			if (p)
			{
				p->SetNormalColour(wxColor("RED"));// fghp);
				p->SetVisitedColour(wxColor("RED")); (fghp);
				p->SetHoverColour(wxColor("RED")); (fghp);
			}
			*/
		}

		node = node->GetNext();
	}
}