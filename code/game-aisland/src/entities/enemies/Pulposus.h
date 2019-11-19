////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Pulposus
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Pulposus_h___
#define ___Pulposus_h___
#include <src/entities/Enemy.h>

#include <gamelib/TimeClock.h>

class Sprite;
class SpriteSheet;

class Pulposus : public Enemy
{
	enum STATE
	{
		STATE_UP,
		STATE_DOWN,
		STATE_DEAD,
	};
	
	STATE				state;
	int					health;
	Vector2f			velocity;
	SpriteSheet*		sheet;
	Sprite*				sprite;
	int					spriteIndex;
	int					spriteHints;
	TimeClock			spriteClock;
public:
	Pulposus(Scene* s, double x, double y, int health = 2);
	~Pulposus();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef getCollisionRectangle() const;
};

#endif
