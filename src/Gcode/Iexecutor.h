#pragma once
#include "gcodedefs.h"

using namespace Interpreter;


class IExecutor
{
public:
	virtual ~IExecutor() { }
	virtual void set_current_line(int nu_of_line) = 0;
	virtual void set_feed_rate(double feed) = 0;
	virtual void set_spindle_speed(double speed) = 0;
	virtual void set_css_spindlemode(double &diam, double &speed) = 0;
	virtual void set_regular_spindlemode() = 0;
	virtual void set_tool_change(int toolid) = 0;
	virtual void straight_feed(const Coords &position) = 0;
	virtual void straight_traverce(const Coords &position) = 0;
	virtual void arc_feed(RunnerData *rd, double &end1, double &end2, double &center1, double &center2, int turn, double &end3, double &AA_end, double &BB_end, double &CC_end, double &u, double &v) = 0;
	virtual void run_mcode(int id) = 0;
	virtual void set_end_programm() = 0;
	virtual void set_dwell(long millseconds) = 0;
	virtual void process_probe(const Coords &position) = 0;
	virtual bool stop_parsing() { return false; }
};



