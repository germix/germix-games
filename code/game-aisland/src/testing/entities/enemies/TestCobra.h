////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestCobra
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestCobra_h___
#define ___TestCobra_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/Cobra.h>

class TestCobra : public TestEntities
{
public:
	TestCobra()
	{
	}
	~TestCobra()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Cobra(scene, hero->getPosition().x + 120, 184));
	}
};

#endif
