////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyBullet_Normal
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___EnemyBullet_Normal_h___
#define ___EnemyBullet_Normal_h___
#include <src/entities/enemies/bullets/EnemyBullet.h>

class EnemyBullet_Normal : public EnemyBullet
{
public:
	EnemyBullet_Normal(Scene* s, double x, double y, double angle, double velocity);
	~EnemyBullet_Normal();
};

#endif
