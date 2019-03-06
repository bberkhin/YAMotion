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
		ev->SetString("More then 100 outputs");
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


void ExecutorLogWnd::addTrackPoint(TypeMove type, const Coords &position)
{
	ExecutorLog::addTrackPoint(type, position);
	double val = distance(cur_position, position);
	update_position(position);
	if (type == fast)
	{
		traverce_len += val;
		//traverce_time += calc_time(val);
	}
	else
	{
		feed_len += val;
		//feed_time += calc_time(cur_feed, val);
	}
}

void ExecutorLogWnd::update_position(const Coords &position)
{
	cur_position = position;
}

double ExecutorLogWnd::distance(const Coords &cur_position, const Coords &position)
{
	double dx = position.x - cur_position.x;
	double dy = position.y - cur_position.y;
	double dz = position.z - cur_position.z;
	return sqrt(dx*dx + dy * dy + dz * dz);
}


void LoggerWnd::log_string(int type, int linen, const char *s)
{
	if (!handler)
		return;

	wxString label(s);
	wxThreadEvent *ev = new wxThreadEvent(wxEVT_THREAD, CHECK_GCODE_UPDATE);
	ev->SetInt(type);
	ev->SetExtraLong(linen);
	ev->SetString(label);
	wxQueueEvent(handler, ev);
}