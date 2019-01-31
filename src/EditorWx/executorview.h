#pragma once

#include "iexecutor.h"
#include <vector>

enum TypeMove
{
	fast,
	feedline,
	feedarc
} ;


struct TrackPoint
{
	TypeMove type;
	Coords pt;
};

class ExecutorView : public IExecutor
{
public:
	ExecutorView(wxEvtHandler *_logger);
    void set_current_line( int num_of_line );
    void set_feed_rate(double feed);
    void set_spindle_speed(int speed);
    void set_tool_change( int toolid);
    void straight_feed(const Coords &position );
    void straight_traverce(const Coords &position );
    void arc_feed(const Coords &position, bool cw );
    void run_mcode( int toolid);
    void set_end_programm();
	std::vector<TrackPoint> *getTrack() { return &trj; }
	CoordsBox getBox() { return box; }
private:
	void addTrackPoint(TypeMove type, const Coords &pt);
	void output(const std::string &str);
private:
	int nline;
	wxEvtHandler *logger;
	CoordsBox box;
	std::vector<TrackPoint> trj;
};

