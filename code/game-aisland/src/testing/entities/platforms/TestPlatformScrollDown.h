////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestPlatformScrollDown
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestPlatformScrollDown_h___
#define ___TestPlatformScrollDown_h___
#include <src/testing/TestEntities.h>

#include <src/EntityParameters.h>
#include <src/entities/platforms/PlatformScrollDown.h>

class TestPlatformScrollDown : public TestEntities
{
public:
	TestPlatformScrollDown()
	{
	}
	~TestPlatformScrollDown()
	{
	}
private:
	void create()
	{
		EntityParameters params;
		
		params.insert("Image", "Platform.Clouds");
		
		scene->addEntity(new PlatformScrollDown(scene, 100, 150, params));
	}
};

#endif
