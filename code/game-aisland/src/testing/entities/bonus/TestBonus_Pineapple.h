////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestBonus_Pineapple
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestBonus_Pineapple_h___
#define ___TestBonus_Pineapple_h___
#include <src/testing/TestEntities.h>

#include <src/entities/bonus/Bonus_Pineapple.h>

class TestBonus_Pineapple : public TestEntities
{
public:
	TestBonus_Pineapple()
	{
	}
	~TestBonus_Pineapple()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Bonus_Pineapple(scene, 120, 150));
	}
};

#endif

