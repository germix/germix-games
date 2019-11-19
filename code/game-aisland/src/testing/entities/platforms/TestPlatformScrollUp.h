////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestPlatformScrollUp
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestPlatformScrollUp_h___
#define ___TestPlatformScrollUp_h___
#include <src/testing/TestEntities.h>

#include <src/EntityParameters.h>
#include <src/entities/platforms/PlatformScrollUp.h>

class TestPlatformScrollUp : public TestEntities
{
public:
	TestPlatformScrollUp()
	{
	}
	~TestPlatformScrollUp()
	{
	}
private:
	void create()
	{
		EntityParameters params;
		
		params.insert("Image", "Platform.Clouds");
		
		scene->addEntity(new PlatformScrollUp(scene, 100, 150, params));
	}
};

#endif
