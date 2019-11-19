////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bat
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bat_h___
#define ___Bat_h___
#include <src/entities/Enemy.h>

#include <gamelib/TimeClock.h>

class Sprite;
class SpriteSheet;

class Bat : public Enemy
{
	enum STATE
	{
		STATE_INACTIVE,
		STATE_FLYING,
		STATE_DEAD,
	};
	
	STATE			state;
	int				dir;
	double			minY;
	double			maxY;
	Vector2f		velocity;
	SpriteSheet*	sheet;
	Sprite*			sprite;
	int				spriteIndex;
	TimeClock		spriteClock;
public:
	Bat(Scene* s, double x, double y, int baseY);
	~Bat();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef getCollisionRectangle() const;
};

#endif
