#include "wx/wx.h"
#include <wx/textctrl.h>
#include <wx/statline.h>
#include "flatstaticline.h"
#include "mathsimpledlg.h"
#include "prefs.h"

enum
{
ID_OPERAND = wxID_HIGHEST,
ID_MAXVALUE,
ID_MINVALUE,
ID_INSELECTED,
ID_INNEWFILE,
ID_PLUSBT = wxID_HIGHEST+100
};

using namespace Interpreter;
#define GRID_PARAM_COLUMNS 12
#define Y_MARGIN 10
#define X_MARGIN 7

#define ADD_STATICTEXT_TO_GRID(text) pt = new wxStaticText(this, wxID_ANY, text); \
									gd->Add(pt, 0, wxALIGN_RIGHT); 

#define ADD_PARAM_TO_GRID(text, paramId)	pch = new wxCheckBox(this, 100+paramId, text); \
											if (domath->HasParemeter(paramId)) \
												pch->SetValue(true);\
											gd->Add(pch); 

#define ADD_GRIPPER(margin1,margin2) clientarea->AddSpacer(margin1);\
					pGripper = new FlatStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL); \
					clientarea->Add(pGripper, 0, wxGROW | wxLEFT | wxRIGHT, 0);\
					clientarea->AddSpacer(margin2);

wxString DoubleToString(const double &val)
{
	wxString out;
	std::string st;
	std::stringstream s(st);
	//s << std::fixed;
	//s << std::scientific;
	if ( (s << val) )
	{
		out = s.str().c_str();
	}
	return out;
}

MathSimpleDlg::MathSimpleDlg(DoMathSimple *dm, wxWindow *parent, bool hasselection)
	: domath(dm), wxDialog(parent, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize,
		wxDEFAULT_DIALOG_STYLE)//| wxRESIZE_BORDER) 
{
	// sets the application title
	SetTitle(_("G-Code transformation"));
	
	wxBoxSizer *clientarea = new wxBoxSizer(wxVERTICAL);
	FlatStaticLine *pGripper;
	ADD_GRIPPER(Y_MARGIN, Y_MARGIN);
	// Add Parameters
	wxStaticText *pt;
	wxCheckBox *pch;
	
	wxFlexGridSizer  *gd = new wxFlexGridSizer(GRID_PARAM_COLUMNS, wxSize(10, 5));// 2, 0, 0);	
	ADD_STATICTEXT_TO_GRID(_("Axis: "));
	ADD_PARAM_TO_GRID(L"X", PARAM_X ); //1
	ADD_PARAM_TO_GRID(L"Y", PARAM_Y); //2
	ADD_PARAM_TO_GRID(L"Z", PARAM_Z); //3
	gd->AddSpacer(1); //4
	ADD_PARAM_TO_GRID(L"A", PARAM_A); //5
	ADD_PARAM_TO_GRID(L"B", PARAM_B); //6
	ADD_PARAM_TO_GRID(L"C", PARAM_C); //7
	gd->AddSpacer(1); //8
	ADD_PARAM_TO_GRID(L"U", PARAM_U); //9
	ADD_PARAM_TO_GRID(L"V", PARAM_V); //10
	ADD_PARAM_TO_GRID(L"W", PARAM_W); //11
	ADD_STATICTEXT_TO_GRID(_("Parameters: "));
	ADD_PARAM_TO_GRID(L"D", PARAM_D);  //1
	ADD_PARAM_TO_GRID(L"E", PARAM_E);  //2
	ADD_PARAM_TO_GRID(L"F", PARAM_F);  //3
	ADD_PARAM_TO_GRID(L"I", PARAM_I);  //4
	ADD_PARAM_TO_GRID(L"J", PARAM_J);  //5
	ADD_PARAM_TO_GRID(L"K", PARAM_K);  //6
	ADD_PARAM_TO_GRID(L"P", PARAM_P);  //7
	ADD_PARAM_TO_GRID(L"Q", PARAM_Q);  //8
	ADD_PARAM_TO_GRID(L"R", PARAM_R);  //9
	ADD_PARAM_TO_GRID(L"S", PARAM_S);  //10
	ADD_PARAM_TO_GRID(L"L", PARAM_L);  //11
	
	ADD_STATICTEXT_TO_GRID(" ");
	ADD_PARAM_TO_GRID(L"H", PARAM_H);  //1
	ADD_PARAM_TO_GRID(L"T", PARAM_T);  //2
	ADD_PARAM_TO_GRID(L"N", PARAM_N);  //3

	wxBoxSizer *inputpane = new wxBoxSizer(wxHORIZONTAL);
	inputpane->AddSpacer(X_MARGIN);
	inputpane->Add(gd, wxEXPAND, wxEXPAND);
	inputpane->AddSpacer(X_MARGIN);

	clientarea->Add(inputpane, wxEXPAND, wxEXPAND);

	

	ADD_GRIPPER(Y_MARGIN, Y_MARGIN);
	

	inputpane = new wxBoxSizer(wxHORIZONTAL);
	inputpane->AddSpacer(X_MARGIN);

	inputpane->Add(new wxStaticText(this, wxID_ANY, _("Value: ")), 0, wxALIGN_CENTER_VERTICAL);
	inputpane->AddSpacer(10);
	inputpane->Add(new wxTextCtrl(this, ID_OPERAND, DoubleToString(domath->GetOperand())), 0, wxALIGN_CENTER_VERTICAL);
	inputpane->AddSpacer(10);
	
	inputpane->AddStretchSpacer();

	inputpane->Add(new wxStaticText(this, wxID_ANY, _("Action: ")), 0, wxALIGN_CENTER_VERTICAL);
	inputpane->AddSpacer(5);

	const wxString operation[] = { "+ ", "- ", "x ","/ ","= " };
	MathOperationType ot = domath->GetOperation();

	/*
	wxRadioBox *operands = new wxRadioBox(this, ID_PLUSBT,
		wxEmptyString, wxDefaultPosition, wxDefaultSize,
		WXSIZEOF(operation), operation, 0, wxRA_SPECIFY_COLS);
	
	operands->SetSelection(ot - MOT_PLUS);
	inputpane->Add(operands, 0, wxALIGN_CENTER_VERTICAL);
	*/
	for (int i = 0; i < WXSIZEOF(operation); ++i)
	{
		wxRadioButton *prb = new wxRadioButton(this, ID_PLUSBT + i, operation[i]);
		prb->SetValue(i == ot);
		inputpane->Add(prb, 0, wxALIGN_CENTER_VERTICAL);
	}

		
	inputpane->AddSpacer(X_MARGIN);
	clientarea->Add(inputpane, 0, wxEXPAND);
	
	ADD_GRIPPER(Y_MARGIN, Y_MARGIN);
// Add min max
	inputpane = new wxBoxSizer(wxHORIZONTAL);
	double minv, maxv;
	inputpane->AddSpacer(X_MARGIN);
	domath->GetMinMax(&minv, &maxv);
	inputpane->Add(new wxStaticText(this, wxID_ANY, _("Min value: ")), 0, wxALIGN_CENTER_VERTICAL);
	inputpane->Add(new wxTextCtrl(this, ID_MINVALUE, DoubleToString(minv)), 0, wxALIGN_CENTER_VERTICAL);
	//inputpane->AddStretchSpacer();
	inputpane->AddSpacer(X_MARGIN*2);
	inputpane->Add(new wxStaticText(this, wxID_ANY, _("Max value: ")), 0, wxALIGN_CENTER_VERTICAL );
	inputpane->Add(new wxTextCtrl(this, ID_MAXVALUE, DoubleToString(maxv)), 0, wxALIGN_CENTER_VERTICAL );
	inputpane->AddSpacer(X_MARGIN);
	clientarea->Add(inputpane, 0, wxEXPAND);
	ADD_GRIPPER(Y_MARGIN, Y_MARGIN);

	inputpane = new wxBoxSizer(wxHORIZONTAL);
	inputpane->AddSpacer(X_MARGIN);
	wxCheckBox *pinnefile = new wxCheckBox(this, ID_INNEWFILE, _("Create new file"));
	pinnefile->SetValue(domath->InNewFile());
	inputpane->Add(pinnefile);
	//inputpane->AddStretchSpacer();
	inputpane->AddSpacer(X_MARGIN * 2);
	wxCheckBox *pinsel = new wxCheckBox(this, ID_INSELECTED, _("In selected"));
	pinsel->SetValue(hasselection ? dm->InSelected() : false);
	pinsel->Enable(hasselection);
	inputpane->Add(pinsel);
	inputpane->AddSpacer(X_MARGIN);
	clientarea->Add(inputpane, 0, wxEXPAND);

	// total pane
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	totalpane->Add(clientarea, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	totalpane->Add(CreateStdDialogButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_RIGHT, 2);

	//UpdateThemeColor();
	SetSizerAndFit(totalpane);

}

void MathSimpleDlg::UpdateThemeColor()
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
	int ret = wxDialog::ShowModal();
	

	if (ret == wxID_OK)
	{
		if (GetEditDouble(ID_OPERAND, &val))
			domath->SetOperand(val);

		domath->ClearParams();
		int n = PARAM_MAX;
		for (int i = 0; i < n; ++i)
		{
			wxCheckBox *pch = dynamic_cast<wxCheckBox *>(FindWindow(i + 100));
			if (pch  && pch->IsChecked())
			{
				domath->AddParam( (IndexParam )i );
				ok = true;
			}
		}

		if (!ok)
		{
			wxMessageBox(_("Please, select at least one parameter"));
			return wxID_CANCEL;
		}

		for (int i = MOT_PLUS; i < MOT_MAX; ++i)
		{
			wxRadioButton *operands = dynamic_cast<wxRadioButton *>(FindWindow(ID_PLUSBT + i));
			if (operands && operands->GetValue() )
			{
				domath->SetOperation(MathOperationType(i));
				break;
			}
		}

		if (GetEditDouble(ID_MINVALUE, &minv) && GetEditDouble(ID_MAXVALUE, &maxv))
			domath->SetMinMax(minv, maxv);

		wxCheckBox *pinsel = dynamic_cast<wxCheckBox *>(FindWindow(ID_INSELECTED));
		if (pinsel && pinsel->IsEnabled() )
			domath->SetSelected( pinsel->GetValue() );
		else
			domath->SetSelected(false);

		wxCheckBox *pnewfile = dynamic_cast<wxCheckBox *>(FindWindow(ID_INNEWFILE));
		if (pnewfile)
			domath->SetInNewFile(pnewfile->GetValue());

		domath->SaveConfig();
	}
	return ret;
}
