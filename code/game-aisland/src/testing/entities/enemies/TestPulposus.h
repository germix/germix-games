////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestPulposus
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestPulposus_h___
#define ___TestPulposus_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/Pulposus.h>

class TestPulposus : public TestEntities
{
public:
	TestPulposus()
	{
	}
	~TestPulposus()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Pulposus(scene, hero->getPosition().x + 70, 184, 1));
		scene->addEntity(new Pulposus(scene, hero->getPosition().x + 150, 184, 2));
	}
};

#endif
