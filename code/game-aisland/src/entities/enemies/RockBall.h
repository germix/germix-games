////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RockBall
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___RockBall_h___
#define ___RockBall_h___
#include <src/entities/Enemy.h>

class Texture;

class RockBall : public Enemy
{
	bool			active;
	Texture*		texture;
	Vector2f		velocity;
public:
	RockBall(Scene* s, double x, double y);
	~RockBall();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	Rectanglef getCollisionRectangle() const;
};

#endif
