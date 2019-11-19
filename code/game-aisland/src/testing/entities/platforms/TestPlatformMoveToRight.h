////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestPlatformMoveToRight
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestPlatformMoveToRight_h___
#define ___TestPlatformMoveToRight_h___
#include <src/testing/TestEntities.h>

#include <src/EntityParameters.h>
#include <src/entities/platforms/PlatformMoveTo.h>

class TestPlatformMoveToRight : public TestEntities
{
public:
	TestPlatformMoveToRight()
	{
	}
	~TestPlatformMoveToRight()
	{
	}
private:
	void create()
	{
		EntityParameters params;
		
		params.insert("Image", "Platform.Castle");
		params.insert("To", "250");
		params.insert("Mode", "ToRight");

		scene->addEntity(new PlatformMoveTo(scene, 100, 180, params));
	}
};

#endif
