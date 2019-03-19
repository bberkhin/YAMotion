#pragma once
#include "domath.h"

class MathDlg : public wxDialog
{
public:
	MathDlg(DoMath *dm, wxWindow *parent);
	~MathDlg();
	virtual int ShowModal();
private:
	bool GetEditDouble(int id, double *val);
private:
	DoMath *domath;
};
