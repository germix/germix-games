////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Battleship
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Battleship_h___
#define ___Battleship_h___
#include <src/entities/enemies/Enemy.h>

#include <vector>
#include <string>

class Texture;
class BattleshipTower;
class BattleshipCannon;
class BattleshipHangar;

class Battleship : public Enemy
{
protected:
	Texture*			texture;
	bool				destroyed;
	
	std::vector<BattleshipTower*>	towers;
	std::vector<BattleshipCannon*>	cannons;
	std::vector<BattleshipHangar*>	hangars;
	
public:
	Battleship(Scene* s, double x, double y, const std::string& fname);
	~Battleship();
public:
	Rectanglef rect() const;
	void update(double dt);
	void render(Graphics* gr);
	bool hurt(int damage);
	bool isAlive() const;
	bool isDestroyed() const;
	int getHealth() const;
	int getDestructionScore() const;
	void checkHit(HeroBullet* bullet);
protected:
	void updateComponents(double dt);
};

#endif
