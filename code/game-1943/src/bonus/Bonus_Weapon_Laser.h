////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Weapon_Laser
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Weapon_Laser_h___
#define ___Bonus_Weapon_Laser_h___
#include <src/Bonus.h>

class Bonus_Weapon_Laser : public Bonus
{
public:
	Bonus_Weapon_Laser();
	virtual ~Bonus_Weapon_Laser();
public:
	virtual void action(Scene* scene, Hero* hero);
};

#endif
