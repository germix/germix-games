////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusEffect | Efecto visual cuando se obtiene un bonus
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___BonusEffect_h___
#define ___BonusEffect_h___
#include <src/scene/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class BonusEffect : public Entity
{
	int				frame;
	TimeClock		clock;
	Sprite*			sprite;
public:
	BonusEffect(Scene* scene, double x, double y);
	~BonusEffect();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
