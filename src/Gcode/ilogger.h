#pragma once

#define LOG_WARNING 1
#define LOG_ERROR 2
class ILogger
{    
public:
    void log(int type, const char *format, ...);
	virtual void log_string(int type, const char *s) = 0;
};

//void log_console(const char *format, ...);

//#define log_message(format, ...) log_console(format, ##__VA_ARGS__)

//#define log_warning(format, ...) log_console(format, ##__VA_ARGS__)

//extern Logger g_logger;

//inline std::string to_string(int value)
//{
	//return std::to_string((long long) value);
//}

//inline std::string to_string(double value)
//{
	//return std::to_string((long double) value);
//}
