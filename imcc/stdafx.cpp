#include "stdafx.h"

#ifdef _UNICODE
	std::wostream& cout = std::wcout;
#else
	std::ostream& cout = std::cout;
#endif
