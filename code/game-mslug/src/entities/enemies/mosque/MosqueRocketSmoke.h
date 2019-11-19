////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MosqueRocketSmoke | Humo del lanzamiento del cohete de la mezquita
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MosqueRocketSmoke_h___
#define ___MosqueRocketSmoke_h___
#include <src/scene/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class MosqueRocketSmoke : public Entity
{
	int				frame;
	TimeClock		clock;
	Sprite*			sprite;
public:
	MosqueRocketSmoke(Scene* scene, double x, double y);
	~MosqueRocketSmoke();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
