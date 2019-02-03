#include "wx/wx.h"

#include "ExecutorView.h"
#include <iostream>
#include <string>
//#include <fstream>
#include <stdio.h>
#include "defsext.h"     // Additional definitions


using namespace std;

ExecutorView::ExecutorView(wxEvtHandler *_logger) : logger(_logger)
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

 void ExecutorView::set_current_line( int num_of_line )
 {
     nline = num_of_line;
 }

 void ExecutorView::set_feed_rate(double feed)
 {
    output( std::string("set_feed_rate ") + std::to_string(feed) );
 }

 void ExecutorView::set_spindle_speed(double speed)
 {
    output( std::string("set_spindle_speed ") + std::to_string(speed) );
 }

 void ExecutorView::set_tool_change( int toolid)
 {
    output( std::string("set_tool_change ") + std::to_string(toolid) );
 }


 void ExecutorView::addTrackPoint(TypeMove type, const Coords &position)
 {
	 TrackPoint point;
	 point.type = type;
	 point.pt = position;
	 trj.push_back(point);
	 box.addCoords(position);
 }

 void ExecutorView::straight_feed(const Coords &position)
 {
	 addTrackPoint(fast, position);
 }

 void ExecutorView::straight_traverce(const Coords &position )
 {
	addTrackPoint(fast, position);	
 }
 void ExecutorView::arc_feed(const Coords &position, bool  )
 {
	 addTrackPoint(feedarc, position);
 }

 void ExecutorView::run_mcode( int code )
 {
    output( std::string("run_mcode ") + std::to_string(code) );
 }
 void ExecutorView::set_end_programm()
 {
    output( std::string("set_end_programm") );
 }

