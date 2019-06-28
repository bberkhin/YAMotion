#pragma once

#define LOG_WARNING 1
#define LOG_ERROR 2
#define LOG_INFORMATION 3
#define LOG_INFORMATIONSUM 4

class ILogger
{    
public:
    void log(int type, int linen, const char *format, ...);
	void log(int type, const char *format, ...);
	virtual void log_string(int type, int linen, const char *s) = 0;
	virtual int errors_count() = 0;
};

