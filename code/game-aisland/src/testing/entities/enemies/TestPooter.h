////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestPooter
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestPooter_h___
#define ___TestPooter_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/Pooter.h>

class TestPooter : public TestEntities
{
public:
	TestPooter()
	{
	}
	~TestPooter()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Pooter(scene, hero->getPosition().x + 120, 184));
	}
};

#endif
