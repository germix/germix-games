////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GrenadeExplosion | Explosi�n de granada
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___GrenadeExplosion_h___
#define ___GrenadeExplosion_h___
#include <src/scene/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class GrenadeExplosion : public Entity
{
	int				frame;
	TimeClock		clock;
	Sprite*			sprite;
public:
	GrenadeExplosion(Scene* scene, double x, double y);
	~GrenadeExplosion();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
