////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_WeaponR | Bonus que entrega una arma RocketLauncher
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_WeaponR_h___
#define ___Bonus_WeaponR_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_WeaponR : public Bonus
{
public:
	static const char* NAME;
public:
	Bonus_WeaponR(Scene* scene, double x, double y);
	~Bonus_WeaponR();
protected:
	void activate(Hero* hero);
};

#endif
