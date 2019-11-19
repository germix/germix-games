////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Skull
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Skull_h___
#define ___Skull_h___
#include <src/entities/Enemy.h>

#include <gamelib/TimeClock.h>

class Sprite;
class SpriteSheet;

class Skull : public Enemy
{
	bool				alive;
	Vector2f			velocity;
	int					deltaIndex;
	SpriteSheet*		sheet;
	Sprite*				sprite;
	int					spriteIndex;
	TimeClock			spriteClock;
public:
	Skull(Scene* s, double x, double y);
	~Skull();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef getCollisionRectangle() const;
};

#endif
