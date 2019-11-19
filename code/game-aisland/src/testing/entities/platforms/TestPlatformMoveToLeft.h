////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestPlatformMoveToLeft
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestPlatformMoveToLeft_h___
#define ___TestPlatformMoveToLeft_h___
#include <src/testing/TestEntities.h>

#include <src/EntityParameters.h>
#include <src/entities/platforms/PlatformMoveTo.h>

class TestPlatformMoveToLeft : public TestEntities
{
public:
	TestPlatformMoveToLeft()
	{
	}
	~TestPlatformMoveToLeft()
	{
	}
private:
	void create()
	{
		EntityParameters params;
		
		params.insert("Image", "Platform.Castle");
		params.insert("To", "50");
		params.insert("Mode", "ToLeft");

		scene->addEntity(new PlatformMoveTo(scene, 100, 180, params));
	}
};

#endif
