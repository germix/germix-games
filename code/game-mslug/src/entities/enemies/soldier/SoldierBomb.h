////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SoldierBomb | Bomba del soldado
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SoldierBomb_h___
#define ___SoldierBomb_h___
#include <src/entities/projectiles/EnemyProjectile.h>

#include <gamelib/TimeClock.h>

class Sprite;

class SoldierBomb : public EnemyProjectile
{
	Vector2f			vel;
	Vector2f			accel;
	Sprite*				sprite;
	int					animIndex;
	TimeClock			animClock;
	const int*			hints;
	int					hintsLength;
	const int*			indexes;
	int					indexesLength;
public:
	SoldierBomb(Scene* scene, double px, double py, double vx, double vy);
	~SoldierBomb();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	
	void collide(Entity* other);
	Rectanglef collisionRect() const;
private:
	void explode();
};

#endif
