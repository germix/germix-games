////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestRock
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestRock_h___
#define ___TestRock_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/Rock.h>

class TestRock : public TestEntities
{
public:
	TestRock()
	{
	}
	~TestRock()
	{
	}
private:
	void create()
	{
		double x = scene->getHero()->getPosition().x;
		scene->addEntity(new Rock(scene, x + 100, 184));
		scene->addEntity(new Rock(scene, x + 130, 184));
	}
};

#endif
