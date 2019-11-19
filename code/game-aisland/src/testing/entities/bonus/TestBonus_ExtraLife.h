////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestBonus_ExtraLife
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestBonus_ExtraLife_h___
#define ___TestBonus_ExtraLife_h___
#include <src/testing/TestEntities.h>

#include <src/entities/bonus/Bonus_ExtraLife.h>

class TestBonus_ExtraLife : public TestEntities
{
public:
	TestBonus_ExtraLife()
	{
	}
	~TestBonus_ExtraLife()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Bonus_ExtraLife(scene, 120, 150));
	}
};

#endif
