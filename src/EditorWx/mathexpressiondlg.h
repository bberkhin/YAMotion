#pragma once

class MathExpressionDlg :	public wxDialog
{
public:
	MathExpressionDlg(wxWindow *parent);
	~MathExpressionDlg();
	virtual int ShowModal();
};

