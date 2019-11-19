////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestCoyote
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestCoyote_h___
#define ___TestCoyote_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/Coyote.h>

class TestCoyote : public TestEntities
{
public:
	TestCoyote()
	{
	}
	~TestCoyote()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Coyote(scene, hero->getPosition().x + 120, 184));
	}
};

#endif
