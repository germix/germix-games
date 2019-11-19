////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Weapon_Shotgun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Weapon_Shotgun_h___
#define ___Weapon_Shotgun_h___
#include <src/entities/hero/weapons/Weapon.h>

class Weapon_Shotgun : public Weapon
{
public:
	Weapon_Shotgun();
	~Weapon_Shotgun();
public:
	const char* name() const;
	double delay() const;
	double continuity() const;
	void shoot(Scene* scene, double x, double y, bool isStrong, bool isReinforced);
};

#endif
