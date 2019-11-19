////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BattleshipTower
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___BattleshipTower_h___
#define ___BattleshipTower_h___
#include <src/entities/enemies/Enemy.h>

class Texture;
class Battleship;

class BattleshipTower : public Enemy
{
	Texture*		texture;
	bool			destroyed;
	Battleship*		battleship;
public:
	BattleshipTower(Scene* scene, double x, double y, Texture* texture, Battleship* battleship);
	~BattleshipTower();
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
public:
	void destroy();
};

#endif
