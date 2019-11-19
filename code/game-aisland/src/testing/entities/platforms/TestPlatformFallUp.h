////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestPlatformFallUp
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestPlatformFallUp_h___
#define ___TestPlatformFallUp_h___
#include <src/testing/TestEntities.h>

#include <src/EntityParameters.h>
#include <src/entities/platforms/PlatformFallUp.h>

class TestPlatformFallUp : public TestEntities
{
public:
	TestPlatformFallUp()
	{
	}
	~TestPlatformFallUp()
	{
	}
private:
	void create()
	{
		EntityParameters params;
		
		params.insert("Image", "Platform.Clouds");
		
		scene->addEntity(new PlatformFallUp(scene, 100, 155, params));
	}
};

#endif
