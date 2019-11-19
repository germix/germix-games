////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bird
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bird_h___
#define ___Bird_h___
#include <src/entities/Enemy.h>

#include <mach/String.h>
#include <gamelib/TimeClock.h>

class Sprite;
class SpriteSheet;

class Bird : public Enemy
{
	int					dir;
	double				min;
	double				max;
	double				vel;

	bool				alive;
	Vector2f			velocity;
	SpriteSheet*		sheet;
	Sprite*				sprite;
	int					spriteHints;
	int					spriteIndex;
	TimeClock			spriteClock;
public:
	Bird(Scene* s, double x, double y, const String& eggEntity = "");
	~Bird();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef getCollisionRectangle() const;
};

#endif
