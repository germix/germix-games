////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BradleyRocket
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___BradleyRocket_h___
#define ___BradleyRocket_h___
#include <src/entities/projectiles/EnemyProjectile.h>

class Sprite;

class BradleyRocket : public EnemyProjectile
{
	Sprite*		sprite;
	Vector2f	vel;
	Vector2f	accel;
	Vector2f	oldPos;
public:
	BradleyRocket(Scene* scene, double x, double y);
	~BradleyRocket();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	
	void collide(Entity* other);
	Rectanglef collisionRect() const;
};

#endif
