////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BattleshipCannon
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___BattleshipCannon_h___
#define ___BattleshipCannon_h___
#include <src/entities/enemies/Enemy.h>
#include <src/Shootable.h>

#include <gamelib/TimeClock.h>

class Sprite;
class Battleship;
class EnemyWeapon;
class EnemyWeaponHandler;

class BattleshipCannon : public Enemy
{
	Sprite*				sprite;
	int					spriteIndex;
	bool				destroyed;
	Battleship*			battleship;
	
	int					health;
	
	EnemyWeaponHandler*	weapon;
	bool				isGiantCannon;
public:
	BattleshipCannon(Scene* scene, double x, double y, Battleship* battleship, Sprite* sprite, int health, EnemyWeapon* weapon, bool isGiantCannon);
	~BattleshipCannon();
public:
	Vector2f position() const;
	Rectanglef rect() const;
	void update(double dt);
	void render(Graphics* gr);
	bool hurt(int damage);
	bool isAlive() const;
	bool isDestroyed() const;
	int getHealth() const;
	int getDestructionScore() const;
	void checkHit(HeroBullet* bullet);
};

#endif
