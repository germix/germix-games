////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MasknellShotEffect | Efecto de disparo del Masknell
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MasknellShotEffect_h___
#define ___MasknellShotEffect_h___
#include <src/scene/Scene.h>

#include <gamelib/TimeClock.h>

class Sprite;

class MasknellShotEffect : public Entity
{
	int				frame;
	TimeClock		clock;
	Sprite*			sprite;
public:
	MasknellShotEffect(Scene* scene, double x, double y);
	~MasknellShotEffect();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
