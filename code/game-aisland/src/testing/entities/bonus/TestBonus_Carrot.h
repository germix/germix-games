////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestBonus_Carrot
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestBonus_Carrot_h___
#define ___TestBonus_Carrot_h___
#include <src/testing/TestEntities.h>

#include <src/entities/bonus/Bonus_Carrot.h>

class TestBonus_Carrot : public TestEntities
{
public:
	TestBonus_Carrot()
	{
	}
	~TestBonus_Carrot()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Bonus_Carrot(scene, 120, 150));
	}
};

#endif
