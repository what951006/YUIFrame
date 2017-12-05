#include "stdafx.h"
#include "GlobalFunc.h"





void Debug(const char *format, ...)
{
#ifdef _DEBUG
	time_t curTime;
	time(&curTime);
	tm *p ;
	p=localtime(&curTime);
	fprintf(stdout, "[%d-%02d-%02d %02d:%02d:%02d]---->  ", 
		p->tm_year + 1900, 
		p->tm_mon  + 1,
		p->tm_mday,
		p->tm_hour,
		p->tm_min,
		p->tm_sec);

	va_list argptr;
	va_start(argptr, format);
	vfprintf(stdout, format, argptr);
	va_end(argptr);
	fprintf(stdout, "\n");
#endif
}
