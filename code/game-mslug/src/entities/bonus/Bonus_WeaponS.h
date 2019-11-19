////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_WeaponS | Bonus que entrega una arma Shotgun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_WeaponS_h___
#define ___Bonus_WeaponS_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_WeaponS : public Bonus
{
public:
	static const char* NAME;
public:
	Bonus_WeaponS(Scene* scene, double x, double y);
	~Bonus_WeaponS();
protected:
	void activate(Hero* hero);
};

#endif
