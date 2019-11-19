////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IronNokanaCannonShot | Efecto de disparo del cañón de IronNokana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___IronNokanaCannonShot_h___
#define ___IronNokanaCannonShot_h___

#include <src/scene/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class IronNokanaCannonShot : public Entity
{
	int				frame;
	TimeClock		clock;
	Sprite*			sprite;
public:
	IronNokanaCannonShot(Scene* scene, double x, double y);
	~IronNokanaCannonShot();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
