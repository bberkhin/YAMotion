#ifndef EXECUTORLOG_H
#define EXECUTORLOG_H
#include "IExecutor.h"
#include "ILogger.h"

class ExecutorLog : public IExecutor
{
    int nline;
	bool doprint;
public:
    ExecutorLog(bool needprint = true);
	void setneedprint(bool needprint = true);
    void set_current_line( int nu_of_line );
    void set_feed_rate(double feed);
    void set_spindle_speed(double speed);
    void set_tool_change( int toolid);
    void straight_feed(const Coords &position );
    void straight_traverce(const Coords &position );
    void arc_feed(const Coords &position, bool cw );
    void run_mcode( int toolid);
    void set_end_programm();
private:
    void output(const std::string &str  );
    void output(const std::string &str, const Coords &position );
};


class LoggerConsole : public ILogger
{
public:
	LoggerConsole()  { }
	void log_string(int type, const char *s);
private:

};


#endif // EXECUTORLOG_H
