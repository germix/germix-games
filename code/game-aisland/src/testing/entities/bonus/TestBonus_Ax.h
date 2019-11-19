////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestBonus_Ax
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestBonus_Ax_h___
#define ___TestBonus_Ax_h___
#include <src/testing/TestEntities.h>

#include <src/entities/bonus/Bonus_Ax.h>

class TestBonus_Ax : public TestEntities
{
public:
	TestBonus_Ax()
	{
	}
	~TestBonus_Ax()
	{
	}
private:
	void create()
	{
		scene->addEntity(new Bonus_Ax(scene, 120, 150));
	}
};

#endif
