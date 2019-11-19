////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestRockBall
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestRockBall_h___
#define ___TestRockBall_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/RockBall.h>

class TestRockBall : public TestEntities
{
public:
	TestRockBall()
	{
	}
	~TestRockBall()
	{
	}
private:
	void create()
	{
		scene->addEntity(new RockBall(scene, hero->getPosition().x + 120, 150));
	}
};

#endif
