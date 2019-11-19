////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Snail
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Snail_h___
#define ___Snail_h___
#include <src/entities/Enemy.h>

#include <gamelib/TimeClock.h>

class Sprite;
class SpriteSheet;

class Snail : public Enemy
{
	bool				alive;
	Vector2f			velocity;
	SpriteSheet*		sheet;
	Sprite*				sprite;
	int					spriteIndex;
	TimeClock			spriteClock;
public:
	Snail(Scene* s, double x, double y);
	~Snail();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef getCollisionRectangle() const;
};

#endif
