#include "wx/wx.h"
#include "mathexpressiondlg.h"

#define USE_EXPRTK 1
#ifdef USE_EXPRTK
#include <exprtk/exprtk.hpp>
#endif


enum { ID_XEXPR = wxID_HIGHEST, ID_YEXPR, ID_ZEXPR };


MathExpressionDlg::MathExpressionDlg(wxWindow *parent)
	:  wxDialog(parent, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize,
		wxDEFAULT_DIALOG_STYLE)//| wxRESIZE_BORDER) 
{
	// sets the application title
	SetTitle(_("GCode expression calculator"));

	wxBoxSizer *inputpane = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer *inputexp = new wxBoxSizer(wxHORIZONTAL);
	inputexp->Add(new wxStaticText(this, wxID_ANY, _("X=")));
	inputexp->Add(new wxTextCtrl(this, ID_XEXPR, "X" ));
	
	inputpane->Add(inputexp);
	inputpane->Add(0, 10);
	
	inputexp = new wxBoxSizer(wxHORIZONTAL);
	inputexp->Add(new wxStaticText(this, wxID_ANY, _("Y=")));
	inputexp->Add(new wxTextCtrl(this, ID_YEXPR, "Y"));

	inputpane->Add(inputexp);
	inputpane->Add(0, 10);


	inputexp = new wxBoxSizer(wxHORIZONTAL);
	inputexp->Add(new wxStaticText(this, wxID_ANY, _("Z=")));
	inputexp->Add(new wxTextCtrl(this, ID_ZEXPR, "Z"));
	inputpane->Add(inputexp);
	inputpane->Add(0, 10);

	// total pane
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	totalpane->Add(inputpane, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	totalpane->Add(0, 10);
	totalpane->Add(CreateStdDialogButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_RIGHT, 2);

	SetSizerAndFit(totalpane);

}


MathExpressionDlg::~MathExpressionDlg()
{
}


void trig_function(const char *s)
{
#ifdef USE_EXPRTK
	typedef exprtk::symbol_table<double> symbol_table_t;
	typedef exprtk::expression<double>     expression_t;
	typedef exprtk::parser<double>             parser_t;

	std::string expression_string(s);// = "clamp(-1.0,sin(2 * pi * x) + cos(x / 2 * pi),+1.0)";

	double x;

	symbol_table_t symbol_table;
	symbol_table.add_variable("X", x);
	symbol_table.add_constants();

	expression_t expression;
	expression.register_symbol_table(symbol_table);

	parser_t parser;
	if (!parser.compile(expression_string, expression))
	{
		wxString errMsg;
		for (std::size_t i = 0; i < parser.error_count(); ++i)
		{
			typedef exprtk::parser_error::type error_t;
			error_t error = parser.get_error(i);
			exprtk::parser_error::update_error(error, expression_string);
			errMsg += wxString::Format("Error[%02d] at line: %d column: %d\n", i, error.line_no, error.column_no);
		}
		wxMessageBox(errMsg);
		return;
	}
		
	x = 10;
	double xres = expression.value();
	wxMessageBox(wxString::Format("xresult = %f", xres));
#endif
}



int MathExpressionDlg::ShowModal()
{
	int ret = wxDialog::ShowModal();

	wxString label;
	std::string str;
	if (ret == wxID_OK)
	{	
		wxTextCtrl *pedit = dynamic_cast<wxTextCtrl *>(FindWindow(ID_XEXPR));
		if (pedit)
		{
			label = pedit->GetValue();
			trig_function(label.c_str());
		}
	}
	return ret;
}