////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestEgg
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestEgg_h___
#define ___TestEgg_h___
#include <src/testing/TestEntities.h>

#include <src/entities/Egg.h>

class TestEgg : public TestEntities
{
public:
	TestEgg()
	{
	}
	~TestEgg()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Egg(scene, hero->getPosition().x + 80, 184, "Milk"));
	}
};

#endif
