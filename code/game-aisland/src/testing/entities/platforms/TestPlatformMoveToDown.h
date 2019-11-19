////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestPlatformMoveToDown
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestPlatformMoveToDown_h___
#define ___TestPlatformMoveToDown_h___
#include <src/testing/TestEntities.h>

#include <src/EntityParameters.h>
#include <src/entities/platforms/PlatformMoveTo.h>

class TestPlatformMoveToDown : public TestEntities
{
public:
	TestPlatformMoveToDown()
	{
	}
	~TestPlatformMoveToDown()
	{
	}
private:
	void create()
	{
		EntityParameters params;
		
		params.insert("Image", "Platform.Castle");
		params.insert("To", "180");
		params.insert("Mode", "ToDown");

		scene->addEntity(new PlatformMoveTo(scene, 100, 160, params));
	}
};

#endif
