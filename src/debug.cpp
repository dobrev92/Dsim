#include "debug.h"

#ifdef __DEBUG__ 

#include <iostream>
#include <fstream>
#include <string>
#include <cstdarg>

int dbg_text(const char* format, ...)
{
	va_list args;
	int done;
	char buffer[1000];

	va_start(args, format);
	done = vsprintf(buffer, format, args);
	va_end(args);
	std::string str(buffer);
	std::cout<<str;
	return done;
}

#endif //__DEBUG__
