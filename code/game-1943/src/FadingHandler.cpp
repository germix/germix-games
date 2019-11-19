////////////////////////////////////////////////////////////////////////////////////////////////////
//
// FadingHandler
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/FadingHandler.h>

FadingHandler::FadingHandler(double ___maxTime, int ___maxValue)
{
	time = 0;
	inverted = false;
	maxTime = ___maxTime;
	minValue = 0;
	maxValue = ___maxValue;
	currentValue = 0;
	initialValue = 0;
}
FadingHandler::FadingHandler(double ___maxTime, int ___maxValue, bool ___inverted)
{
	time = 0;
	inverted = ___inverted;
	maxTime = ___maxTime;
	minValue = 0;
	maxValue = ___maxValue;
	if(!inverted)
		currentValue = minValue;
	else
		currentValue = maxValue;
	initialValue = currentValue;
}
FadingHandler::FadingHandler(double ___maxTime, int ___minValue, int ___maxValue, bool ___inverted)
{
	time = 0;
	inverted = ___inverted;
	maxTime = ___maxTime;
	minValue = ___minValue;
	maxValue = ___maxValue;
	if(!inverted)
		currentValue = minValue;
	else
		currentValue = maxValue;
	initialValue = currentValue;
}
FadingHandler::~FadingHandler()
{
}
void FadingHandler::reset(bool inv)
{
	time = 0;
	inverted = inv;
	currentValue = initialValue;
	if(!inverted)
		currentValue = minValue;
	else
		currentValue = maxValue;
}
bool FadingHandler::update(double dt)
{
	if(inverted)
	{
		if(currentValue <= minValue)
		{
			return false;
		}
		time += dt;
		currentValue = maxValue - (int)((maxTime*time)*maxValue);
		if(currentValue < minValue)
		{
			currentValue = minValue;
		}
	}
	else
	{
		if(currentValue >= maxValue)
		{
			return false;
		}
		time += dt;
		currentValue = (int)((maxTime*time)*maxValue);
		if(currentValue > maxValue)
		{
			currentValue = maxValue;
		}
	}
	return true;
}
