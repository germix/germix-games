////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Treasure | Bonus caja de tesoro
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Treasure_h___
#define ___Bonus_Treasure_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_Treasure : public Bonus
{
public:
	static const char* NAME;
public:
	Bonus_Treasure(Scene* scene, double x, double y);
	~Bonus_Treasure();
protected:
	void animate(double dt);
	void activate(Hero* hero);
};

#endif
