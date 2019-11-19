////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Pooter
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Pooter_h___
#define ___Pooter_h___
#include <src/entities/Enemy.h>

#include <gamelib/TimeClock.h>

class Sprite;
class SpriteSheet;

class Pooter : public Enemy
{
	bool				alive;
	Vector2f			velocity;
	SpriteSheet*		sheet;
	Sprite*				sprite;
	int					spriteIndex;
	TimeClock			spriteClock;
public:
	Pooter(Scene* s, double x, double y);
	~Pooter();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef getCollisionRectangle() const;
};

#endif
