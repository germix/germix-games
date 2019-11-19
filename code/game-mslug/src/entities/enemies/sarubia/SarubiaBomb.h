////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SarubiaBomb | Bomba disparada por Sarubia
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SarubiaBomb_h___
#define ___SarubiaBomb_h___
#include <src/entities/projectiles/EnemyProjectile.h>

#include <gamelib/TimeClock.h>

class Sprite;

class SarubiaBomb : public EnemyProjectile
{
	enum STATE
	{
		STATE_NOTHING,
		STATE_BOUNCE,
		STATE_ROLLING,
	};
	STATE			state;
	Vector2f		vel;
	Vector2f		accel;
	bool			onGround;
	int				animIndex;
	Sprite*			sprite;
	int				spriteFrame;
	TimeClock		spriteClock;
public:
	SarubiaBomb(Scene* scene, double x, double y);
	~SarubiaBomb();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	
	void collide(Entity* other);
	Rectanglef collisionRect() const;
};

#endif
