#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <tchar.h>
//#include <windows.h>
#include "imcc/CenwaveHeader.h"
#pragma comment(lib, "imcc/lib/mcutilc.lib")
#pragma comment(lib, "imcc/lib/mcconfc.lib")
#pragma comment(lib, "imcc/lib/mcnetc.lib")
#pragma comment(lib, "imcc/lib/mccorec.lib")
#pragma comment(lib, "imcc/lib/mctracec.lib" )

#pragma once

#ifdef _UNICODE
	typedef std::wstring string;
	typedef std::wstringstream strstream;
	extern std::wostream& cout;
#else
	typedef std::string string;
	typedef std::stringstream strstream;
	extern std::ostream& cout;
#endif
