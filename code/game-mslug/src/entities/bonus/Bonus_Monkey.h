////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Monkey | Bonus mono
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Monkey_h___
#define ___Bonus_Monkey_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_Monkey : public Bonus
{
public:
	static const char* NAME;
public:
	Bonus_Monkey(Scene* scene, double x, double y);
	~Bonus_Monkey();
protected:
	void animate(double dt);
	void activate(Hero* hero);
};

#endif

