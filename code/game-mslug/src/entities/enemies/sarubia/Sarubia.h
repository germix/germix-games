////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Sarubia | Nop-03 Sarubia (Tanque blindado disparador de bomba)
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Sarubia_h___
#define ___Sarubia_h___
#include <src/entities/enemies/Enemy.h>
#include <src/___/HurtableRect.h>

#include <gamelib/TimeClock.h>

class Sprite;

class Sarubia : public Enemy, public HurtableRect
{
	enum STATE
	{
		STATE_NOTHING,
		STATE_IDLE,
		STATE_DRIVING,
		STATE_STOPPING,
		STATE_PREPARING,
		STATE_SHOOTING,
		STATE_WRECKED,
	};
	STATE			state;
	bool			onGround;
	Vector2f		vel;
	Vector2f		accel;
	Sprite*			sprite;
	int				spriteFrame;
	TimeClock		spriteClock;
	int				initialX;
	TimeClock		shootingClock;
	int				healt;
	int				currentExplosion;
	TimeClock		explosionClock;

	Sprite*			SPRITE_IDLE;
	Sprite*			SPRITE_DRIVING;
	Sprite*			SPRITE_STOPPING;
	Sprite*			SPRITE_PREPARING;
	Sprite*			SPRITE_SHOOTING;
	Sprite*			SPRITE_WRECKED;

public:
	Sarubia(Scene* scene, double x, double y);
	~Sarubia();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;

	void hurt(int damage);
	bool isHurtable() const;
	Rectanglef hurtableRect() const;
};

#endif
