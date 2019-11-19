////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SideFighter
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SideFighter_h___
#define ___SideFighter_h___
#include <src/Direction.h>
#include <mach/Vector2f.h>
#include <mach/Rectanglef.h>

#include <gamelib/TimeClock.h>

class Graphics;
class Sprite;
class Scene;
class Hero;
class EnemyBullet;

class SideFighter
{
	enum STATE
	{
		STATE_NONE,
		STATE_ENTER,
		STATE_LEAVE,
		STATE_ACTIVE,
	};
	Vector2f		pos;
	Direction		dir;
	Hero*			hero;
	Scene*			scene;
	STATE			state;
	bool			destroyed;
	Sprite*			sprite;
	int				spriteIndex;

	Sprite*			spriteForNormal;
	Sprite*			spriteForLooping;

	int				health;
	bool			canHurt;
	TimeClock		hurtTime;
public:
	SideFighter(Scene* s, Hero* h, Direction d);
	~SideFighter();
public:
	Rectanglef rect() const;
	void update(double dt);
	void render(Graphics* gr);
	void checkHit(EnemyBullet* bullet);
	bool isDestroyed() const;
private:
	void moveX();
	void moveY();
	bool incrY(double dt);
	bool decrY(double dt);
};

#endif
