////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Ballons
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Ballons.h>
#include <src/Config.h>
#include <src/resources/ResourceManager.h>

#include <mach/Random.h>
#include <mach/Graphics.h>

Ballons::Ballons()
: ballonTexture(null)
, nextBallonIndex(0)
, nextBallonClock(0.02)
{
	memset(ballons, 0, sizeof(ballons));
	ballonTexture = res.findTexture("Ballon");
}
Ballons::~Ballons()
{
}
void Ballons::update(double dt)
{
	for(int i = 0; i < MAX_BALLONS; i++)
	{
		if(ballons[i].active)
		{
			ballons[i].y -= dt*300;
			if(ballons[i].y < -32)
				ballons[i].active = false;
			
			ballons[i].timeFrame += dt;
			if(ballons[i].timeFrame > 0.08)
			{
				ballons[i].timeFrame = 0;
				if(ballons[i].dir == 1)
				{
					ballons[i].frameIndex++;
					if(ballons[i].frameIndex >= 4-1)
						ballons[i].dir = -1;
				}
				else
				{
					ballons[i].frameIndex--;
					if(ballons[i].frameIndex <= 0)
						ballons[i].dir = +1;
				}
			}
		}
	}
	if(nextBallonClock.update(dt))
	{
		ballons[nextBallonIndex].x = nextBallonRandom.nextInt(MAP_WIDTH);
		ballons[nextBallonIndex].y = MAP_HEIGHT + 30;
		ballons[nextBallonIndex].dir = 1;
		ballons[nextBallonIndex].active = true;
		ballons[nextBallonIndex].timeFrame = 0;
		ballons[nextBallonIndex].frameIndex = 0;
		
		if(++nextBallonIndex >= MAX_BALLONS)
			nextBallonIndex = 0;
	}
}
void Ballons::render(Graphics* gr)
{
	for(int i = 0; i < MAX_BALLONS; i++)
	{
		if(ballons[i].active)
		{
			int w = 64/4;
			int h = 32;
			int dx1 = ballons[i].x - 8;
			int dy1 = ballons[i].y;
			int dx2 = dx1+w;
			int dy2 = dy1+h;
			int sx1 = ballons[i].frameIndex*w;
			int sy1 = 0;
			int sx2 = sx1+w;
			int sy2 = sy1+h;
			gr->drawTexture(ballonTexture, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2);
		}
	}
}
