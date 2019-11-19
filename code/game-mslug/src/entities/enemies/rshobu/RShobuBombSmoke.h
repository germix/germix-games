////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RShobuBombSmoke | Humo generado en cuando el helic�ptero R-Shobu lanza una bomba
//
// Germ�n Mart�nez
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
