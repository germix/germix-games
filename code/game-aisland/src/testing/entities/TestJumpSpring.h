////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestJumpSpring
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestJumpSpring_h___
#define ___TestJumpSpring_h___
#include <src/testing/TestEntities.h>

#include <src/entities/JumpSpring.h>

class TestJumpSpring : public TestEntities
{
public:
	TestJumpSpring()
	{
	}
	~TestJumpSpring()
	{
	}
private:
	void create()
	{
	}
	void firstCreate()
	{
		scene->addEntity(new JumpSpring(scene, 100, 184));
	}
};

#endif
