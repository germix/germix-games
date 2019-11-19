////////////////////////////////////////////////////////////////////////////////////////////////////
//
// NormalExplosionS | Explosión normal de tamaño pequeño (Small)
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___NormalExplosionS_h___
#define ___NormalExplosionS_h___
#include <src/scene/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class NormalExplosionS : public Entity
{
	int				frame;
	TimeClock		clock;
	Sprite*			sprite;
public:
	NormalExplosionS(Scene* scene, double x, double y);
	~NormalExplosionS();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif

