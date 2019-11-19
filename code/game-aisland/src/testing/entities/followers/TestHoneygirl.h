////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestHoneygirl
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestHoneygirl_h___
#define ___TestHoneygirl_h___
#include <src/testing/TestEntities.h>

#include <src/entities/enemies/Frog.h>
#include <src/entities/enemies/Rock.h>
#include <src/entities/enemies/WoodFire.h>
#include <src/entities/followers/Honeygirl.h>

class TestHoneygirl : public TestEntities
{
public:
	TestHoneygirl()
	{
	}
	~TestHoneygirl()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Honeygirl(scene, hero->getPosition().x, 184));
		scene->addEntity(new Frog(scene, hero->getPosition().x + 80, 184, 2, true));
		scene->addEntity(new Rock(scene, hero->getPosition().x + 80+32, 184));
		scene->addEntity(new WoodFire(scene, hero->getPosition().x + 80+32+32, 184));
	}
};

#endif
