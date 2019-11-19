////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestBonus_Apple
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestBonus_Apple_h___
#define ___TestBonus_Apple_h___
#include <src/testing/TestEntities.h>

#include <src/entities/bonus/Bonus_Apple.h>

class TestBonus_Apple : public TestEntities
{
public:
	TestBonus_Apple()
	{
	}
	~TestBonus_Apple()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Bonus_Apple(scene, 120, 150));
	}
};

#endif
