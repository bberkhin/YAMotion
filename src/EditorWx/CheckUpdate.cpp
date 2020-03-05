#include "wx/wx.h"
#include <wx/sstream.h>
#include <wx/protocol/http.h>
#include <wx/mstream.h>
#include <wx/html/htmlwin.h>

#include "CheckUpdate.h"
#include "appdefs.h"
#include "StandartPaths.h"
#include "flatstaticline.h"


#define MARGIN_HOR 10
#define MARGIN_VERT 10

CheckUpdateDlg::CheckUpdateDlg(wxWindow *parent)
	: wxDialog(parent, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize,
		wxDEFAULT_DIALOG_STYLE)//| wxRESIZE_BORDER) 
{
	wxString desc, verName;
	int err;
	wxString title(_("Checking for update"));
	if (!DoCheckUpdate(desc, verName, &err))
	{
		if (err == 0 ) //have last version
			wxMessageBox(_("You have the latest version of the application"), title);
		else if (err == 1) // no connection
			wxMessageBox(_T("Unable to connect to update server!"), title);
		else // no version
			wxMessageBox(_T("Somthing goes wrong :( Version Info not found"), title);
		return;
	}
	
	// sets the application title
	SetTitle(title);

	if (desc.IsEmpty())
		desc = _("No description");
	
	
	wxBoxSizer *infopane = new wxBoxSizer(wxVERTICAL);
	wxString verText = wxString::Format(_("Version avalible: %s  (Current: %s)"), verName, APP_VERSION);
	wxStaticText *verCtrl = new wxStaticText(this, wxID_ANY, verText);
	verCtrl->SetFont(wxFontInfo(10).Bold());
	infopane->Add(verCtrl, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT);

	infopane->AddSpacer(MARGIN_VERT);
	infopane->Add(new FlatStaticLine(this, wxLI_HORIZONTAL), 0, wxGROW | wxLEFT | wxRIGHT);
	infopane->AddSpacer(MARGIN_VERT);

	wxHtmlWindow *html;
	wxSize maxSize = wxGetDisplaySize().Scale(0.6, 0.6);
	wxSize okSize = maxSize.Scale(0.8, 1);
	okSize.y = 240;

	html = new wxHtmlWindow(this, wxID_ANY, wxDefaultPosition, okSize, wxHW_NO_SELECTION); //wxHW_SCROLLBAR_NEVER
	html->SetBorders(1);
	
	wxColor clr = this->GetBackgroundColour();
	//clr = wxColor("RED");
	
	html->SetPage(desc);
	html->SetHTMLBackgroundColour(clr);

	int w = html->GetInternalRepresentation()->GetWidth();
	int h = html->GetInternalRepresentation()->GetHeight();

	okSize.x = std::max(okSize.x, w );
	okSize.y = std::max(okSize.y, h);
	
	okSize.x = std::min(okSize.x, maxSize.x);
	okSize.y = std::min(okSize.y, maxSize.y);

	html->SetInitialSize(okSize);

	//htmlwnd->SetPage(desc);
	
	infopane->Add(html, 0, wxEXPAND);
	
	wxBoxSizer *inputpane = new wxBoxSizer(wxHORIZONTAL);
	inputpane->AddSpacer(MARGIN_HOR);
	inputpane->Add(infopane, 1, wxALL | wxEXPAND);
	inputpane->AddSpacer(MARGIN_HOR);
	
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	totalpane->AddSpacer(MARGIN_VERT);
	totalpane->Add(inputpane, 0, wxEXPAND | wxLEFT | wxRIGHT);
	totalpane->AddSpacer(MARGIN_VERT);

	totalpane->Add(CreateStdDialogButtonSizer(wxOK | wxCLOSE), 0, wxALL | wxALIGN_RIGHT, 2);
	wxWindow *okBtn = this->FindWindowById(wxID_OK);
	if (okBtn)
		okBtn->SetLabel(_("Open download page..."));
	SetEscapeId(wxID_CLOSE);
	
	SetSizerAndFit(totalpane);

	if (ShowModal() == wxID_OK)
	{
		wxString url(APP_WEBSITEURL);
		if (HELP_DOWNLOAD != 0 && wcslen(HELP_DOWNLOAD) > 0)
		{
			url += HELP_DOWNLOAD;
			//url += StandartPaths::Get()->GetLanguageCatalog().c_str();
		}
		wxLaunchDefaultApplication(url);
	}
}


CheckUpdateDlg::~CheckUpdateDlg()
{
}


wxBEGIN_EVENT_TABLE(CheckUpdateDlg, wxDialog)
wxEND_EVENT_TABLE()


static bool IsNewVersion(const wxString &version)
{
	// return true if current version older then argument
	// formt: "%d.%d.%d %s",APP_VERSION_MAJOR,APP_VERSION_MINOR,APP_VERSION_REVISION,APP_VERSION_EXTSTR
	wxString major = version.BeforeFirst('.');
	wxString minor = version.AfterFirst('.');
	wxString revision = minor.AfterFirst('.');;
	revision = revision.BeforeFirst('.');
	minor = minor.BeforeFirst('.');
	long imajor = 0;
	major.ToLong(&imajor);
	long iminor = 0;
	minor.ToLong(&iminor);
	long irevision = 0;
	revision.ToLong(&irevision);

	if (imajor > APP_VERSION_MAJOR)
		return true;
	if (iminor > APP_VERSION_MINOR)
		return true;
	if (irevision > APP_VERSION_REVISION)
		return true;
	
	return false;
}

static wxString SubstructXmlValue(const wxString &text, const wxString &tag)
{
	wxString tagfull = wxString::Format("<%s>", tag);
	int start = text.Find(tagfull);
	int end = text.Find(wxString::Format("</%s>", tag));
	if (start < end)
	{
		return text.SubString(start + tagfull.Length(), end - 1);
	}
	else
		return wxEmptyString;
}


bool DoCheckUpdate(wxString &desc, wxString &verName, int *err)
{
	wxHTTP get;
//	wxString url(APP_WEBSITE);
	//wxString url_stream("/version");
	wxString url("onedrive.live.com");
	wxString url_stream("/download?cid=9614716AD031A9C3&resid=9614716AD031A9C3%21117&authkey=AH7ITGsF99dXPfs");
	
//https://onedrive.live.com/download?cid=9614716AD031A9C3&resid=9614716AD031A9C3%21117&authkey=AH7ITGsF99dXPfs
  https://onedrive.live.com/download?cid=9614716AD031A9C3&amp;resid=9614716AD031A9C3%21117&amp;authkey=AH7ITGsF99dXPfs
	get.SetHeader(_T("Content-type"), _T("xml"));


	get.SetTimeout(10); // 10 seconds of timeout instead of 10 minutes ...

	// this will wait until the user connects to the internet. It is important in case of dialup (or ADSL) connections
	int n = 0;
	if (err)
		*err = 0;
	bool ret = false;

	while (!get.Connect(url) && n < 3)  // only the server, no pages here yet ...
	{
		wxSleep(1);
		n++;
	}

	wxApp::IsMainLoopRunning(); // should return true
	wxInputStream *httpStream = get.GetInputStream(url_stream);
	if (get.GetError() == wxPROTO_NOERR)
	{
		wxString res;
		wxStringOutputStream out_stream(&res);
		httpStream->Read(out_stream);
		verName = SubstructXmlValue(res, "version");
		desc = SubstructXmlValue(res, wxString("description") + StandartPaths::Get()->GetLanguageCatalog());
		if (desc.IsEmpty())
			desc = SubstructXmlValue(res, wxString("description"));
		
		if (!verName.IsEmpty())
		{
			ret = IsNewVersion(verName);
		}
		else if (err)
			*err = 2; // no  version info connection
	}
	else if (err)
		*err = 1; // no connection

	wxDELETE(httpStream);
	get.Close();
	return ret;
}
