////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestIcicle
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestIcicle_h___
#define ___TestIcicle_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/Icicle.h>

class TestIcicle : public TestEntities
{
public:
	TestIcicle()
	{
	}
	~TestIcicle()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Icicle(scene, hero->getPosition().x + 130, 90));
	}
};

#endif
