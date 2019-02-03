#include "wx/wx.h"

#include "executorlog.h"
#include <iostream>
#include <string>
//#include <fstream>
#include <stdio.h>
#include "defsext.h"     // Additional definitions


using namespace std;

ExecutorLog::ExecutorLog()
{

}

void ExecutorLog::output(const std::string &str )
{
    cout << nline << " " << str << "\n" ;
}

void ExecutorLog::output(const std::string &str, const Coords &position )
{
    cout << nline << " " << str << " ";
    cout << position.x << " " << position.y << " " <<position.z << "\n";
}

 void ExecutorLog::set_current_line( int num_of_line )
 {
     nline = num_of_line;
 }

 void ExecutorLog::set_feed_rate(double feed)
 {
    output( std::string("set_feed_rate ") + std::to_string(feed) );
 }
 void ExecutorLog::set_spindle_speed(double speed)
 {
    output( std::string("set_spindle_speed ") + std::to_string(speed) );
 }

 void ExecutorLog::set_tool_change( int toolid)
 {
    output( std::string("set_tool_change ") + std::to_string(toolid) );
 }

 void ExecutorLog::straight_feed(const Coords &position )
 {
    output( std::string("straight_feed ") , position );
 }
 void ExecutorLog::straight_traverce(const Coords &position )
 {
    output( std::string("straight_traverce"), position );
 }
 void ExecutorLog::arc_feed(const Coords &position, bool  )
 {
    output( std::string("arc_feed"), position );
 }
 void ExecutorLog::run_mcode( int code )
 {
    output( std::string("run_mcode ") + std::to_string(code) );
 }
 void ExecutorLog::set_end_programm()
 {
    output( std::string("set_end_programm") );
 }


 void ExecutorLogWnd::output(const std::string &str)
 {	 
	 if (!handler)
		 return;
	 /*
	 wxString label = wxString::Format("LINE: %d <font color=#FF00FF>"
		 "%s</font>", nline, str.c_str());

	 wxThreadEvent *ev = new wxThreadEvent(wxEVT_THREAD, CHECK_GCODE_UPDATE);
	 ev->SetString(label);
	 wxQueueEvent(handler, ev);	
*/ 
	 
 }

 void ExecutorLogWnd::output(const std::string &str, const Coords &position)
 {
	if (!handler)
		 return;
	/*
	 wxString label = wxString::Format("LINE: %d <font color=#FF00FF>"
		 "%s %f %f %f </font>", nline, str.c_str(), position.x ,position.y, position.z);

	 wxThreadEvent *ev = new wxThreadEvent(wxEVT_THREAD, CHECK_GCODE_UPDATE);
	 ev->SetString(label);
	 wxQueueEvent(handler, ev);
	 
*/
 }

 void LoggerWnd::log_string(int type, const char *s)
 {
	 if (!handler)
		 return;

	 wxString label;
	 if (type == LOG_ERROR )
		label = wxString::Format("<font color=#FF0000> %s </font>", s);
	 else 
		label = wxString::Format("<font color=#0000FF> %s </font>", s);

	 
	wxThreadEvent *ev = new wxThreadEvent(wxEVT_THREAD, CHECK_GCODE_UPDATE);
	ev->SetString(label);
	wxQueueEvent(handler, ev);
 }