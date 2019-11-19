////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Poop | Bonus caquita
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Poop_h___
#define ___Bonus_Poop_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_Poop : public Bonus
{
public:
	static const char* NAME;
public:
	Bonus_Poop(Scene* scene, double x, double y);
	~Bonus_Poop();
protected:
	void animate(double dt);
	void activate(Hero* hero);
};

#endif
