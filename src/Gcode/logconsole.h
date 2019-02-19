#ifndef LOGCONSOLE_H
#define LOGCONSOLE_H
#include "IExecutor.h"
#include "ILogger.h"
#include "gcodedefs.h"


enum TypeMove
{
	fast,
	feedline,
	feedarc
};

class ExecutorLog : public IExecutor
{
public:
    ExecutorLog(bool needprint = true);
	virtual ~ExecutorLog() { }
	void setneedprint(bool needprint = true);
    void set_current_line( int nu_of_line );
    void set_feed_rate(double feed);
    void set_spindle_speed(double speed);
	void set_css_spindlemode(double &diam, double &speed);
	void set_regular_spindlemode();
    void set_tool_change( int toolid);
    void straight_feed(const Coords &position );
    void straight_traverce(const Coords &position );
	void arc_feed(RunnerData *rd, double &end1, double &end2, double &center1, double &center2, int turn, double &end3, double &AA_end, double &BB_end, double &CC_end, double &u, double &v);
    void run_mcode( int toolid);
    void set_end_programm();
	void set_dwell(long millseconds);
	void process_probe(const Coords &position);
	CoordsBox getBox() { return box; }

protected:
	virtual void addTrackPoint(TypeMove type, const Coords &pt);
    virtual void output(const std::string &str  );
	virtual void output(const std::string &str, const Coords &position );
protected:
	int nline;
	bool doprint;
	CoordsBox box;
};


class LoggerConsole : public ILogger
{
public:
	LoggerConsole()  { }
	void log_string(int type, const char *s);
private:

};


#endif // LOGCONSOLE_H
