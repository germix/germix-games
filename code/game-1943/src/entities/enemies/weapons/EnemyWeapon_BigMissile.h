////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyWeapon_BigMissile
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___EnemyWeapon_BigMissile_h___
#define ___EnemyWeapon_BigMissile_h___
#include <src/entities/enemies/weapons/EnemyWeapon.h>

class EnemyWeapon_BigMissile : public EnemyWeapon
{
public:
	EnemyWeapon_BigMissile();
	~EnemyWeapon_BigMissile();
public:
	void shoot(Scene* scene, const Vector2f& p, double velocity);
};

#endif
