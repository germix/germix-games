////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestBonus_Banana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestBonus_Banana_h___
#define ___TestBonus_Banana_h___
#include <src/testing/TestEntities.h>

#include <src/entities/bonus/Bonus_Banana.h>

class TestBonus_Banana : public TestEntities
{
public:
	TestBonus_Banana()
	{
	}
	~TestBonus_Banana()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Bonus_Banana(scene, 120, 150));
	}
};

#endif

