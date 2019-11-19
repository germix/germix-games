////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroProjectile | Proyectil de héroe
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroProjectile_h___
#define ___HeroProjectile_h___
#include <src/entities/projectiles/Projectile.h>

class HeroProjectile : public Projectile
{
public:
	HeroProjectile(Scene* scene, double x, double y) : Projectile(scene, x, y)
	{
	}
	~HeroProjectile()
	{
	}
};

#endif
