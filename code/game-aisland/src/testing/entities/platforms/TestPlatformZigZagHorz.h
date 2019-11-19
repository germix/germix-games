////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestPlatformZigZagHorz
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestPlatformZigZagHorz_h___
#define ___TestPlatformZigZagHorz_h___
#include <src/testing/TestEntities.h>

#include <src/EntityParameters.h>
#include <src/entities/platforms/PlatformZigZagHorz.h>

class TestPlatformZigZagHorz : public TestEntities
{
public:
	TestPlatformZigZagHorz()
	{
	}
	~TestPlatformZigZagHorz()
	{
	}
private:
	void create()
	{
		EntityParameters params;
		
		params.insert("Image", "Platform.Clouds");
		params.insert("Min", "76");
		params.insert("Max", "136");
		scene->addEntity(new PlatformZigZagHorz(scene, 100, 150, params));
	}
};

#endif
