////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BradleyShootingFire
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___BradleyShootingFire_h___
#define ___BradleyShootingFire_h___
#include <src/scene/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class BradleyShootingFire : public Entity
{
	int				frame;
	TimeClock		clock;
	Sprite*			sprite;
public:
	BradleyShootingFire(Scene* scene, double x, double y);
	~BradleyShootingFire();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
