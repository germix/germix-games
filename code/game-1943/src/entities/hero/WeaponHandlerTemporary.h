////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WeaponHandlerTemporary
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___WeaponHandlerTemporary_h___
#define ___WeaponHandlerTemporary_h___
#include <src/entities/hero/WeaponHandler.h>

class WeaponHandlerTemporary
{
	const double	maxTime;			// Máximo 60 segundos
	const double	growTime;			// Incremento de a 20 segundos
	
	WeaponHandler	handler;
	double			remainingTime;
public:
	WeaponHandlerTemporary();
	~WeaponHandlerTemporary();
public:
	void update(double dt);
	bool trigger(Scene* scene, double x, double y, bool initialTrigger, double pressedTime, bool isReinforced);
	void reload();
	void setWeapon(Weapon* w);
	Weapon* getWeapon() const;
	double getRemainingTime() const;
};

#endif
