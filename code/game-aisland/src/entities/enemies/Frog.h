////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Frog
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Frog_h___
#define ___Frog_h___
#include <src/entities/Enemy.h>

#include <gamelib/TimeClock.h>

class Sprite;
class SpriteSheet;

class Frog : public Enemy
{
	enum STATE
	{
		STATE_IDLE,
		STATE_JUMP,
		STATE_DEAD,
	};
	STATE			state;
	int				health;
	Vector2f		velocity;
	SpriteSheet*	sheet;
	Sprite*			sprite;
	int				spriteIndex;
	TimeClock		spriteClock;
	bool			canJump;
public:
	Frog(Scene* s, double x, double y, int health, bool canJump);
	~Frog();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	Rectanglef getCollisionRectangle() const;
private:
	void jump();
private:
	static const char* getIdleSpriteName(int health)
	{
		return (health == 2) ? "Frog2-Idle" : "Frog1-Idle";
	}
	static const char* getDeadSpriteName(int health)
	{
		return (health == 2) ? "Frog2-Dead" : "Frog1-Dead";
	}
	static const char* getJumpSpriteName(int health)
	{
		return (health == 2) ? "Frog2-Jump" : "Frog1-Jump";
	}
};

#endif
