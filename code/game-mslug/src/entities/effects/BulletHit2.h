////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BulletHit2 | Explosión de bala que se genera cuando se golpea contra un elemento del entorno
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___BulletHit2_h___
#define ___BulletHit2_h___
#include <src/scene/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class BulletHit2 : public Entity
{
	int				frame;
	TimeClock		clock;
	Sprite*			sprite;
public:
	BulletHit2(Scene* scene, double x, double y);
	~BulletHit2();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
