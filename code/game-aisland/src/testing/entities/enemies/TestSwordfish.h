////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestSwordfish
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestSwordfish_h___
#define ___TestSwordfish_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/Swordfish.h>

class TestSwordfish : public TestEntities
{
public:
	TestSwordfish()
	{
	}
	~TestSwordfish()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Swordfish(scene, hero->getPosition().x + 120, 150));
	}
};

#endif
