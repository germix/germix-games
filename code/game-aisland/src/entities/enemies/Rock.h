////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Rock
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Rock_h___
#define ___Rock_h___
#include <src/entities/Enemy.h>

class Texture;

class Rock : public Enemy
{
	Texture* texture;
public:
	Rock(Scene* s, double x, double y);
	~Rock();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef getCollisionRectangle() const;
};

#endif
