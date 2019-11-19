////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyWeapon_Missile
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___EnemyWeapon_Missile_h___
#define ___EnemyWeapon_Missile_h___
#include <src/entities/enemies/weapons/EnemyWeapon.h>

class EnemyWeapon_Missile : public EnemyWeapon
{
public:
	EnemyWeapon_Missile();
	~EnemyWeapon_Missile();
public:
	void shoot(Scene* scene, const Vector2f& p, double velocity);
};

#endif
