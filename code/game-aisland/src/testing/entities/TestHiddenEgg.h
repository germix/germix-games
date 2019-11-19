////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestHiddenEgg
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestHiddenEgg_h___
#define ___TestHiddenEgg_h___
#include <src/testing/TestEntities.h>

#include <src/entities/HiddenEgg.h>

class TestHiddenEgg : public TestEntities
{
public:
	TestHiddenEgg()
	{
	}
	~TestHiddenEgg()
	{
	}
private:
	void create()
	{
		scene->addEntity(new HiddenEgg(scene, hero->getPosition().x + 80, 184, "Milk"));
	}
};

#endif
