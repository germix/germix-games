////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Weapon_Normal
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Weapon_Normal_h___
#define ___Weapon_Normal_h___
#include <src/entities/hero/weapons/Weapon.h>

class Weapon_Normal : public Weapon
{
public:
	Weapon_Normal();
	~Weapon_Normal();
public:
	const char* name() const;
	double delay() const;
	double continuity() const;
	void shoot(Scene* scene, double x, double y, bool isStrong, bool isReinforced);
};

#endif
