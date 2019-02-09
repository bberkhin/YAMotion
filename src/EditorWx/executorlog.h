#ifndef EXECUTORLOG_H
#define EXECUTORLOG_H
#include "iexecutor.h"
#include "logconsole.h"


class wxEvtHandler;
class ExecutorLogWnd : public  ExecutorLog
{
public:
	ExecutorLogWnd(wxEvtHandler *lbox, bool needprint = false)
		: handler(lbox), ExecutorLog(needprint) { }

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
