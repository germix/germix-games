////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SoldierBullet | Bala del soldado
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SoldierBullet_h___
#define ___SoldierBullet_h___
#include <src/entities/projectiles/EnemyProjectile.h>

#include <gamelib/TimeClock.h>

class Sprite;

class SoldierBullet : public EnemyProjectile
{
	Sprite*			sprite;
	int				spriteFrame;
	TimeClock		spriteClock;
	double			velocityX;
public:
	SoldierBullet(Scene* scene, double px, double py, int dirX);
	~SoldierBullet();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	
	void collide(Entity* other);
	Rectanglef collisionRect() const;
};

#endif
