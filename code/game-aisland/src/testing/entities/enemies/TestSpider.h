////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestSpider
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestSpider_h___
#define ___TestSpider_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/Spider.h>

class TestSpider : public TestEntities
{
public:
	TestSpider()
	{
	}
	~TestSpider()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Spider(scene, hero->getPosition().x + 120, 150));
		scene->addEntity(new Spider(scene, hero->getPosition().x + 170, 150, 120, 180));
	}
};

#endif
