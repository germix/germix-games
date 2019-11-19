////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestPlatformMoveToUp
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestPlatformMoveToUp_h___
#define ___TestPlatformMoveToUp_h___
#include <src/testing/TestEntities.h>

#include <src/EntityParameters.h>
#include <src/entities/platforms/PlatformMoveTo.h>

class TestPlatformMoveToUp : public TestEntities
{
public:
	TestPlatformMoveToUp()
	{
	}
	~TestPlatformMoveToUp()
	{
	}
private:
	void create()
	{
		EntityParameters params;
		
		params.insert("Image", "Platform.Castle");
		params.insert("To", "150");
		params.insert("Mode", "ToUp");

		scene->addEntity(new PlatformMoveTo(scene, 100, 180, params));
	}
};

#endif
