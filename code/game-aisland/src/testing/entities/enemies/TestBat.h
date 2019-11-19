////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestBat
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestBat_h___
#define ___TestBat_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/Bat.h>

class TestBat : public TestEntities
{
public:
	TestBat()
	{
	}
	~TestBat()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Bat(scene, hero->getPosition().x + 120, 70, scene->getCameraRect().getMaxY() - 40));
	}
};

#endif
