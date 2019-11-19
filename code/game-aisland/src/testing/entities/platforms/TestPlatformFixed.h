////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestPlatformFixed
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestPlatformFixed_h___
#define ___TestPlatformFixed_h___
#include <src/testing/TestEntities.h>

#include <src/EntityParameters.h>
#include <src/entities/platforms/PlatformFixed.h>

class TestPlatformFixed : public TestEntities
{
public:
	TestPlatformFixed()
	{
	}
	~TestPlatformFixed()
	{
	}
private:
	void create()
	{
	}
	void firstCreate()
	{
		EntityParameters params;
		
		params.insert("Image", "Platform.Clouds");
		
		scene->addEntity(new PlatformFixed(scene, 100, 155, params));
	}
};

#endif
