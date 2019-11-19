////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Carrot
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Carrot_h___
#define ___Bonus_Carrot_h___
#include <src/entities/bonus/Bonus_Fruit.h>

class Bonus_Carrot : public Bonus_Fruit
{
public:
	Bonus_Carrot(Scene* s, double x, double y);
	~Bonus_Carrot();
public:
	void activated(Hero* h);
};

#endif
