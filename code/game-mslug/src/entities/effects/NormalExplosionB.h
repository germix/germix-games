////////////////////////////////////////////////////////////////////////////////////////////////////
//
// NormalExplosionB | Explosi�n normal de tama�o grande (Big)
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___NormalExplosionB_h___
#define ___NormalExplosionB_h___
#include <src/scene/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class NormalExplosionB : public Entity
{
	int				frame;
	TimeClock		clock;
	Sprite*			sprite;
public:
	NormalExplosionB(Scene* scene, double x, double y);
	~NormalExplosionB();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif

