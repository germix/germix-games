////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Pig | Bonus Babe, el chanchito valiente! =)
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Pig_h___
#define ___Bonus_Pig_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_Pig : public Bonus
{
	enum STATE
	{
		STATE_IDLE,
		STATE_FALLING,
	};
	STATE state;
public:
	static const char* NAME;
public:
	Bonus_Pig(Scene* scene, double x, double y);
	~Bonus_Pig();
protected:
	void animate(double dt);
	void activate(Hero* hero);
};

#endif

