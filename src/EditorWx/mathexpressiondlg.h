#pragma once
#include "gcodedefs.h"

class DoMathExpression;

class MathExpressionDlg :	public wxDialog
{
public:
	MathExpressionDlg(DoMathExpression *pmth, wxWindow *parent);
	~MathExpressionDlg();
	virtual int ShowModal();
private:
	void AddExpressionParam(int id, Interpreter::IndexParam p);
private:
	DoMathExpression *mth;
};

