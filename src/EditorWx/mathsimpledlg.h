#pragma once
#include "domath.h"

class MathSimpleDlg : public wxDialog
{
public:
	MathSimpleDlg(DoMathSimple *dm, wxWindow *parent, bool hasselection);
	~MathSimpleDlg();
	virtual int ShowModal();
private:
	bool GetEditDouble(int id, double *val);
private:
	DoMathSimple *domath;
};
