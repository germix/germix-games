////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroFollower
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroFollower_h___
#define ___HeroFollower_h___
#include <src/Entity.h>

#include <gamelib/TimeClock.h>

class Hero;

class HeroFollower : public Entity
{
protected:
	enum STATE
	{
		STATE_IDLE,
		STATE_LEAVE,
	};
	Hero*			hero;
	STATE			state;
	Vector2f		velocity;
	int				dy;
	int				dir;
	TimeClock		clock;
	bool			readyX;
	bool			readyY;
public:
	HeroFollower(Scene* s, double x, double y);
	~HeroFollower();
public:
	void update(double dt);
	void leave();
};

#endif
