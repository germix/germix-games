////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Fps
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "Fps.h"
#include "Time.h"

Fps::Fps(int fps)
{
	TARGET_FPS = double(fps);
#if defined(TIME_MILLIS)
	OPTIMAL_TIME = 1000.0 / TARGET_FPS;
#else
	OPTIMAL_TIME = 1000000000.0 / TARGET_FPS;
#endif
#if defined(DEBUG_FPS)
	printf("OPTIMAL_TIME=%f\n", OPTIMAL_TIME);
#endif
}
void Fps::init()
{
	ups = 0;
	fps = 0;
	frameTimer = 0;
	
#if defined(TIME_MILLIS)
	lastTime = currentTime = nextSecond = Time::getMillis();
#else
	lastTime = currentTime = Time::getNanos();
	nextSecond = Time::getMillis();
#endif
}
bool Fps::tick(double* deltaTime)
{
	//
	// Obtener tiempo y calcular tiempo transcurrido
	//
	lastTime = currentTime;
#if defined(TIME_MILLIS)
	currentTime = Time::getMillis();
	diffTime = (currentTime - lastTime);
	if(currentTime-nextSecond > 1000)
#else
	currentTime = Time::getNanos();
	diffTime = (currentTime - lastTime);
	if(Time::getMillis()-nextSecond > 1000)
#endif
	{
#if defined(DEBUG_FPS)
		printf("ups: %d, fps: %d\n", ups, fps);
#endif
		fps = 0;
		ups = 0;
		nextSecond += 1000;
	}
	if(diffTime == 0)
	{
		return false;
	}
	ups++;
#if defined(TIME_MILLIS)
	*deltaTime = (double)diffTime / 1000.0;
#else
	*deltaTime = (double)diffTime / 1000000000.0;
#endif

	return true;
}
bool Fps::canRender()
{
	frameTimer += diffTime;
	if(frameTimer > OPTIMAL_TIME)
	{
		fps++;
		frameTimer -= OPTIMAL_TIME;
		return true;
	}
	return false;
}
