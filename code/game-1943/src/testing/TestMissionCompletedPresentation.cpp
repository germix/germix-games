////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestMissionCompletedPresentation
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/testing/TestMissionCompletedPresentation.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/presentations/MissionCompletedPresentation.h>

#include <mach/Color.h>
#include <mach/Graphics.h>
#include <mach/Machine.h>

TestMissionCompletedPresentation::TestMissionCompletedPresentation()
{
}
TestMissionCompletedPresentation::~TestMissionCompletedPresentation()
{
}
void TestMissionCompletedPresentation::init(Machine* mach)
{
	res.load("1943/resources.xres");
	presentation = new MissionCompletedPresentation(93);
}
void TestMissionCompletedPresentation::close(Machine* mach)
{
}
void TestMissionCompletedPresentation::update(Machine* mach, double dt)
{
	if(presentation->update(dt))
	{
		delete presentation;
		mach->shutdown();
	}
}
void TestMissionCompletedPresentation::render(Machine* mach, Graphics* gr)
{
	gr->translate(SCENE_X, SCENE_Y);
	gr->fillRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT, Color(120, 120, 120));
	presentation->render(gr);
	gr->translate(-SCENE_X, -SCENE_Y);
}
