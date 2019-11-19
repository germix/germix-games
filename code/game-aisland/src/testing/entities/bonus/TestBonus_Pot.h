////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestBonus_Pot
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestBonus_Pot_h___
#define ___TestBonus_Pot_h___
#include <src/testing/TestEntities.h>

#include <src/entities/bonus/Bonus_Pot.h>

class TestBonus_Pot : public TestEntities
{
public:
	TestBonus_Pot()
	{
	}
	~TestBonus_Pot()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Bonus_Pot(scene, 120, 150));
	}
};

#endif

