////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyWeaponHandler
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___EnemyWeaponHandler_h___
#define ___EnemyWeaponHandler_h___

class Scene;
class EnemyWeapon;

#include <gamelib/TimeClock.h>

class EnemyWeaponHandler
{
	EnemyWeapon*	weapon;
	TimeClock		clock;
	int				velocity;
public:
	EnemyWeaponHandler(EnemyWeapon* w, double shootTime, int bulletVelocity);
	~EnemyWeaponHandler();
public:
	void update(Scene* scene, double x, double y, double dt);
};

#endif
