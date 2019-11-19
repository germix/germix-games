////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBomb | Bomba del h�roe
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroBomb_h___
#define ___HeroBomb_h___
#include <src/entities/projectiles/HeroProjectile.h>

class HeroBomb : public HeroProjectile
{
public:
	HeroBomb(Scene* scene, double x, double y) : HeroProjectile(scene, x, y)
	{
	}
	~HeroBomb()
	{
	}
public:
	virtual void explode() = 0;
};

#endif
