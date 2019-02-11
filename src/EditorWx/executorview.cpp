#include "wx/wx.h"

#include "ExecutorView.h"
#include <iostream>
#include <string>
//#include <fstream>
#include <stdio.h>
#include "defsext.h"     // Additional definitions


using namespace std;

ExecutorView::ExecutorView(wxEvtHandler *_logger) : ExecutorLog(false),  logger(_logger)
{

}


void ExecutorView::output(const std::string &str)
{
	if (!logger)
		return;

	wxString label = wxString::Format("LINE: %d <font color=#FF00FF>"
		"%s</font>", nline, str.c_str());

//	wxThreadEvent *ev = new wxThreadEvent(wxEVT_THREAD, CHECK_SIMULATE_UPDATE);
//	ev->SetString(label);
	//wxQueueEvent(logger, ev);
}

void ExecutorView::output(const std::string &str, const Coords &position)
{

}

 void ExecutorView::addTrackPoint(TypeMove type, const Coords &position)
 {
	 ExecutorLog::addTrackPoint(type, position);
	 TrackPoint point;
	 point.type = type;
	 point.pt = position;
	 trj.push_back(point);
 }

 