////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Debug
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static char buf[256];

void Debug::log(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vsprintf(buf, fmt, ap);
	fprintf(stderr, "LOG: %s", buf);
	va_end(ap);
}
void Debug::error(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vsprintf(buf, fmt, ap);
	fprintf(stderr, "ERROR: %s", buf);
	va_end(ap);
}
void Debug::warning(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vsprintf(buf, fmt, ap);
	fprintf(stderr, "WARNING: %s", buf);
	va_end(ap);
}
