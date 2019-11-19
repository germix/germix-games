////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SoldierBombExplosion | Efecto de explosi�n de la bomba del soldado
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SoldierBombExplosion_h___
#define ___SoldierBombExplosion_h___
#include <src/scene/Entity.h>
#include <gamelib/TimeClock.h>

class Sprite;

class SoldierBombExplosion : public Entity
{
	int				frame;
	TimeClock		clock;
	Sprite*			sprite;
public:
	SoldierBombExplosion(Scene* scene, double x, double y);
	~SoldierBombExplosion();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
