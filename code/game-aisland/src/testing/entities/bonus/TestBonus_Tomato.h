////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestBonus_Tomato
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestBonus_Tomato_h___
#define ___TestBonus_Tomato_h___
#include <src/testing/TestEntities.h>

#include <src/entities/bonus/Bonus_Tomato.h>

class TestBonus_Tomato : public TestEntities
{
public:
	TestBonus_Tomato()
	{
	}
	~TestBonus_Tomato()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Bonus_Tomato(scene, 120, 150));
	}
};

#endif

