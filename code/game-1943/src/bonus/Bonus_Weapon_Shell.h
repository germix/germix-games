////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Weapon_Shell
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Weapon_Shell_h___
#define ___Bonus_Weapon_Shell_h___
#include <src/Bonus.h>

class Bonus_Weapon_Shell : public Bonus
{
public:
	Bonus_Weapon_Shell();
	virtual ~Bonus_Weapon_Shell();
public:
	virtual void action(Scene* scene, Hero* hero);
};

#endif
