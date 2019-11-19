////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Swordfish
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Swordfish_h___
#define ___Swordfish_h___
#include <src/entities/Enemy.h>

class Texture;

class Swordfish : public Enemy
{
	bool			alive;
	Texture*		texture;
	Vector2f		velocity;
public:
	Swordfish(Scene* s, double x, double y);
	~Swordfish();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef getCollisionRectangle() const;
};

#endif
