#include "wx/wx.h"
#include "wx/html/htmlproc.h"
#include "wx/html/m_templ.h"
#include <wx/statline.h>

#include "appdefs.h"
#include "welcomewnd.h"
#include "standartpaths.h"
#include "configdata.h"
#include "app.h"
#include "prefs.h"
#include "defsext.h"
#include "flatbuttom.h"

#define WELCOME_MARGIN 10

class FooterCell : public wxHtmlContainerCell
{
	
public:
	FooterCell(wxHtmlContainerCell *parent, int height);
	virtual ~FooterCell() { }
	//virtual ~wxHtmlListCell();
	virtual void Layout(int w) wxOVERRIDE;
	virtual void Draw(wxDC& WXUNUSED(dc),
		int WXUNUSED(x), int WXUNUSED(y),
		int WXUNUSED(view_y1), int WXUNUSED(view_y2),
		wxHtmlRenderingInfo& WXUNUSED(info));
	void CalcHeight(int height) { m_calcHeight = height;  }
private:
	int m_calcHeight;
	wxDECLARE_NO_COPY_CLASS(FooterCell);
	
};


FooterCell::FooterCell(wxHtmlContainerCell *p, int height ) : wxHtmlContainerCell(p)
{
	m_calcHeight = 0;
}

void FooterCell::Layout(int w)  
{
	int h = GetParent()->GetHeight();
	wxHtmlContainerCell::Layout(w);	
	m_Height = m_calcHeight; //windowH - h;
	SetPos(0, 0);
	if (m_Cells)
	{
		for (wxHtmlCell *cell = m_Cells; cell; cell = cell->GetNext())
			cell->SetPos(cell->GetPosX(), m_Height - cell->GetHeight());
	}
}

void FooterCell::Draw(wxDC &dc, int x, int y,int view_y1, int view_y2, wxHtmlRenderingInfo &info) 
{
#if 1 // useful for debugging
	dc.SetPen(*wxBLACK_PEN);
	dc.DrawRectangle(x + m_PosX, y + m_PosY, m_Width /* VZ: +1? */, m_Height);
#endif

	wxHtmlContainerCell::Draw(dc, x, y, view_y1, view_y2, info);
}




TAG_HANDLER_BEGIN(FOOTER, "FOOTER")
TAG_HANDLER_PROC(tag)
{
	int ah;

	tag.ScanParam("Height", "%i", &ah);
	wxHtmlContainerCell *c;
	m_WParser->CloseContainer();
	c = m_WParser->OpenContainer();
	m_WParser->SetContainer(new FooterCell(c,ah));
	ParseInner(tag);
	m_WParser->CloseContainer();
	m_WParser->OpenContainer();
	
	return false;
}

TAG_HANDLER_END(MYBIND)



TAGS_MODULE_BEGIN(Footer)

TAGS_MODULE_ADD(FOOTER)

TAGS_MODULE_END(Footer)




class WelcomProcessor : public wxHtmlProcessor
{
public:
	virtual wxString Process(const wxString& s) const wxOVERRIDE
	{
		wxString r(s);
		// set version info
		r.Replace("<verinfo>", APP_VERSION);
		wxString updateString;
		if (wxGetApp().GetUptadeInfo(updateString))
		{
			r.Replace("<updateinfo>", updateString);
			r.Replace("<download>", _("<a href = \"cmd:6005\">Download update</a>"));
		}

		ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
		if (config)
		{
			const FileNamesList &files = config->GetFiles();
			if (!files.empty())
			{
				wxString table(_("<table>")); //<tr><td>File Name</td><td>Date</td></tr>
				int n = 0;
				std::for_each(files.begin(), files.end(),
					[&table, &n](const wxFileName &p) {
					//table += wxString::Format("<tr><td><a href=\"gcode:%d\">%s</a></td><td>%s</td></tr>", n, p, _("Today")); n++; });
					table += wxString::Format("<tr><td><a href=\"gcode:%d\">%s</a></td></tr>", n, p.GetFullName()); n++; });

				table += ("</table>");
				r.Replace("<lastfiles>", table);
			}
		}
		return r;
	}
};



WelcomeWndHtml::WelcomeWndHtml(wxWindow *parent) : wxHtmlWindow()
{
	// tempoary create own frame
	long style = GetWindowStyle();
	SetWindowStyle(style | wxBORDER_NONE );
	pWelcomeFrame = new wxFrame(parent, wxID_ANY, _("Welcome Wnd"));
	Create(pWelcomeFrame);
	SetRelatedFrame(pWelcomeFrame, _("Welcome Wnd1"));
	pWelcomeFrame->Layout();

	WelcomProcessor *processor = new WelcomProcessor;
	processor->Enable(true);
	ReadCustomization(wxConfig::Get());
	AddProcessor(processor);
	SetHomePage();
}

WelcomeWndHtml::~WelcomeWndHtml()
{
}

FooterCell *FindFooter(wxHtmlContainerCell *Cell)
{

	FooterCell *fc = dynamic_cast<FooterCell *>(Cell);
	if (fc)
		return fc;

	if (!Cell)
		return 0;

	for (wxHtmlCell *cell = Cell->GetFirstChild() ; cell; cell = cell->GetNext())
	{
		wxHtmlContainerCell *c = dynamic_cast<wxHtmlContainerCell *>(cell);
		if (!c)
			continue;
		fc = FindFooter(c);
		if (fc)
			return fc;
	}
	return 0;
}

void WelcomeWndHtml::SetHomePage()
{
	wxString path_name = StandartPaths::Get()->GetResourcesPath(L"welcome.htm").c_str();
	LoadFile(path_name);
	UpdateFooter();
	
}


void WelcomeWndHtml::ShowWelcome(bool bShow)
{
	pWelcomeFrame->Show(bShow);
}



wxBEGIN_EVENT_TABLE(WelcomeWndHtml, wxHtmlWindow)
//EVT_ERASE_BACKGROUND(WelcomeWnd::OnEraseBgEvent)
EVT_HTML_LINK_CLICKED(wxID_ANY, WelcomeWndHtml::OnHtmlLinkClicked)
EVT_SIZE(WelcomeWndHtml::OnSize)
wxEND_EVENT_TABLE()

//EVT_HTML_LINK_CLICKED(wxID_ANY, MyFrame::OnHtmlLinkClicked)


void WelcomeWndHtml::RunCommand(const wxString &url, int baseCmd)
{
	long n = 0;
	if (url.After(':').ToLong(&n))
	{
		wxCommandEvent *ev = new wxCommandEvent(wxEVT_MENU, baseCmd + n);
		ev->SetClientData(this);
		wxQueueEvent(pWelcomeFrame->GetParent(), ev);
	}
}
void WelcomeWndHtml::OnHtmlLinkClicked(wxHtmlLinkEvent &event)
{
	// skipping this event the default behaviour (load the clicked URL)
	// will happen...

	const wxString &url = event.GetLinkInfo().GetHref();
	//wxMessageBox(url);
	wxString cmdType = url.BeforeFirst(':');
	if (cmdType == "gcode")
	{
		RunCommand(url,wxID_FILE);
		SetHomePage(); // need to reload last file table	
	}
	else if (cmdType == "cmd")
	{
		RunCommand(url,0);
	}
	else
		event.Skip();
}

void WelcomeWndHtml::UpdateFooter()
{
	FooterCell *fc = FindFooter(m_Cell);
	if (!fc)
		return;
	wxHtmlContainerCell *Cell = fc->GetParent();
	int h = 0;
	for (wxHtmlCell *cell = Cell->GetFirstChild(); cell; cell = cell->GetNext())
	{
		if (fc == cell)
			continue;
		int hc = cell->GetHeight();
		if (hc > h) h = hc;
	}
	wxSize cs = GetSize();
	fc->CalcHeight(cs.y - h);
	m_Cell->Layout(cs.x);
}

void WelcomeWndHtml::OnSize(wxSizeEvent& event)
{
	wxHtmlWindow::OnSize(event);
	UpdateFooter();
	event.Skip();
}





//wxIMPLEMENT_ABSTRACT_CLASS(WelcomeWnd, wxPanel);

wxBEGIN_EVENT_TABLE(WelcomeWnd, wxPanel)
//EVT_BUTTON(ID_TO3DBUTTON, EditorPanel::OnTo3DButton)
wxEND_EVENT_TABLE()

WelcomeWnd::WelcomeWnd(wxWindow *parent) : wxPanel(parent)
{
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	const CommonInfo &common_prefs = Preferences::Get()->Common();

	
	m_fgColor = wxColor(0xeeeeee); //clrs->Get(ColourScheme::WINDOW_TEXT);
	m_fghColor = m_fgColor;
	//m_fghColor = wxColor(0x800000); //clrs->Get(ColourScheme::WINDOW_TEXT);
	m_bgColor = wxColor(0x333333); //clrs->Get(ColourScheme::WINDOW);
	m_bghColor = wxColor(0x4d4d4d);

	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	// Header
	wxStaticText *ptxt = new wxStaticText(this, wxID_ANY, APP_NAME );
	ptxt->SetFont(wxFontInfo(28).Bold());
	totalpane->Add(ptxt, 0, wxEXPAND);
	totalpane->AddSpacer(WELCOME_MARGIN);

	wxBoxSizer *panemain = new wxBoxSizer(wxHORIZONTAL);
	panemain->Add(CreateCommand(), 0, wxLEFT);
	panemain->AddSpacer(WELCOME_MARGIN);
	wxStaticLine *pGripper = new wxStaticLine(this,wxID_ANY,wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	panemain->Add(pGripper, 0, wxGROW | wxLEFT | wxRIGHT, 5);
	panemain->AddSpacer(WELCOME_MARGIN);
	
	panemain->Add(CreateRecentFilesList(), 0, wxEXPAND, wxBORDER);
	panemain->AddSpacer(WELCOME_MARGIN);
	pGripper = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
	panemain->Add(pGripper, 0, wxGROW | wxLEFT | wxRIGHT, 5);
	panemain->AddSpacer(WELCOME_MARGIN);
	panemain->Add(CreateDoc(), 0, wxRIGHT);


	totalpane->Add(panemain, 0, wxEXPAND);
	
	totalpane->Add(CreateFooter(), wxEXPAND, wxEXPAND);
	totalpane->AddSpacer(WELCOME_MARGIN);
	
	UpdateThemeColor();
	SetSizerAndFit(totalpane);
}


void WelcomeWnd::UpdateThemeColor()
{

	SetBackgroundColour(m_bgColor);
	SetForegroundColour(m_fgColor);

	wxWindowList::compatibility_iterator node = GetChildren().GetFirst();
	while (node)
	{
		wxWindow* child = node->GetData();
		child->SetBackgroundColour(m_bgColor);
		child->SetForegroundColour(m_fgColor);
		node = node->GetNext();
	}
	
}

void WelcomeWnd::AddColumnHeader(wxBoxSizer *pane, const wxString &text)
{
	wxStaticText *ph = new wxStaticText(this, wxID_ANY, text);
	ph->SetFont(wxFontInfo(10).Bold()); 
	pane->Add(ph, 0, 0); 
	pane->AddSpacer(WELCOME_MARGIN * 2);
}

void WelcomeWnd::AddCommand(wxBoxSizer *pane, const wxString &text, int cmd, bool footer)
{
	//wxStaticText *ph = new wxStaticText(this, cmd, text);	
	FlatButton *ph = new FlatButton(this, cmd, text, footer ? (FB_BITMAP_LEFT | FB_LABEL_LEFT) : (FB_BITMAP_RIGHT | FB_LABEL_LEFT));
	
	ph->SetCommand(cmd);
	ph->SetFont(wxFontInfo(10));
	ph->SetColour(FlatButton::BackgroundColour, m_bgColor);
	//ph->SetColour(FlatButton::BackgroundColour, wxColor(*wxRED));
	ph->SetColour(FlatButton::HoverBackgroundColour, m_bghColor);
	ph->SetColour(FlatButton::PressBackgroundColour, m_bghColor);
	ph->SetColour(FlatButton::ForegroundColour, m_fgColor);
	ph->SetColour(FlatButton::HoverForegroundColour, m_fghColor);
	ph->SetColour(FlatButton::PressForegroundColour, m_fghColor);

	wxBitmap bmp = wxArtProvider::GetBitmap(wxART_NEW, wxART_MENU);
	if (footer)
	{
		ph->SetBitmap(bmp, 3);
		pane->Add(ph, 0, wxALIGN_BOTTOM);
	}
	else
	{
		ph->SetBitmap(bmp, 30);
		pane->Add(ph, 0, wxEXPAND);
	}
}

void WelcomeWnd::AddRecentFile(wxBoxSizer *pane, const wxFileName &p, int n)
{	
	int cmd = wxID_FILE + n;
	FlatButton *ph = new FlatButton(this,100+n, p.GetFullName(), FB_BITMAP_LEFT);

	ph->SetCommand(cmd);
	ph->SetFont(wxFontInfo(10));
	ph->SetColour(FlatButton::BackgroundColour, m_bgColor);
	ph->SetColour(FlatButton::HoverBackgroundColour, m_bghColor);
	ph->SetColour(FlatButton::PressBackgroundColour, m_bghColor);
	ph->SetColour(FlatButton::ForegroundColour, m_fgColor);
	ph->SetColour(FlatButton::HoverForegroundColour, m_fghColor);
	ph->SetColour(FlatButton::PressForegroundColour, m_fghColor);

	wxBitmap bmp = wxArtProvider::GetBitmap(wxART_NEW, wxART_LIST);
	ph->SetBitmap(bmp, 10 );
	pane->Add(ph, 0, wxEXPAND);
}

wxBoxSizer *WelcomeWnd::CreateCommand()
{
	wxBoxSizer *pane = new wxBoxSizer(wxVERTICAL);
	AddColumnHeader(pane, _("Files"));
	AddCommand(pane, _("Open"), ID_OPENFILE);
	pane->AddSpacer(WELCOME_MARGIN);
	AddCommand(pane, _("New    GCODE"), ID_NEWNC );
	AddCommand(pane, _("New GCMC"), ID_NEWGCMC);
	return pane;
}


void WelcomeWnd::AddHelpLink(wxBoxSizer *pane, const wxString &text, int cmd )
{
	//wxStaticText *ph = new wxStaticText(this, cmd, text);
	FlatButton *ph = new FlatButton(this, cmd, text, FB_LABEL_LEFT);

	ph->SetCommand(cmd);
	ph->SetFont(wxFontInfo(10));
	ph->SetColour(FlatButton::BackgroundColour, m_bgColor);	
	ph->SetColour(FlatButton::HoverBackgroundColour, m_bghColor);
	ph->SetColour(FlatButton::PressBackgroundColour, m_bghColor);
	ph->SetColour(FlatButton::ForegroundColour, m_fgColor);
	ph->SetColour(FlatButton::HoverForegroundColour, m_fghColor);
	ph->SetColour(FlatButton::PressForegroundColour, m_fghColor);

	ph->UpdateSize();
	pane->Add(ph, 0, wxEXPAND);

}


wxBoxSizer *WelcomeWnd::CreateDoc()
{
	wxBoxSizer *pane = new wxBoxSizer(wxVERTICAL);
	AddColumnHeader(pane, _("Help"));
	AddHelpLink(pane, _("Use GCMC to write easy"), 200);
	AddHelpLink(pane, _("Use GCode directly"), 201);
	AddHelpLink(pane, _("Whats News"), 203);
	return pane;
}

wxBoxSizer *WelcomeWnd::CreateRecentFilesList( )
{
	wxBoxSizer *pane = new wxBoxSizer(wxVERTICAL);
	AddColumnHeader(pane, _("Recent Files"));
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	if (config)
	{
		const FileNamesList &files = config->GetFiles();
		if (!files.empty())
		{
			int n = 0;
			WelcomeWnd *parent = this;
			std::for_each(files.begin(), files.end(),
				[&pane, &n, parent](const wxFileName &p) {
				parent->AddRecentFile(pane, p, n++);
				});
		}
	}
	return pane;
}


wxBoxSizer *WelcomeWnd::CreateFooter()
{
	wxBoxSizer *pane = new wxBoxSizer(wxHORIZONTAL);
	pane->AddSpacer(WELCOME_MARGIN);
	wxStaticText *pTxt = new wxStaticText(this, wxID_ANY, APP_COPYRIGTH);
	pTxt->SetFont(wxFontInfo(10));
	pTxt->SetForegroundColour(wxColor(0x999999));

	pane->Add(pTxt , 0, wxALIGN_BOTTOM);
	pane->AddSpacer(WELCOME_MARGIN);
	
	AddCommand(pane, _("Preference"), ID_GLOBALPREFS, true);
	//pane->Add(new wxStaticText(this, wxID_ANY, ), 0, wxALIGN_BOTTOM);
	pane->AddSpacer(WELCOME_MARGIN);
	AddCommand(pane, _("Check for Update"), ID_DOWNLOADUPDATE, true);
	pane->AddStretchSpacer();
	wxBoxSizer *pane1 = new wxBoxSizer(wxVERTICAL);

	pTxt = new wxStaticText(this, wxID_ANY, _("Help us become better."));
	pTxt->SetFont(wxFontInfo(10).Bold());
	pane1->Add(pTxt, 0, wxALIGN_CENTER_HORIZONTAL);
	
	pTxt = new wxStaticText(this, wxID_ANY, _(" Tell us what you liked or what you lack in our application"));
	pTxt->SetFont(wxFontInfo(10));
	pane1->Add(pTxt, 0, wxALIGN_CENTER_HORIZONTAL);

	FlatButton *ph = new FlatButton(this, wxID_ANY, _("WRITE TO US"), FB_LABEL_CENTER);
	ph->SetCommand(ID_WRITEFEEDBACK);
	ph->SetFont(wxFontInfo(11).Bold() );
	ph->SetMargins(-1, 8);

	wxBitmap bmp = wxArtProvider::GetBitmap(wxART_NEW, wxART_OTHER);
	ph->SetBitmap(bmp, 2);
	
	wxColor clrbg("#cc8830");
	wxColor clrbghv("#bb6600");

	ph->SetColour(FlatButton::BackgroundColour, clrbg);
	ph->SetColour(FlatButton::HoverBackgroundColour, clrbghv);
	ph->SetColour(FlatButton::PressBackgroundColour, clrbghv);
	ph->SetColour(FlatButton::ForegroundColour, wxColor(*wxWHITE));
	ph->SetColour(FlatButton::HoverForegroundColour, wxColor(*wxWHITE));
	ph->SetColour(FlatButton::PressForegroundColour, wxColor(*wxWHITE));

	pane1->Add(ph, 0, wxEXPAND );
	pane->Add(pane1, 0, wxRIGHT | wxALIGN_BOTTOM);
	return pane;
}

WelcomeWnd::~WelcomeWnd()
{

}

void WelcomeWnd::OnHtmlLinkClicked(wxHtmlLinkEvent &event)
{

}

