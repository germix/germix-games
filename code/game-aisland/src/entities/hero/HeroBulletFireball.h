////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBulletFireball
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroBulletFireball_h___
#define ___HeroBulletFireball_h___
#include <src/entities/hero/HeroBullet.h>

class HeroBulletFireball : public HeroBullet
{
public:
	HeroBulletFireball(Scene* s, double x, double y, double vx, double vy);
	~HeroBulletFireball();
};

#endif
