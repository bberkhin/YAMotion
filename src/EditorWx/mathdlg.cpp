#include "wx/wx.h"
#include <wx/textctrl.h>
#include "mathdlg.h"


MathDlg::MathDlg(DoMath *dm, wxWindow *parent)
	: domath(dm), wxDialog(parent, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize,
		wxDEFAULT_DIALOG_STYLE)//| wxRESIZE_BORDER) 
{
	// sets the application title
	SetTitle(_("GCode calculator"));
	wxBoxSizer *inputpane = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *Info = new wxStaticText(this, wxID_ANY, _("Input value:"));
	
	wxTextCtrl *Input = new wxTextCtrl(this, wxID_HIGHEST, wxString::FromDouble(domath->GetOperand()) );
	inputpane->Add(Info);
	inputpane->Add(Input);

	// total pane
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	totalpane->Add(inputpane, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	totalpane->Add(0, 10);
	totalpane->Add(CreateStdDialogButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_RIGHT, 2);


	SetSizerAndFit(totalpane);
}


MathDlg::~MathDlg()
{
}


int MathDlg::ShowModal()
{
	int ret = wxDialog::ShowModal();
	if (ret == wxID_OK)
	{
		wxWindow *pwnd = FindWindow(wxID_HIGHEST);
		if (pwnd)
		{
			wxTextCtrl *pedit = dynamic_cast<wxTextCtrl *>(pwnd);
			if (pedit)
			{
				wxString label = pedit->GetValue();
				double val;
				if (label.ToDouble(&val))
					domath->SetOperand(val);
			}
		}
		domath->AddParam(Interpreter::PARAM_X);
		domath->AddParam(Interpreter::PARAM_Y);
		domath->SaveConfig();
	}
	return ret;

}
