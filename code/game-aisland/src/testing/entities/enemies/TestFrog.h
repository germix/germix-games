////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestFrog
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestFrog_h___
#define ___TestFrog_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/Frog.h>

class TestFrog : public TestEntities
{
public:
	TestFrog()
	{
	}
	~TestFrog()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Frog(scene, hero->getPosition().x + 120, 184, 2, true));
	}
};

#endif
