////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Icicle
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Icicle_h___
#define ___Icicle_h___
#include <src/entities/Enemy.h>

#include <gamelib/TimeClock.h>

class Sprite;
class SpriteSheet;

class Icicle : public Enemy
{
	enum STATE
	{
		STATE_INACTIVE,
		STATE_FALLING,
		STATE_CRASH,
	};
	STATE			state;
	SpriteSheet*	sheet;
	Sprite*			sprite;
	Vector2f		velocity;
	TimeClock		crashClock;
public:
	Icicle(Scene* s, double x, double y);
	~Icicle();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	Rectanglef getCollisionRectangle() const;
};

#endif
