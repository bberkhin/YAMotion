#ifndef EXECUTORLOG_H
#define EXECUTORLOG_H
#include "iexecutor.h"
#include "logconsole.h"


class wxEvtHandler;
class wxThread;

class ExecutorLogWnd : public  ExecutorLog
{
public:
	ExecutorLogWnd(ILogger *_logger, wxThread *thr = 0, bool needprint = false)
		: logger(_logger), num_outputs(0), ExecutorLog(needprint), m_thread(thr) { }
	virtual bool stop_parsing();
protected:
	virtual void output(const std::string &str);
	virtual void output(const std::string &str, const Coords &position);
protected:
	ILogger *logger;
	int num_outputs;
	wxThread *m_thread;
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
