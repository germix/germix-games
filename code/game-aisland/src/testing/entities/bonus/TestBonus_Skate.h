////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestBonus_Skate
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestBonus_Skate_h___
#define ___TestBonus_Skate_h___
#include <src/testing/TestEntities.h>

#include <src/entities/bonus/Bonus_Skate.h>

class TestBonus_Skate : public TestEntities
{
public:
	TestBonus_Skate()
	{
	}
	~TestBonus_Skate()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Bonus_Skate(scene, 120, 170));
	}
};

#endif

