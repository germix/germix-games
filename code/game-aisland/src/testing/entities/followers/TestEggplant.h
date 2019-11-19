////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestEggplant
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestEggplant_h___
#define ___TestEggplant_h___
#include <src/testing/TestEntities.h>

#include <src/entities/followers/Eggplant.h>

class TestEggplant : public TestEntities
{
public:
	TestEggplant()
	{
	}
	~TestEggplant()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Eggplant(scene, hero->getPosition().x + 120, 184));
	}
};

#endif
