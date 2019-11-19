////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RShobuBombSmoke | Humo generado en cuando el helicóptero R-Shobu lanza una bomba
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___RShobuBombSmoke_h___
#define ___RShobuBombSmoke_h___
#include <src/scene/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class RShobuBombSmoke : public Entity
{
	int				frame;
	TimeClock		clock;
	Sprite*			sprite;
public:
	RShobuBombSmoke(Scene* scene, double x, double y);
	~RShobuBombSmoke();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
