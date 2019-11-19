////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Coyote
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Coyote_h___
#define ___Coyote_h___
#include <src/entities/Enemy.h>

#include <gamelib/TimeClock.h>

class Sprite;
class SpriteSheet;

class Coyote : public Enemy
{
	enum STATE
	{
		STATE_INACTIVE,
		STATE_WALKING,
		STATE_STOPPED,
		STATE_DEAD,
	};
	STATE			state;
	TimeClock		clock;
	int				health;
	double			velocity;
	SpriteSheet*	sheet;
	Sprite*			sprite;
	int				spriteIndex;
public:
	Coyote(Scene* s, double x, double y);
	~Coyote();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef getCollisionRectangle() const;
};

#endif
