////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestBonus_Flower
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestBonus_Flower_h___
#define ___TestBonus_Flower_h___
#include <src/testing/TestEntities.h>

#include <src/entities/bonus/Bonus_Flower.h>

class TestBonus_Flower : public TestEntities
{
public:
	TestBonus_Flower()
	{
	}
	~TestBonus_Flower()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Bonus_Flower(scene, 120, 184));
	}
};

#endif
