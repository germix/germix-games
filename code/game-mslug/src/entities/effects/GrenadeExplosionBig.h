////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GrenadeExplosionBig | Explosión de granada (grande)
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___GrenadeExplosionBig_h___
#define ___GrenadeExplosionBig_h___
#include <src/scene/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class GrenadeExplosionBig : public Entity
{
	int				frame;
	TimeClock		clock;
	Sprite*			sprite;
public:
	GrenadeExplosionBig(Scene* scene, double x, double y);
	~GrenadeExplosionBig();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif

