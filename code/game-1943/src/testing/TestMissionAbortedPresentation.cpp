////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MissionAbortedPresentation
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/testing/TestMissionAbortedPresentation.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/presentations/MissionAbortedPresentation.h>

#include <mach/Color.h>
#include <mach/Graphics.h>
#include <mach/Machine.h>

TestMissionAbortedPresentation::TestMissionAbortedPresentation()
{
}
TestMissionAbortedPresentation::~TestMissionAbortedPresentation()
{
}
void TestMissionAbortedPresentation::init(Machine* mach)
{
	res.load("1943/resources.xres");
	presentation = new MissionAbortedPresentation(41);
}
void TestMissionAbortedPresentation::close(Machine* mach)
{
}
void TestMissionAbortedPresentation::update(Machine* mach, double dt)
{
	if(presentation->update(dt))
	{
		delete presentation;
		mach->shutdown();
	}
}
void TestMissionAbortedPresentation::render(Machine* mach, Graphics* gr)
{
	gr->translate(SCENE_X, SCENE_Y);
	gr->fillRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT, Color(120, 120, 120));
	presentation->render(gr);
	gr->translate(-SCENE_X, -SCENE_Y);
}
