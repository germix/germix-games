////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBullet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroBullet_h___
#define ___HeroBullet_h___
#include <src/entities/Bullet.h>

class HeroBullet : public Bullet
{
protected:
	const double	length;
	const Vector2f	initialPos;
	const int		damageToEnemy;
	const int		damageToBullet;
public:
	HeroBullet(Scene* s, double x, double y, Sprite* sprite, double angle, double length, double velocity, int damageToEnemy, int damageToBullet);
	~HeroBullet();
public:
	void update(double dt);
	void destroy();
	int getDamageToEnemy() const;
	int getDamageToBullet() const;
};

#endif
