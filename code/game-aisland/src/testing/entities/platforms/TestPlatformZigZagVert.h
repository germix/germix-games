////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestPlatformZigZagVert
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestPlatformZigZagVert_h___
#define ___TestPlatformZigZagVert_h___
#include <src/testing/TestEntities.h>

#include <src/EntityParameters.h>
#include <src/entities/platforms/PlatformZigZagVert.h>

class TestPlatformZigZagVert : public TestEntities
{
public:
	TestPlatformZigZagVert()
	{
	}
	~TestPlatformZigZagVert()
	{
	}
private:
	void create()
	{
		EntityParameters params;
		
		params.insert("Image", "Platform.Clouds");
		params.insert("Min", "120");
		params.insert("Max", "180");
		scene->addEntity(new PlatformZigZagVert(scene, 100, 160, params));
	}
};

#endif
