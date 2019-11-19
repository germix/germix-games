////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RShobuBomb | Bomba del helicóptero R-Shobu
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___RShobuBomb_h___
#define ___RShobuBomb_h___
#include <src/entities/projectiles/EnemyProjectile.h>
#include <src/___/HurtableRect.h>

#include <gamelib/TimeClock.h>

class Sprite;

class RShobuBomb : public EnemyProjectile, public HurtableRect
{
	Vector2f		vel;
	Vector2f		accel;
	
	int				dir;
	Sprite*			sprite;
	int				spriteFrame;
	TimeClock		spriteClock;
public:
	RShobuBomb(Scene* scene, double x, double y);
	~RShobuBomb();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;

	void hurt(int damage);
	bool isHurtable() const;
	Rectanglef hurtableRect() const;
	
	void collide(Entity* other);
	Rectanglef collisionRect() const;
};

#endif
