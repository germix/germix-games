////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MasknellBullet | Bala del Masknell
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MasknellBullet_h___
#define ___MasknellBullet_h___
#include <src/entities/projectiles/EnemyProjectile.h>

#include <gamelib/TimeClock.h>

class Sprite;

class MasknellBullet : public EnemyProjectile
{
	Vector2f	vel;
	Vector2f	accel;
	Sprite*		sprite;
	int			spriteFrame;
	TimeClock	spriteClock;
public:
	MasknellBullet(Scene* scene, double x, double y);
	~MasknellBullet();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	
	void collide(Entity* other);
	Rectanglef collisionRect() const;
};

#endif
