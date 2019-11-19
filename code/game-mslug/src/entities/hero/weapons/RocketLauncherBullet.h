////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RocketLauncherBullet | Cohete lanzado por RocketLauncher
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___RocketLauncherBullet_h___
#define ___RocketLauncherBullet_h___
#include <src/entities/projectiles/HeroBullet.h>
#include <gamelib/TimeClock.h>

class Sprite;

class RocketLauncherBullet : public HeroBullet
{
	Vector2f		vel;
	Vector2f		accel;
	Sprite*			sprite;
	int				spriteFrame;
	unsigned int	spriteHints;
	TimeClock		spriteClock;
	int				dirX;
	int				dirY;
public:
	RocketLauncherBullet(Scene* scene, double px, double py, int shotAngle, int lookX);
	~RocketLauncherBullet();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	void hurt(HurtableRect* hr);
};

#endif
