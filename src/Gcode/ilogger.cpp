//#include "pch.h"
#include "ilogger.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#pragma warning(disable:4996)


#define MAX_MESSAGE_SIZE 512


void ILogger::log(int type, const char *format, ...)
{
    char buffer[MAX_MESSAGE_SIZE];
    va_list args; 
	va_start(args, format);
    vsprintf(buffer, format, args);
	log_string(type, buffer);
}
