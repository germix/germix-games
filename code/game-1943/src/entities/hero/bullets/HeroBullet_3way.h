////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBullet_3way
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroBullet_3way_h___
#define ___HeroBullet_3way_h___
#include <src/entities/hero/bullets/HeroBullet.h>

class HeroBullet_3way : public HeroBullet
{
public:
	HeroBullet_3way(Scene* s, double x, double y, double angle, int dir);
	~HeroBullet_3way();
};

#endif