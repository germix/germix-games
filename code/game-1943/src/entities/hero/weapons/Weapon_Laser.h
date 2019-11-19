////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Weapon_Laser
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Weapon_Laser_h___
#define ___Weapon_Laser_h___
#include <src/entities/hero/weapons/Weapon.h>

class Weapon_Laser : public Weapon
{
public:
	Weapon_Laser();
	~Weapon_Laser();
public:
	const char* name() const;
	double delay() const;
	double continuity() const;
	void shoot(Scene* scene, double x, double y, bool isStrong, bool isReinforced);
};

#endif
