////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TimeClock
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <gamelib/TimeClock.h>

TimeClock::TimeClock()
{
	timeStep = 1;
	elapsedTime = 0;
	relativeTime = 0;
}
TimeClock::TimeClock(double step)
{
	timeStep = step;
	elapsedTime = 0;
	relativeTime = 0;
}
double TimeClock::time()
{
	return elapsedTime;
}
void TimeClock::reset()
{
	elapsedTime = 0;
	relativeTime = 0;
}
void TimeClock::reset(double step)
{
	timeStep = step;
	elapsedTime = 0;
	relativeTime = 0;
}
bool TimeClock::update(double deltaTime)
{
	elapsedTime += deltaTime;
	relativeTime += deltaTime;
	if(relativeTime > timeStep)
	{
		relativeTime -= timeStep;
		return true;
	}
	return false;
}

