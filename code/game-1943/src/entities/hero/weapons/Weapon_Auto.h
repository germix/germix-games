////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Weapon_Auto
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Weapon_Auto_h___
#define ___Weapon_Auto_h___
#include <src/entities/hero/weapons/Weapon.h>

class Weapon_Auto : public Weapon
{
public:
	Weapon_Auto();
	~Weapon_Auto();
public:
	const char* name() const;
	double delay() const;
	double continuity() const;
	void shoot(Scene* scene, double x, double y, bool isStrong, bool isReinforced);
};

#endif
