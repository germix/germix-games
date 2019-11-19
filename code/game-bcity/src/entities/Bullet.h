////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bullet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bullet_h___
#define ___Bullet_h___
#include <src/entities/Entity.h>
#include <src/base/Direction.h>

#include <gamelib/TimeClock.h>

class Tank;
class HeroTank;
class EnemyTank;
class Rectangle;

class Bullet : public Entity
{
	int						vx;
	int						vy;
	TimeClock				clock;

	HeroTank*				hero;
	EnemyTank*				enemy;
	
	bool					strong;

	int						spriteIndex;
	
public:
	Bullet(Map* m, Scene* s, int x, int y, Direction dir, Tank* shooter, double velocity, bool strong);
	~Bullet();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* other);
private:
	bool moveOrHit(const Rectangle& collisionRect, int dx, int dy);
};

#endif
