////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WoodFire
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___WoodFire_h___
#define ___WoodFire_h___
#include <src/entities/Enemy.h>

#include <gamelib/TimeClock.h>

class Sprite;
class SpriteSheet;

class WoodFire : public Enemy
{
	SpriteSheet*		sheet;
	Sprite*				sprite;
	int					spriteIndex;
	TimeClock			spriteClock;
public:
	WoodFire(Scene* s, double x, double y);
	~WoodFire();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef WoodFire::getCollisionRectangle() const;
};

#endif
