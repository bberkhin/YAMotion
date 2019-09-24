#include "wx/wx.h"
#include <wx/textctrl.h>
#include <wx/statline.h>

#include "mathsimpledlg.h"


enum
{
ID_OPERAND = wxID_HIGHEST,
ID_PARAMETERSLIST,
ID_PLUSBT,
ID_MINUSBT,
ID_MULTISBT,
ID_DEVIDEBT, 
ID_MAXVALUE,
ID_MINVALUE,
ID_INSELECTED
};

using namespace Interpreter;

struct ParamName
{
	char name[5];
	IndexParam id;
};
ParamName param_names[] = {
{"X", PARAM_X}, { "Y", PARAM_Y }, { "Z", PARAM_Z }, { "A", PARAM_A }, { "B", PARAM_B }, { "C", PARAM_C },
{"D", PARAM_D }, { "E", PARAM_E }, { "F", PARAM_F }, { "I", PARAM_I }, { "J", PARAM_J },
{"K", PARAM_K}, { "P", PARAM_P }, { "Q", PARAM_Q }, { "R", PARAM_R }, { "S", PARAM_S }, { "N", PARAM_N } };


MathSimpleDlg::MathSimpleDlg(DoMathSimple *dm, wxWindow *parent, bool hasselection)
	: domath(dm), wxDialog(parent, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize,
		wxDEFAULT_DIALOG_STYLE)//| wxRESIZE_BORDER) 
{
	// sets the application title
	SetTitle(_("GCode calculator"));
	
	wxBoxSizer *clientarea = new wxBoxSizer(wxHORIZONTAL);
	wxCheckListBox *params = new wxCheckListBox(this, ID_PARAMETERSLIST);
	int n = WXSIZEOF(param_names);
	int index;
	for (int i = 0; i < n; ++i)
	{
		index = params->Append(param_names[i].name, &param_names[i].id);
		if (domath->HasParemeter(param_names[i].id))
			params->Check(index, true);
	}

	clientarea->Add(params);//, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	clientarea->Add(10, 0);

	// Add operands

	const wxString operation[] = { "+", "-", "*","/","=" };
	wxRadioBox *operands = new wxRadioBox(this, ID_PLUSBT,
		"Operation",	wxDefaultPosition, wxDefaultSize,
		WXSIZEOF(operation), operation, 0, wxRA_SPECIFY_ROWS);
	
	MathOperationType ot = domath->GetOperation();
	operands->SetSelection(ot - MOT_PLUS);
	
	clientarea->Add(operands);
	clientarea->Add(10, 0);

	wxBoxSizer *inputpane = new wxBoxSizer(wxVERTICAL);
	inputpane->Add(new wxStaticText(this, wxID_ANY, _("Input value:")));
	inputpane->Add(new wxTextCtrl(this, ID_OPERAND, wxString::FromDouble(domath->GetOperand()) ));
	inputpane->Add(0, 10);
	inputpane->Add(new wxStaticLine(this), wxSizerFlags().Expand() );


	double minv, maxv;
	domath->GetMinMax(&minv, &maxv);
	inputpane->Add(new wxStaticText(this, wxID_ANY, _("Min value:")));
	inputpane->Add(new wxTextCtrl(this, ID_MINVALUE, wxString::FromDouble(minv) ));
	inputpane->Add(new wxStaticText(this, wxID_ANY, _("Max value:")));
	inputpane->Add(new wxTextCtrl(this, ID_MAXVALUE, wxString::FromDouble(maxv)));

	inputpane->Add(10, 10);
	inputpane->Add(new wxStaticLine(this), wxSizerFlags().Expand());	
	wxCheckBox *pinsel = new wxCheckBox(this, ID_INSELECTED, _("In selected"));
	pinsel->SetValue(hasselection ? dm->InSelected() : false);
	pinsel->Enable(hasselection);
	inputpane->Add(pinsel);

	clientarea->Add(inputpane);

	// total pane
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	totalpane->Add(clientarea, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	totalpane->Add(0, 10);
	totalpane->Add(CreateStdDialogButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_RIGHT, 2);

	SetSizerAndFit(totalpane);
}


MathSimpleDlg::~MathSimpleDlg()
{
}

bool MathSimpleDlg::GetEditDouble(int id, double *val)
{
	wxWindow *pwnd = FindWindow(id);
	if (pwnd)
	{
		wxTextCtrl *pedit = dynamic_cast<wxTextCtrl *>(pwnd);
		if (pedit)
		{
			wxString label = pedit->GetValue();
			if (label.ToDouble(val))
				return true;
		}
	}
	return false;

}

int MathSimpleDlg::ShowModal()
{
	bool ok = false;
	double val,minv,maxv;
	wxWindow *pwnd;
	int ret = wxDialog::ShowModal();
	

	if (ret == wxID_OK)
	{
		if (GetEditDouble(ID_OPERAND, &val))
			domath->SetOperand(val);

		pwnd = FindWindow(ID_PARAMETERSLIST);
		if (pwnd)
		{
			wxCheckListBox *params = dynamic_cast<wxCheckListBox *>(pwnd);
			if (params)
			{
				domath->ClearParams();
				int n = params->GetCount();

				for (int i = 0; i < n; ++i)
				{
					if (params->IsChecked(i))
					{
						domath->AddParam(*((IndexParam *)params->GetClientData(i)));
						ok = true;
					}
				}
			}
		}
		if (!ok)
		{
			wxMessageBox(_("Please, select at least one parameter"));
			return wxID_CANCEL;
		}

		pwnd = FindWindow(ID_PLUSBT);
		if (pwnd)
		{
			wxRadioBox *operands = dynamic_cast<wxRadioBox *>(pwnd);
			int n = operands->GetSelection();
			domath->SetOperation(MathOperationType(MOT_PLUS + n));
		}

		if (GetEditDouble(ID_MINVALUE, &minv) && GetEditDouble(ID_MAXVALUE, &maxv))
			domath->SetMinMax(minv, maxv);

		wxCheckBox *pinsel = dynamic_cast<wxCheckBox *>(FindWindow(ID_INSELECTED));
		if (pinsel && pinsel->IsEnabled() )
			domath->SetSelected( pinsel->GetValue() );
		else
			domath->SetSelected(false);

		domath->SaveConfig();
	}
	return ret;
}
