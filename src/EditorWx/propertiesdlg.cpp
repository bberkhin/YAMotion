#include "wx/wx.h"
#include "propertiesdlg.h"
#include "edit.h"

//----------------------------------------------------------------------------
// EditProperties
//----------------------------------------------------------------------------

EditProperties::EditProperties(Edit *edit,
	long style)
	: wxDialog(edit, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize,
		style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {

	// sets the application title
	SetTitle(_("Properties"));
	wxString text;

	// full name
	wxBoxSizer *fullname = new wxBoxSizer(wxHORIZONTAL);
	fullname->Add(10, 0);
	fullname->Add(new wxStaticText(this, wxID_ANY, _("Full filename"),
		wxDefaultPosition, wxSize(80, wxDefaultCoord)),
		0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	fullname->Add(new wxStaticText(this, wxID_ANY, edit->GetFilename()),
		0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	// text info
	wxGridSizer *textinfo = new wxGridSizer(4, 0, 2);
	textinfo->Add(new wxStaticText(this, wxID_ANY, _("Language"),
		wxDefaultPosition, wxSize(80, wxDefaultCoord)),
		0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxLEFT, 4);
	textinfo->Add(new wxStaticText(this, wxID_ANY, edit->m_language->name),
		0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
	textinfo->Add(new wxStaticText(this, wxID_ANY, _("Lexer-ID: "),
		wxDefaultPosition, wxSize(80, wxDefaultCoord)),
		0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxLEFT, 4);
	text = wxString::Format("%d", edit->GetLexer());
	textinfo->Add(new wxStaticText(this, wxID_ANY, text),
		0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
	wxString EOLtype = wxEmptyString;
	switch (edit->GetEOLMode()) {
	case wxSTC_EOL_CR: {EOLtype = "CR (Unix)"; break; }
	case wxSTC_EOL_CRLF: {EOLtype = "CRLF (Windows)"; break; }
	case wxSTC_EOL_LF: {EOLtype = "CR (Macintosh)"; break; }
	}
	textinfo->Add(new wxStaticText(this, wxID_ANY, _("Line endings"),
		wxDefaultPosition, wxSize(80, wxDefaultCoord)),
		0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxLEFT, 4);
	textinfo->Add(new wxStaticText(this, wxID_ANY, EOLtype),
		0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);

	// text info box
	wxStaticBoxSizer *textinfos = new wxStaticBoxSizer(
		new wxStaticBox(this, wxID_ANY, _("Information")),
		wxVERTICAL);
	textinfos->Add(textinfo, 0, wxEXPAND);
	textinfos->Add(0, 6);

	// statistic
	wxGridSizer *statistic = new wxGridSizer(4, 0, 2);
	statistic->Add(new wxStaticText(this, wxID_ANY, _("Total lines"),
		wxDefaultPosition, wxSize(80, wxDefaultCoord)),
		0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxLEFT, 4);
	text = wxString::Format("%d", edit->GetLineCount());
	statistic->Add(new wxStaticText(this, wxID_ANY, text),
		0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
	statistic->Add(new wxStaticText(this, wxID_ANY, _("Total chars"),
		wxDefaultPosition, wxSize(80, wxDefaultCoord)),
		0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxLEFT, 4);
	text = wxString::Format("%d", edit->GetTextLength());
	statistic->Add(new wxStaticText(this, wxID_ANY, text),
		0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
	statistic->Add(new wxStaticText(this, wxID_ANY, _("Current line"),
		wxDefaultPosition, wxSize(80, wxDefaultCoord)),
		0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxLEFT, 4);
	text = wxString::Format("%d", edit->GetCurrentLine());
	statistic->Add(new wxStaticText(this, wxID_ANY, text),
		0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
	statistic->Add(new wxStaticText(this, wxID_ANY, _("Current pos"),
		wxDefaultPosition, wxSize(80, wxDefaultCoord)),
		0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxLEFT, 4);
	text = wxString::Format("%d", edit->GetCurrentPos());
	statistic->Add(new wxStaticText(this, wxID_ANY, text),
		0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);

	// char/line statistics
	wxStaticBoxSizer *statistics = new wxStaticBoxSizer(
		new wxStaticBox(this, wxID_ANY, _("Statistics")),
		wxVERTICAL);
	statistics->Add(statistic, 0, wxEXPAND);
	statistics->Add(0, 6);

	// total pane
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	totalpane->Add(fullname, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	totalpane->Add(0, 6);
	totalpane->Add(textinfos, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	totalpane->Add(0, 10);
	totalpane->Add(statistics, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	totalpane->Add(0, 6);
	wxButton *okButton = new wxButton(this, wxID_OK, _("OK"));
	okButton->SetDefault();
	totalpane->Add(okButton, 0, wxALIGN_CENTER | wxALL, 10);

	SetSizerAndFit(totalpane);

	ShowModal();
}
