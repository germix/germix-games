////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Banana | Bonus banana
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Banana_h___
#define ___Bonus_Banana_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_Banana : public Bonus
{
public:
	static const char* NAME;
public:
	Bonus_Banana(Scene* scene, double x, double y);
	~Bonus_Banana();
protected:
	void animate(double dt);
	void activate(Hero* hero);
};

#endif

