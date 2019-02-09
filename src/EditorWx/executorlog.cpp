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
	 if (!handler || !doprint )
		 return;
	
	 wxString label = wxString::Format("LINE: %d <font color=#FF00FF>"
		 "%s</font>", nline, str.c_str());

	 wxThreadEvent *ev = new wxThreadEvent(wxEVT_THREAD, CHECK_GCODE_UPDATE);
	 ev->SetString(label);
	 wxQueueEvent(handler, ev);	

	 
 }

 void ExecutorLogWnd::output(const std::string &str, const Coords &position)
 {
	if (!handler || !doprint)
		 return;
	
	 wxString label = wxString::Format("LINE: %d <font color=#FF00FF>"
		 "%s %f %f %f </font>", nline, str.c_str(), position.x ,position.y, position.z);

	 wxThreadEvent *ev = new wxThreadEvent(wxEVT_THREAD, CHECK_GCODE_UPDATE);
	 ev->SetString(label);
	 wxQueueEvent(handler, ev);
 
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