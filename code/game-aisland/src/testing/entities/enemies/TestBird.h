////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestBird
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestBird_h___
#define ___TestBird_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/Bird.h>

class TestBird : public TestEntities
{
public:
	TestBird()
	{
	}
	~TestBird()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Bird(scene, hero->getPosition().x + 80, 150, "Fireball"));
	}
};

#endif
