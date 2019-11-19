////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Aircraft
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Aircraft_h___
#define ___Aircraft_h___
#include <src/entities/enemies/Enemy.h>
#include <src/Collisionable.h>

#include <gamelib/TimeClock.h>

class Sprite;

class AircraftTroop;
class AircraftBehavior;
class EnemyWeaponHandler;

class Aircraft : public Enemy, public Collisionable
{
	Sprite*				sprite;
	int					spriteIndex;

	bool				alive;
	int					health;
	
	bool				interactive;
	
	AircraftTroop*		troop;
	AircraftBehavior*	behavior;
	
	EnemyWeaponHandler*	weapon;

	bool				canHurt;
	TimeClock			hurtTime;
public:
	Aircraft(Scene* s, double x, double y, int health, Sprite* sprite, AircraftTroop* troop, AircraftBehavior* behavior, EnemyWeaponHandler* weapon);
	~Aircraft();
public:
	Rectanglef rect() const;
	void update(double dt);
	void render(Graphics* gr);
public:
	bool hurt(int damage);
	bool isAlive() const;
	bool isDestroyed() const;
	int getHealth() const;
	int getDestructionScore() const;
	void checkHit(HeroBullet* bullet);
	void checkCollision(Entity* other);
protected:
	void removeMe(bool destroyed);
	void checkInteractivity();
};

#endif
