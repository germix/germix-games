////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Ballons
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Ballons_h___
#define ___Ballons_h___

#include <mach/Random.h>

#include <gamelib/TimeClock.h>

class Texture;
class Graphics;

class Ballons
{
	enum
	{
		MAX_BALLONS = 100,
	};
	struct Ballon
	{
		int			x;
		double		y;
		bool		active;
		int			dir;
		double		timeFrame;
		int			frameIndex;
	};
	Ballon		ballons[MAX_BALLONS];
	Texture*	ballonTexture;
	int			nextBallonIndex;
	TimeClock	nextBallonClock;
	Random		nextBallonRandom;
public:
	Ballons();
	~Ballons();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
