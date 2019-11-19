////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Enemy
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Enemy_h___
#define ___Enemy_h___
#include <src/Entity.h>

#include <mach/String.h>

class Hero;

class Enemy : public Entity
{
protected:
	const String eggEntity;
public:
	Enemy(Scene* s, double x, double y, const String& eggEntity = "");
	~Enemy();
protected:
	void collideWithHero(Hero* h);
	bool collideWithHoneygirl(Hero* h);
};

#endif
