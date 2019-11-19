////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_WeaponH | Bonus que entrega una arma HeavyMachineGun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_WeaponH_h___
#define ___Bonus_WeaponH_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_WeaponH : public Bonus
{
public:
	static const char* NAME;
public:
	Bonus_WeaponH(Scene* scene, double x, double y);
	~Bonus_WeaponH();
protected:
	void activate(Hero* hero);
};

#endif
