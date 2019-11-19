////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusPack
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___BonusPack_h___
#define ___BonusPack_h___
#include <src/Entity.h>
#include <src/Shootable.h>
#include <src/Collisionable.h>

#include <mach/String.h>

class Sprite;
class Bonus;
class HeroBullet;

class BonusPack : public Entity, public Shootable, public Collisionable
{
	Sprite*					sprite;
	double					spriteTime;
	int						spriteIndex;
	
	std::vector<Bonus*>		bonusList;
	int						currentBonus;
	
	int						hitCount;
	bool					interactive;
public:
	BonusPack(Scene* s, double x, double y, const String& bonusDescriptor);
	~BonusPack();
public:
	Rectanglef rect() const;
	void update(double dt);
	void render(Graphics* gr);
	void checkHit(HeroBullet* bullet);
	void checkCollision(Entity* other);
private:
	void setupSprite();
};

#endif
