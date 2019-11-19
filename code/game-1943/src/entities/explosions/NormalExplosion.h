////////////////////////////////////////////////////////////////////////////////////////////////////
//
// NormalExplosion
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___NormalExplosion_h___
#define ___NormalExplosion_h___
#include <src/entities/explosions/Explosion.h>

#include <gamelib/TimeClock.h>

class Sprite;

class NormalExplosion : public Explosion
{
	Entity*			ref;
	TimeClock		clock;
	Sprite*			sprite;
	int				spriteIndex;
public:
	NormalExplosion(Scene* s, double x, double y, Entity* ref, const char* sound, const char* sprite, double time = 0.05);
	~NormalExplosion();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
