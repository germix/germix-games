////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestBonus_Gamepad
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestBonus_Gamepad_h___
#define ___TestBonus_Gamepad_h___
#include <src/testing/TestEntities.h>

#include <src/entities/bonus/Bonus_Gamepad.h>

class TestBonus_Gamepad : public TestEntities
{
public:
	TestBonus_Gamepad()
	{
	}
	~TestBonus_Gamepad()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Bonus_Gamepad(scene, 120, 150));
	}
};

#endif
