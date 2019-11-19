////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeavyMachineGunBullet | Bala de HeavyMachineGun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeavyMachineGunBullet_h___
#define ___HeavyMachineGunBullet_h___
#include <src/entities/projectiles/HeroBullet.h>

class Sprite;

class HeavyMachineGunBullet : public HeroBullet
{
	Vector2f		vel;
	Vector2f		accel;
	Sprite*			sprite;
	int				spriteFrame;
	unsigned int	spriteHints;
public:
	HeavyMachineGunBullet(Scene* scene, double px, double py, double vx, double vy, double shootAngle);
	~HeavyMachineGunBullet();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	void hurt(HurtableRect* hr);
};

#endif

