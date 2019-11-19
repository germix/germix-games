////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestBonus_Fireball
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestBonus_Fireball_h___
#define ___TestBonus_Fireball_h___
#include <src/testing/TestEntities.h>

#include <src/entities/bonus/Bonus_Fireball.h>

class TestBonus_Fireball : public TestEntities
{
public:
	TestBonus_Fireball()
	{
	}
	~TestBonus_Fireball()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Bonus_Fireball(scene, 120, 150));
	}
};

#endif
