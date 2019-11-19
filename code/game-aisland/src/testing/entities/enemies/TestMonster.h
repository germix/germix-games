////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestMonster
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestMonster_h___
#define ___TestMonster_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/Monster.h>

class TestMonster : public TestEntities
{
public:
	TestMonster()
	{
	}
	~TestMonster()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Monster(scene, hero->getPosition().x + 120, 184, 1));
	}
};

#endif
