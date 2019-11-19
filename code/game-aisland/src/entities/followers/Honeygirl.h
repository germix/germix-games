////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Honeygirl
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Honeygirl_h___
#define ___Honeygirl_h___
#include <src/entities/hero/HeroFollower.h>

#include <gamelib/TimeClock.h>

class Texture;

class Honeygirl : public HeroFollower
{
	TimeClock		clock;
	Texture*		texture;
public:
	Honeygirl(Scene* s, double x, double y);
	~Honeygirl();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
