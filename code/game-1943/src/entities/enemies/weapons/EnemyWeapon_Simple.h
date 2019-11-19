////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyWeapon_Simple
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___EnemyWeapon_Simple_h___
#define ___EnemyWeapon_Simple_h___
#include <src/entities/enemies/weapons/EnemyWeapon.h>

class EnemyWeapon_Simple : public EnemyWeapon
{
public:
	EnemyWeapon_Simple();
	~EnemyWeapon_Simple();
public:
	void shoot(Scene* scene, const Vector2f& p, double velocity);
};

#endif
