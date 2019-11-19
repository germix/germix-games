////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Weapon_3way
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Weapon_3way_h___
#define ___Weapon_3way_h___
#include <src/entities/hero/weapons/Weapon.h>

class Weapon_3way : public Weapon
{
public:
	Weapon_3way();
	~Weapon_3way();
public:
	const char* name() const;
	double delay() const;
	double continuity() const;
	void shoot(Scene* scene, double x, double y, bool isStrong, bool isReinforced);
};

#endif
