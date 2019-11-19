////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyProjectile | Proyectil de enemigo
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___EnemyProjectile_h___
#define ___EnemyProjectile_h___
#include <src/entities/projectiles/Projectile.h>
#include <src/___/Collisionable.h>

class EnemyProjectile : public Projectile, virtual public Collisionable
{
public:
	EnemyProjectile(Scene* scene, double x, double y) : Projectile(scene, x, y)
	{
	}
	~EnemyProjectile()
	{
	}
};

#endif
