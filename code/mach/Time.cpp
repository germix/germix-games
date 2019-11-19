////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Time
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include "Time.h"

unsigned long Time::getNanos()
{
	LARGE_INTEGER freq, counter;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&counter);
	return (unsigned long)((double)(counter.QuadPart) / ((double)(freq.QuadPart) / 1000000000.0));
}
unsigned long Time::getMillis()
{
	return GetTickCount();
}
