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
	if (!logger || !doprint)
		return;

	if (num_outputs >= 100)
		return;
	num_outputs++;
	if (num_outputs == 100)
	{
		logger->log(LOG_INFORMATIONSUM, _("More then 100 outputs"));
	}
	else
	{
		logger->log(LOG_INFORMATION, nline, str.c_str() );
	}
}

void ExecutorLogWnd::output(const std::string &str, const Coords &position)
{
	if (!logger || !doprint)
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