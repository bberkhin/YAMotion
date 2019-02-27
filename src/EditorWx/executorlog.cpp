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

	wxString label = wxString::Format("LINE: %d <font color=#FF00FF>"
		"%s</font>", nline, str.c_str());

	if (num_outputs == 100)
		label = wxString::Format("<font color=#FF0000> More then 100 outputs </font>");

	wxThreadEvent *ev = new wxThreadEvent(wxEVT_THREAD, CHECK_GCODE_UPDATE);
	ev->SetString(label);
	wxQueueEvent(handler, ev);

}

void ExecutorLogWnd::output(const std::string &str, const Coords &position)
{
	if (!handler || !doprint)
		return;

	if (num_outputs >= 100)
		return;
	num_outputs++;

	wxString label = wxString::Format("LINE: %d <font color=#FF00FF>"
		"%s %f %f %f </font>", nline, str.c_str(), position.x, position.y, position.z);

	if (num_outputs == 100)
		label = wxString::Format("<font color=#FF0000> More then 100 outputs </font>");

	wxThreadEvent *ev = new wxThreadEvent(wxEVT_THREAD, CHECK_GCODE_UPDATE);
	ev->SetString(label);
	wxQueueEvent(handler, ev);

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


void LoggerWnd::log_string(int type, const char *s)
{
	if (!handler)
		return;

	wxString label;
	if (type == LOG_ERROR)
		label = wxString::Format("<font color=#FF0000> %s </font>", s);
	else  if (type == LOG_WARNING)
		label = wxString::Format("<font color=#0000FF> %s </font>", s);
	else
		label = wxString::Format("<font color=#800000> %s </font>", s);


	wxThreadEvent *ev = new wxThreadEvent(wxEVT_THREAD, CHECK_GCODE_UPDATE);
	ev->SetString(label);
	wxQueueEvent(handler, ev);
}