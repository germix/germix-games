////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBullet_Normal
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroBullet_Normal_h___
#define ___HeroBullet_Normal_h___
#include <src/entities/hero/bullets/HeroBullet.h>

class HeroBullet_Normal : public HeroBullet
{
public:
	HeroBullet_Normal(Scene* s, double x, double y, double angle);
	~HeroBullet_Normal();
};

#endif
