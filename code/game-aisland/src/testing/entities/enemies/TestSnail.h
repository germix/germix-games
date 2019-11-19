////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestSnail
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestSnail_h___
#define ___TestSnail_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/Snail.h>

class TestSnail : public TestEntities
{
public:
	TestSnail()
	{
	}
	~TestSnail()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Snail(scene, hero->getPosition().x + 120, 184));
	}
};

#endif
