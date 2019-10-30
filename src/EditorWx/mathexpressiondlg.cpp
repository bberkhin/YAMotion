#include "wx/wx.h"
#include "mathexpressiondlg.h"
#include "domath.h"

//#define USE_EXPRTK 0
#ifdef USE_EXPRTK
#include <exprtk/exprtk.hpp>
#endif

#define USE_EXPMUPP 1
#ifdef USE_EXPMUPP 
#include <muParser.h>
//#import "muParser.lib"
#endif


enum { ID_XEXPR = wxID_HIGHEST, ID_YEXPR, ID_ZEXPR };


MathExpressionDlg::MathExpressionDlg(DoMathExpression *pmth, wxWindow *parent, bool hasenabled)
	: mth(pmth),wxDialog(parent, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize,
		wxDEFAULT_DIALOG_STYLE)//| wxRESIZE_BORDER) 
{
	// sets the application title
	SetTitle(_("G-Code expression calculator"));

	wxBoxSizer *inputpane = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer *inputexp = new wxBoxSizer(wxHORIZONTAL);
	inputexp->Add(new wxStaticText(this, wxID_ANY, _("X=")));

	mu::string_type str_expr;
	inputexp->Add(new wxTextCtrl(this, ID_XEXPR, mth->HasParemeter(Interpreter::PARAM_X, str_expr) ? str_expr.c_str() : wxEmptyString));
	
	inputpane->Add(inputexp);
	inputpane->Add(0, 10);
	
	inputexp = new wxBoxSizer(wxHORIZONTAL);
	inputexp->Add(new wxStaticText(this, wxID_ANY, _("Y=")));
	//inputexp->Add(new wxTextCtrl(this, ID_YEXPR, "Y"));
	inputexp->Add(new wxTextCtrl(this, ID_YEXPR, mth->HasParemeter(Interpreter::PARAM_Y, str_expr) ? str_expr.c_str(): wxEmptyString));

	inputpane->Add(inputexp);
	inputpane->Add(0, 10);


	inputexp = new wxBoxSizer(wxHORIZONTAL);
	inputexp->Add(new wxStaticText(this, wxID_ANY, _("Z=")));
	//inputexp->Add(new wxTextCtrl(this, ID_ZEXPR, "Z"));
	inputexp->Add(new wxTextCtrl(this, ID_ZEXPR, mth->HasParemeter(Interpreter::PARAM_Z, str_expr) ? str_expr.c_str() : wxEmptyString));

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


void trig_function(const wchar_t *s)
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
#else if USE_EXPMUPP
	try
	{
		mu::Parser  parser;
		double x,y, xr, yr;
		parser.DefineVar(L"X", &x);
		parser.DefineVar(L"Y", &y);
		parser.DefineVar(L"X_", &xr);
		parser.DefineVar(L"Y_", &yr);
		//parser.DefineVar(L"õ", &x);	
		mu::string_type sLine(s);
		parser.SetExpr(sLine);
		xr = x = 10;
		yr = y = 20;
		int n = parser.GetNumResults();
		double *xres = parser.Eval(n);
		for (int i = 0; i < n; i++)
		{
			wxMessageBox(wxString::Format("xresult %d = %f", i, xres[i]));
		}
	}
	catch (mu::Parser::exception_type &e)
	{
		wxString errMsg;
		errMsg += wxString::Format("Error%s pos: %d\n", e.GetMsg().c_str(), (int)e.GetPos() );
		wxMessageBox(errMsg);		
	}	
	catch (...)
	{
		wxMessageBox(L"Uups some erorr");
	}
#endif
}

void MathExpressionDlg::AddExpressionParam(int id, Interpreter::IndexParam p)
{

	wxTextCtrl *pedit = dynamic_cast<wxTextCtrl *>(FindWindow(id));
	if (pedit)
	{
		wxString label = pedit->GetValue();
		if ( !label.empty() )
			mth->AddParam(p, label.wc_str());
	}
}


int MathExpressionDlg::ShowModal()
{
	int ret = wxDialog::ShowModal();
	
	std::string str;
	if (ret == wxID_OK)
	{	
		mth->ClearParams();
		AddExpressionParam(ID_XEXPR, Interpreter::PARAM_X);
		AddExpressionParam(ID_YEXPR, Interpreter::PARAM_Y);
		AddExpressionParam(ID_ZEXPR, Interpreter::PARAM_Z);
		mth->SaveConfig();
	}
	return ret;
}