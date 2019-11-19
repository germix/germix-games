////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Pineapple
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Pineapple_h___
#define ___Bonus_Pineapple_h___
#include <src/entities/bonus/Bonus_Fruit.h>

class Bonus_Pineapple : public Bonus_Fruit
{
public:
	Bonus_Pineapple(Scene* s, double x, double y);
	~Bonus_Pineapple();
public:
	void activated(Hero* h);
};

#endif
