////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Coin | Bonus moneda
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Coin_h___
#define ___Bonus_Coin_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_Coin : public Bonus
{
public:
	static const char* NAME;
public:
	Bonus_Coin(Scene* scene, double x, double y);
	~Bonus_Coin();
protected:
	void animate(double dt);
	void activate(Hero* hero);
};

#endif
