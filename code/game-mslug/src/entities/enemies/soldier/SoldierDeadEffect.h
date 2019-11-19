////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SoldierDeadEffect | Effecto de la muerte del soldado
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SoldierDeadEffect_h___
#define ___SoldierDeadEffect_h___
#include <src/scene/Entity.h>
#include <gamelib/TimeClock.h>

class Sprite;

class SoldierDeadEffect : public Entity
{
	int				frame;
	TimeClock		clock;
	Sprite*			sprite;
public:
	SoldierDeadEffect(Scene* scene, double x, double y);
	~SoldierDeadEffect();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
