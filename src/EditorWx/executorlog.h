#ifndef EXECUTORLOG_H
#define EXECUTORLOG_H
#include "iexecutor.h"
#include "logconsole.h"


class wxEvtHandler;
class ExecutorLogWnd : public  ExecutorLog
{
public:
	ExecutorLogWnd(wxEvtHandler *lbox, bool needprint = false)
		: handler(lbox),feed_len(0),traverce_len(0), ExecutorLog(needprint) { }

	double get_traverce_len() { return traverce_len;  }
	double get_feed_len() { return feed_len;  }
protected:
	virtual void output(const std::string &str);
	virtual void output(const std::string &str, const Coords &position);
	virtual void addTrackPoint(TypeMove type, const Coords &pt);


private:
	void update_position(const Coords &position);
	double distance(const Coords &cur_position, const Coords &position);
private:
	wxEvtHandler *handler;
	Coords  cur_position;
	double traverce_len;
	double feed_len;
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
