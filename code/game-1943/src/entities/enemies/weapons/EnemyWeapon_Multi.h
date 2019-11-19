////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyWeapon_Multi
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___EnemyWeapon_Multi_h___
#define ___EnemyWeapon_Multi_h___
#include <src/entities/enemies/weapons/EnemyWeapon.h>

class EnemyWeapon_Multi : public EnemyWeapon
{
public:
	EnemyWeapon_Multi();
	~EnemyWeapon_Multi();
public:
	void shoot(Scene* scene, const Vector2f& p, double velocity);
};

#endif
