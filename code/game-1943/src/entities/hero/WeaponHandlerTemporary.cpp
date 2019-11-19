////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WeaponHandlerTemporary
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/WeaponHandlerTemporary.h>

WeaponHandlerTemporary::WeaponHandlerTemporary()
: maxTime(60.0)
, growTime(20.0)
, handler()
, remainingTime(0)
{
}
WeaponHandlerTemporary::~WeaponHandlerTemporary()
{
}
void WeaponHandlerTemporary::update(double dt)
{
	remainingTime -= dt;
	if(remainingTime < 0)
	{
		remainingTime = 0.0;
		handler.setWeapon(null);
	}
}
bool WeaponHandlerTemporary::trigger(Scene* scene, double x, double y, bool initialTrigger, double pressedTime, bool isReinforced)
{
	return handler.trigger(scene, x, y, initialTrigger, pressedTime, isReinforced);
}
void WeaponHandlerTemporary::reload()
{
	if(handler.getWeapon() != null) // Recargar sólo si hay arma
	{
		remainingTime = maxTime;
	}
}
void WeaponHandlerTemporary::setWeapon(Weapon* w)
{
	handler.setWeapon(w);
	remainingTime += growTime;
	if(remainingTime > maxTime)
		remainingTime = maxTime;
}
Weapon* WeaponHandlerTemporary::getWeapon() const
{
	return handler.getWeapon();
}
double WeaponHandlerTemporary::getRemainingTime() const
{
	return remainingTime;
}
