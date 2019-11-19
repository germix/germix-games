////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Cobra
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Cobra_h___
#define ___Cobra_h___
#include <src/entities/Enemy.h>

#include <gamelib/TimeClock.h>

class Texture;

class Cobra : public Enemy
{
	bool				alive;
	Texture*			texture;
	double				velocityY;
	bool				firstTime;
	TimeClock			attackClock;
public:
	Cobra(Scene* s, double x, double y);
	~Cobra();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef getCollisionRectangle() const;
};

#endif
