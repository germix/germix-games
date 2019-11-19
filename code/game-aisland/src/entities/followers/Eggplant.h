////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Eggplant
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Eggplant_h___
#define ___Eggplant_h___
#include <src/entities/hero/HeroFollower.h>

#include <gamelib/TimeClock.h>

class Texture;

class Eggplant : public HeroFollower
{
	TimeClock		clock;
	Texture*		texture;
public:
	Eggplant(Scene* s, double x, double y);
	~Eggplant();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
