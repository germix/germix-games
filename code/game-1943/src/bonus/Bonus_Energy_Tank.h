////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Energy_Tank
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Energy_Tank_h___
#define ___Bonus_Energy_Tank_h___
#include <src/Bonus.h>

class Bonus_Energy_Tank : public Bonus
{
public:
	Bonus_Energy_Tank();
	virtual ~Bonus_Energy_Tank();
public:
	virtual void action(Scene* scene, Hero* hero);
};

#endif
