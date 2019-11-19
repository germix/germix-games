////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBullet_Shotgun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroBullet_Shotgun_h___
#define ___HeroBullet_Shotgun_h___
#include <src/entities/hero/bullets/HeroBullet.h>

class HeroBullet_Shotgun : public HeroBullet
{
public:
	HeroBullet_Shotgun(Scene* s, double x, double y, double angle, int count, bool strong);
	~HeroBullet_Shotgun();
};

#endif
