////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyBullet_Missile
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___EnemyBullet_Missile_h___
#define ___EnemyBullet_Missile_h___
#include <src/entities/enemies/bullets/EnemyBullet.h>

class EnemyBullet_Missile : public EnemyBullet
{
public:
	EnemyBullet_Missile(Scene* s, double x, double y, double angle, double velocity, bool big);
	~EnemyBullet_Missile();
public:
	void update(double dt);
};

#endif
