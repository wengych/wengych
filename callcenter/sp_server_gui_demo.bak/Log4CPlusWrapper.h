
#ifndef __LOG4CPLUS_WRAPPER_
#define __LOG4CPLUS_WRAPPER_

#pragma  once

/*
//	使用方法
//	包含本头文件：
//	#include "Log4CPlusWrapper.h"
//	使用：
//	LogWrapper::Error("创建进程失败");
*/


#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/fileappender.h"
#include <log4cplus/layout.h>
#include "log4cplus/loglevel.h"
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>

#	ifdef _DEBUG
#		ifdef UNICODE
#			pragma comment(lib,"log4cplusUSD.lib")
#		else
#			pragma comment(lib,"log4cplusSD.lib")
#		endif
#	else
#		ifdef UNICODE
#			pragma comment(lib,"log4cplusUS.lib")
#		else
#			pragma comment(lib,"log4cplusS.lib")
#		endif
#	endif

using namespace log4cplus;
using namespace log4cplus::helpers;


static Logger * g_pLogger = NULL;

class LogWrapper
{
private:
	LogWrapper();

public:
	/*
	*@brief FATAL level
	*/
	static void Fatal(const char * pFormat, ...);

	/*
	*@brief ERROR level
	*/
	static void Error(const char * pFormat, ...);

	/*
	*@brief WARN level
	*/
	static void Warn(const char * pFormat, ...);

	/*
	*@brief INFO level
	*/
	static void Info(const char * pFormat, ...);

	/*
	*@brief DEBUG level
	*/
	static void Debug(const char * pFormat, ...);

	/*
	*@brief TRACE level
	*/
	static void Trace(const char * pFormat, ...);

	static std::string GetLevel(log4cplus::LogLevel level);
};


#endif
