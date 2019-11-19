////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ScrapExplosion
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ScrapExplosion_h___
#define ___ScrapExplosion_h___
#include <src/entities/explosions/Explosion.h>

#include <gamelib/TimeClock.h>

class Sprite;

class ScrapExplosion : public Explosion
{
	TimeClock		clock;
	double			angle;		// En radianes
	Sprite*			sprite;
	int				spriteIndex;
public:
	ScrapExplosion(Scene* s, double x, double y, char type, double angle);
	~ScrapExplosion();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
