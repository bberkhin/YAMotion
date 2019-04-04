#include "wx/wx.h"
#include "wx/html/htmlproc.h"

#include "welcomewnd.h"
#include "standartpaths.h"
#include "configdata.h"


class WelcomProcessor : public wxHtmlProcessor
{
public:
	virtual wxString Process(const wxString& s) const wxOVERRIDE
	{
		wxString r(s);
		ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
		if (config)
		{
			const FileNamesList &files = config->GetFiles();
			if (!files.empty())
			{
				wxString table(_("<table><tr><td>File Name</td><td>Date</td></tr>"));
				int n = 0;
				std::for_each(files.begin(), files.end(),
					[&table, &n](const wxString &p) {
					table += wxString::Format("<tr><td><a href=\"gcode:%d\">%s</a></td><td>%s</td></tr>", n, p, _("Today")); n++; });

				table += ("</table>");
				r.Replace("<lastfiles>", table);
			}
		}
		return r;
	}
};



WelcomeWnd::WelcomeWnd(wxWindow *parent) : wxHtmlWindow()
{
	// tempoary create own frame

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

void WelcomeWnd::SetHomePage()
{
	wxString path_name = StandartPaths::Get()->GetResourcesPath(L"welcome.htm").c_str();
	LoadFile(path_name);
}


void WelcomeWnd::ShowWelcome(bool bShow)
{
	pWelcomeFrame->Show(bShow);
}



wxBEGIN_EVENT_TABLE(WelcomeWnd, wxHtmlWindow)
//EVT_ERASE_BACKGROUND(WelcomeWnd::OnEraseBgEvent)
EVT_HTML_LINK_CLICKED(wxID_ANY, WelcomeWnd::OnHtmlLinkClicked)
wxEND_EVENT_TABLE()

//EVT_HTML_LINK_CLICKED(wxID_ANY, MyFrame::OnHtmlLinkClicked)


void WelcomeWnd::OnHtmlLinkClicked(wxHtmlLinkEvent &event)
{
	// skipping this event the default behaviour (load the clicked URL)
	// will happen...

	const wxString &url = event.GetLinkInfo().GetHref();
	//wxMessageBox(url);

	if (url.BeforeFirst(':') == "gcode")
	{

		long n = 0;
		if (url.After(':').ToLong(&n))
		{
			wxCommandEvent *ev = new wxCommandEvent(wxEVT_MENU, wxID_FILE + n);
			wxQueueEvent(pWelcomeFrame->GetParent(), ev);
			SetHomePage(); // need to reload last file table
		}	
	}
	else
		event.Skip();
}






