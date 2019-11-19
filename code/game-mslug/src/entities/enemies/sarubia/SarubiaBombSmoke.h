////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SarubiaBombSmoke | Efecto de disparo del Sarubia
//
// Germ�n Mart�nez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SarubiaBombSmoke_h___
#define ___SarubiaBombSmoke_h___
#include <src/scene/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class SarubiaBombSmoke : public Entity
{
	int				frame;
	TimeClock		clock;
	Sprite*			sprite;
public:
	SarubiaBombSmoke(Scene* scene, double x, double y);
	~SarubiaBombSmoke();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
