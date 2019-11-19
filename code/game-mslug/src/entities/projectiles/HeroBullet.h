////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBullet | Bala de héroe
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroBullet_h___
#define ___HeroBullet_h___
#include <src/entities/projectiles/HeroProjectile.h>

class HurtableRect;

class HeroBullet : public HeroProjectile
{
public:
	HeroBullet(Scene* scene, double x, double y) : HeroProjectile(scene, x, y)
	{
	}
	~HeroBullet()
	{
	}
public:
	virtual void hurt(HurtableRect* hr) = 0;
};

#endif
