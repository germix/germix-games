////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestCampaignResult
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/testing/TestCampaignResult.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/CampaignResult.h>

#include <mach/Color.h>
#include <mach/Graphics.h>
#include <mach/Machine.h>

TestCampaignResult::TestCampaignResult()
{
}
TestCampaignResult::~TestCampaignResult()
{
}
void TestCampaignResult::init(Machine* mach)
{
	res.load("1943/resources.xres");
	result = new CampaignResult(true);
}
void TestCampaignResult::close(Machine* mach)
{
}
void TestCampaignResult::update(Machine* mach, double dt)
{
	if(result->update(dt))
	{
		delete result;
		mach->shutdown();
	}
}
void TestCampaignResult::render(Machine* mach, Graphics* gr)
{
	gr->translate(SCENE_X, SCENE_Y);
	result->render(gr);
	gr->translate(-SCENE_X, -SCENE_Y);
}
