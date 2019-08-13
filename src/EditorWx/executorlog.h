#ifndef EXECUTORLOG_H
#define EXECUTORLOG_H
#include "iexecutor.h"
#include "logconsole.h"


class wxEvtHandler;
class ExecutorLogWnd : public  ExecutorLog
{
public:
	ExecutorLogWnd(ILogger *_logger, bool needprint = false)
		: logger(_logger), num_outputs(0), ExecutorLog(needprint) { }
protected:
	virtual void output(const std::string &str);
	virtual void output(const std::string &str, const Coords &position);
private:
	ILogger *logger;
	int num_outputs;
};

class LoggerWnd : public ILogger
{
public:
	LoggerWnd(wxEvtHandler *lbox) : errors(0), handler(lbox) { }
	void log_string(int type, int linen, const char *s);
	int errors_count() { return errors; }
private:
	wxEvtHandler *handler;
	int errors;
	
};



#endif // EXECUTORLOG_H
