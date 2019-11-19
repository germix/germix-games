////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestBonus_Milk
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestBonus_Milk_h___
#define ___TestBonus_Milk_h___
#include <src/testing/TestEntities.h>

#include <src/entities/bonus/Bonus_Milk.h>

class TestBonus_Milk : public TestEntities
{
public:
	TestBonus_Milk()
	{
	}
	~TestBonus_Milk()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Bonus_Milk(scene, 120, 150));
	}
};

#endif
