#include "wx/wx.h"

#include "executorlog.h"
#include <iostream>
#include <string>
//#include <fstream>
#include <stdio.h>
#include "defsext.h"     // Additional definitions


using namespace std;

void ExecutorLogWnd::output(const std::string &str)
{
	if (!handler || !doprint)
		return;

	if (num_outputs >= 100)
		return;
	num_outputs++;

	wxThreadEvent *ev = new wxThreadEvent(wxEVT_THREAD, CHECK_GCODE_UPDATE);
	if (num_outputs == 100)
	{
		ev->SetInt(LOG_INFORMATIONSUM);
		ev->SetString(_("More then 100 outputs"));
		ev->SetExtraLong(-1);
	}
	else
	{
		ev->SetInt(LOG_INFORMATION);
		ev->SetExtraLong(nline);
		ev->SetString(str.c_str());
	}
	wxQueueEvent(handler, ev);

}

void ExecutorLogWnd::output(const std::string &str, const Coords &position)
{
	if (!handler || !doprint)
		return;

	std::string strn(str);
	strn += "[";
	strn += std::to_string(position.x);
	strn += " ";
	strn += std::to_string(position.y);
	strn += " ";
	strn += std::to_string(position.z);
	strn += "]";
	
	output(strn);
}


void LoggerWnd::log_string(int type, int linen, const char *s)
{
	if (type == LOG_ERROR)
		++errors;

	if (handler)
	{
		wxString label(s);
		wxThreadEvent *ev = new wxThreadEvent(wxEVT_THREAD, CHECK_GCODE_UPDATE);
		ev->SetInt(type);
		ev->SetExtraLong(linen);
		ev->SetString(label);
		wxQueueEvent(handler, ev);
	}
}