////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Explosion
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Explosion_h___
#define ___Explosion_h___
#include <src/entities/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class Explosion : public Entity
{
	Sprite*		sprite;
	int			spriteIndex;
	TimeClock	spriteClock;
public:
	Explosion(Map* m, Scene* s, int x, int y, Sprite* spr, double time);
	~Explosion();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
