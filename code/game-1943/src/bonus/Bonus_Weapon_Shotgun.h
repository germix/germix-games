////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Weapon_Shotgun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Weapon_Shotgun_h___
#define ___Bonus_Weapon_Shotgun_h___
#include <src/Bonus.h>

class Bonus_Weapon_Shotgun : public Bonus
{
public:
	Bonus_Weapon_Shotgun();
	virtual ~Bonus_Weapon_Shotgun();
public:
	virtual void action(Scene* scene, Hero* hero);
};

#endif
