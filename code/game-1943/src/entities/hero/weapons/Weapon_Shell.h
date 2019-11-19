////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Weapon_Shell
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Weapon_Shell_h___
#define ___Weapon_Shell_h___
#include <src/entities/hero/weapons/Weapon.h>

class Weapon_Shell : public Weapon
{
public:
	Weapon_Shell();
	~Weapon_Shell();
public:
	const char* name() const;
	double delay() const;
	double continuity() const;
	void shoot(Scene* scene, double x, double y, bool isStrong, bool isReinforced);
};

#endif
