////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestSkull
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestSkull_h___
#define ___TestSkull_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/Skull.h>

class TestSkull : public TestEntities
{
public:
	TestSkull()
	{
	}
	~TestSkull()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Skull(scene, hero->getPosition().x + 120, 150));
	}
};

#endif
