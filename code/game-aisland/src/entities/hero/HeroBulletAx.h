////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBulletAx
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroBulletAx_h___
#define ___HeroBulletAx_h___
#include <src/entities/hero/HeroBullet.h>

#include <gamelib/TimeClock.h>

class Sprite;

class HeroBulletAx : public HeroBullet
{
public:
	HeroBulletAx(Scene* s, double x, double y, double vx, double vy);
	~HeroBulletAx();
public:
	void stop();
	Rectanglef getCollisionRectangle() const;
};

#endif
