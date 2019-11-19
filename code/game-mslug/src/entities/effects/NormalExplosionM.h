////////////////////////////////////////////////////////////////////////////////////////////////////
//
// NormalExplosionM | Explosi�n normal de tama�o medio (Medium)
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___NormalExplosionM_h___
#define ___NormalExplosionM_h___
#include <src/scene/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class NormalExplosionM : public Entity
{
	int				frame;
	TimeClock		clock;
	Sprite*			sprite;
public:
	NormalExplosionM(Scene* scene, double x, double y);
	~NormalExplosionM();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif

