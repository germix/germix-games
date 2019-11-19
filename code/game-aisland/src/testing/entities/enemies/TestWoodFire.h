////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestWoodFire
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestWoodFire_h___
#define ___TestWoodFire_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/WoodFire.h>

class TestWoodFire : public TestEntities
{
public:
	TestWoodFire()
	{
	}
	~TestWoodFire()
	{
	}
private:
	void create()
	{
		scene->addEntity(new WoodFire(scene, hero->getPosition().x + 120, 184));
	}
};

#endif
