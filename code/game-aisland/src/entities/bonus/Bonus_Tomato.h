////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Tomato
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Tomato_h___
#define ___Bonus_Tomato_h___
#include <src/entities/bonus/Bonus_Fruit.h>

class Bonus_Tomato : public Bonus_Fruit
{
public:
	Bonus_Tomato(Scene* s, double x, double y);
	~Bonus_Tomato();
public:
	void activated(Hero* h);
};

#endif
