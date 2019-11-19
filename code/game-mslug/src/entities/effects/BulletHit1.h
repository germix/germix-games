////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BulletHit1 | Explosión de bala que se genera cuando se golpea contra una entidad
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___BulletHit1_h___
#define ___BulletHit1_h___
#include <src/scene/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class BulletHit1 : public Entity
{
	int				frame;
	TimeClock		clock;
	Sprite*			sprite;
public:
	BulletHit1(Scene* scene, double x, double y);
	~BulletHit1();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
