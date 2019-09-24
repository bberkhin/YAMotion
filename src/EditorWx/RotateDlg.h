#pragma once
#include "domath.h"

class RotateDlg : public wxDialog
{
public:
	RotateDlg(DoMathRotate *dm, wxWindow *parent, bool hasselection);
	~RotateDlg();
	virtual int ShowModal();
private:
	bool GetEditDouble(int id, double *val);
private:
	DoMathRotate *m_domath;
};

