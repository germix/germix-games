////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PistolBullet | Bala de la pistola
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PistolBullet_h___
#define ___PistolBullet_h___
#include <src/entities/projectiles/HeroBullet.h>

class Sprite;

class PistolBullet : public HeroBullet
{
	Vector2f		vel;
	Vector2f		accel;
	Sprite*			sprite;
public:
	PistolBullet(Scene* scene, double px, double py, double vx, double vy);
	~PistolBullet();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	void hurt(HurtableRect* hr);
};

#endif
