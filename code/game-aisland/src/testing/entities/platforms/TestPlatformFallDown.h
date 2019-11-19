////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestPlatformFallDown
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestPlatformFallDown_h___
#define ___TestPlatformFallDown_h___
#include <src/testing/TestEntities.h>

#include <src/EntityParameters.h>
#include <src/entities/platforms/PlatformFallDown.h>

class TestPlatformFallDown : public TestEntities
{
public:
	TestPlatformFallDown()
	{
	}
	~TestPlatformFallDown()
	{
	}
private:
	void create()
	{
		EntityParameters params;
		
		params.insert("Image", "Platform.Clouds");
		
		scene->addEntity(new PlatformFallDown(scene, 100, 155, params));
	}
};

#endif
