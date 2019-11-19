////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_h___
#define ___Bonus_h___
#include <src/entities/Entity.h>

#include <gamelib/TimeClock.h>

class Sound;
class HeroTank;

class Bonus : public Entity
{
protected:
	enum
	{
		BONUS_HELMET = 0,
		BONUS_CLOCK = 1,
		BONUS_SHOVEL = 2,
		BONUS_STAR = 3,
		BONUS_GRENADE = 4,
		BONUS_TANK = 5,
	};
private:
	int			type;
	Sound*		sound;
	bool		visible;
	TimeClock	blinkClock;
	TimeClock	removeClock;
public:
	Bonus(Map* m, Scene* s, int x, int y, int t, Sound* snd);
	~Bonus();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* other);
protected:
	virtual void activated(HeroTank* hero) = 0;
};

#endif
