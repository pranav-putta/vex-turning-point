#ifndef BCI_TIMER_C_INCLUDED
#define BCI_TIMER_C_INCLUDED

#include "timer.h"
#include <chrono>
using namespace std;
using namespace chrono;

void timer_Initialize(timer *timer)
{
	timer->firstCalled = system_clock::now().time_since_epoch().count();
	timer->lastCalled = 0;
	timer->mark = 0;
	timer->hardMark = -1;
	timer->repeatMark = -1;
}

long timer_GetDT(timer *timer)
{
	long dt = system_clock::now().time_since_epoch().count() - timer->lastCalled;
	timer->lastCalled = system_clock::now().time_since_epoch().count();
	return dt;
}

long timer_GetStartingTime(timer *timer)
{
	return timer->firstCalled;
}

long timer_GetDTFromStart(timer *timer)
{
	return system_clock::now().time_since_epoch().count() - timer->firstCalled;
}

void timer_PlaceMarker(timer *timer)
{
	timer->mark = system_clock::now().time_since_epoch().count();
}

void timer_PlaceHardMarker(timer *timer)
{
	if (timer->hardMark == -1)
	{
		timer->hardMark = system_clock::now().time_since_epoch().count();
	}
}

void timer_ClearHardMarker(timer *timer)
{
	timer->hardMark = -1;
}

long timer_GetDTFromMarker(timer *timer)
{
	return timer->mark == -1 ? 0 : system_clock::now().time_since_epoch().count() - timer->mark;
}

long timer_GetDTFromHardMarker(timer *timer)
{
	return timer->hardMark == -1 ? 0 : system_clock::now().time_since_epoch().count() - timer->hardMark;
}

bool timer_Repeat(timer *timer, long timeMs)
{
	if (timer->repeatMark == -1)
	{
		timer->repeatMark = system_clock::now().time_since_epoch().count();
	}

	if (system_clock::now().time_since_epoch().count() - timer->repeatMark >= timeMs)
	{
		timer->repeatMark = -1;
		return true;
	}

	return false;
}

#endif //BCI_TIMER_C_INCLUDED
