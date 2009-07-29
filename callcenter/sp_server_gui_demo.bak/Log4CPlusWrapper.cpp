#include "StdAfx.h"
#include <stdarg.h>
#include "Log4CPlusWrapper.h"

static void get_logger( )
{
	LogLog::getLogLog()->setInternalDebugging(false);
	PropertyConfigurator::doConfigure("log4cplus.properties");
	static Logger root = Logger::getRoot();
	g_pLogger = &root;
}

#define DO_LOGGER(logLevel, pFormat, bufSize)\
	if(NULL == g_pLogger)\
	{\
		get_logger();\
	}\
	if(g_pLogger->isEnabledFor(logLevel))\
	{\
		va_list args;\
		va_start(args, pFormat);\
		char buf[bufSize] = {0};\
		vsnprintf(buf, sizeof(buf), pFormat, args);\
		va_end(args);\
		g_pLogger->forcedLog(logLevel, buf, __FILE__, __LINE__); \
	}

void LogWrapper::Fatal(const char * pFormat, ...)
{
	DO_LOGGER(log4cplus::FATAL_LOG_LEVEL, pFormat, 512);
}


void LogWrapper::Error(const char * pFormat, ...)
{
	DO_LOGGER(log4cplus::ERROR_LOG_LEVEL, pFormat, 512);
}


void LogWrapper::Warn(const char * pFormat, ...)
{
	DO_LOGGER(log4cplus::WARN_LOG_LEVEL, pFormat, 512);
}


void LogWrapper::Info(const char * pFormat, ...)
{
	DO_LOGGER(log4cplus::INFO_LOG_LEVEL, pFormat, 512);
}


void LogWrapper::Debug(const char * pFormat, ...)
{
	DO_LOGGER(log4cplus::DEBUG_LOG_LEVEL, pFormat, 1024);
}


void LogWrapper::Trace(const char * pFormat, ...)
{
	DO_LOGGER(log4cplus::TRACE_LOG_LEVEL, pFormat, 1024);
}

std::string LogWrapper::GetLevel(log4cplus::LogLevel level)
{
	std::string ret;

	switch(level)
	{
	case log4cplus::DEBUG_LOG_LEVEL:
		ret = "DEBUG";
		break;
	case log4cplus::FATAL_LOG_LEVEL:
		ret = "FATAL";
		break;
	case log4cplus::TRACE_LOG_LEVEL:
		ret = "TRACE";
		break;
	case log4cplus::ERROR_LOG_LEVEL:
		ret = "ERROR";
		break;
	case log4cplus::INFO_LOG_LEVEL:
		ret = "INFO";
		break;
	case log4cplus::WARN_LOG_LEVEL:
		ret = "WARN";
		break;
	default:
		ret = "INFO";
		break;
	}
	return ret;
}
