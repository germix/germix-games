////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyBullet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___EnemyBullet_h___
#define ___EnemyBullet_h___
#include <src/entities/Bullet.h>

class Sprite;

class EnemyBullet : public Bullet
{
	const int damage;
public:
	EnemyBullet(Scene* s, double x, double y, Sprite* sprite, double angle, double velocity, int damage);
	~EnemyBullet();
public:
	void update(double dt);
	int collisioned();
};

#endif
