////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Weapon_3way
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Weapon_3way_h___
#define ___Bonus_Weapon_3way_h___
#include <src/Bonus.h>

class Bonus_Weapon_3way : public Bonus
{
public:
	Bonus_Weapon_3way();
	virtual ~Bonus_Weapon_3way();
public:
	virtual void action(Scene* scene, Hero* hero);
};

#endif
