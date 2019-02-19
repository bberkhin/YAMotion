#include "logconsole.h"
#include <iostream>
#include <string>
//#include <fstream>
#include <stdio.h>

using namespace std;

ExecutorLog::ExecutorLog(bool needprint) : doprint(needprint)
{

}

void ExecutorLog::setneedprint( bool needprint )
{
	doprint = needprint;
}

void ExecutorLog::output(const std::string &str )
{
	if ( doprint )
		cout << nline << " " << str << "\n" ;
}

void ExecutorLog::output(const std::string &str, const Coords &position )
{
	if (doprint)
	{
		cout << nline << " " << str << " ";
		cout << position.x << " " << position.y << " " << position.z << "\n";
	}
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

 
 void ExecutorLog::set_css_spindlemode(double &diam, double &)
 {
	 output(std::string("set_css_spindle_mode Diam") + std::to_string(diam));
 }
 void ExecutorLog::set_regular_spindlemode() 
 {
	 output(std::string("set_regular_spindlemode"));
 }


 void ExecutorLog::set_tool_change( int toolid)
 {
    output( std::string("set_tool_change ") + std::to_string(toolid) );
 }

 void ExecutorLog::straight_feed(const Coords &position )
 {
    output( std::string("straight_feed ") , position );
	addTrackPoint(feedline, position);
 }
 void ExecutorLog::straight_traverce(const Coords &position )
 {
    output( std::string("straight_traverce"), position );
	addTrackPoint(fast, position);
 }
 
 void ExecutorLog::arc_feed(RunnerData *rd, double &end1, double &end2, double &center1, double &center2, int turn, double &end3, double &AA_end, double &BB_end, double &CC_end, double &u, double &v)
 {
	Coords pt;
	pt.x = end1;
	pt.y = end2;
	pt.z = end3;
    output( std::string("arc_feed"), pt );
	addTrackPoint(feedarc, pt);
 }
 void ExecutorLog::run_mcode( int code )
 {
    output( std::string("run_mcode ") + std::to_string(code) );
 }
 void ExecutorLog::set_end_programm()
 {
    output( std::string("set_end_programm") );
 }

 void ExecutorLog::set_dwell(long millseconds)
 {
	 output(std::string("set_dwell"));
 }

 void ExecutorLog::process_probe(const Coords &position)
 {
	 output(std::string("process_probe "), position);
 }


 void ExecutorLog::addTrackPoint(TypeMove type, const Coords &position)
 {
	 box.addCoords(position);
 }

 void LoggerConsole::log_string(int type, const char *s)
 {
	 if (type == LOG_WARNING )
		cout << "WARNING " << s << "\n";
	 else
		 cout << "ERROR " << s << "\n";
 }
