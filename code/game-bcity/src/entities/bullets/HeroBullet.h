////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBullet
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroBullet_h___
#define ___HeroBullet_h___
#include <src/entities/Bullet.h>

class HeroBullet : public Bullet
{
public:
	HeroBullet(Map* m, Scene* s, int x, int y, Direction dir, HeroTank* shooter, bool speedy, bool strong);
	~HeroBullet();
};

#endif