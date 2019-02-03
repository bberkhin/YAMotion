#ifndef EXECUTORLOG_H
#define EXECUTORLOG_H
#include "iexecutor.h"
#include "ilogger.h"

class ExecutorLog : public IExecutor
{
protected:
    int nline;
public:
    ExecutorLog();
    void set_current_line( int nu_of_line );
    void set_feed_rate(double feed);
    void set_spindle_speed(double speed);
    void set_tool_change( int toolid);
    void straight_feed(const Coords &position );
    void straight_traverce(const Coords &position );
    void arc_feed(const Coords &position, bool cw );
    void run_mcode( int toolid);
    void set_end_programm();
protected:
    virtual void output(const std::string &str  );
    virtual void output(const std::string &str, const Coords &position );
};

class wxEvtHandler;
class ExecutorLogWnd : public  ExecutorLog
{
public:
	ExecutorLogWnd(wxEvtHandler *lbox) : handler(lbox) { }

protected:
	virtual void output(const std::string &str);
	virtual void output(const std::string &str, const Coords &position);
private:
	wxEvtHandler *handler;
};

class LoggerWnd : public ILogger
{
public:
	LoggerWnd(wxEvtHandler *lbox) : handler(lbox) { }
	void log_string(int type, const char *s);
private:
	wxEvtHandler *handler;

};



#endif // EXECUTORLOG_H
