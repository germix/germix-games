////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CobraBullet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___CobraBullet_h___
#define ___CobraBullet_h___
#include <src/entities/Enemy.h>

#include <gamelib/TimeClock.h>

class Sprite;
class SpriteSheet;

class CobraBullet : public Enemy
{
	int					dir;
	double				maxY;
	double				minY;
	SpriteSheet*		sheet;
	Sprite*				sprite;
	int					spriteIndex;
	TimeClock			spriteClock;
public:
	CobraBullet(Scene* s, double x, double y);
	~CobraBullet();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef getCollisionRectangle() const;
};

#endif
