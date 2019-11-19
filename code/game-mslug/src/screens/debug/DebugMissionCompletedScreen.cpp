////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugMissionCompletedScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/debug/DebugMissionCompletedScreen.h>
#include <src/Config.h>
#include <src/screens/EnterNameScreen.h>

#include <mach/Color.h>
#include <mach/Graphics.h>
#include <mach/Keyboard.h>

DebugMissionCompletedScreen::DebugMissionCompletedScreen()
: removable(false)
, nextScreen(null)
{
}
DebugMissionCompletedScreen::~DebugMissionCompletedScreen()
{
}
Screen* DebugMissionCompletedScreen::getNext()
{
	return nextScreen;
}
bool    DebugMissionCompletedScreen::isRemovable()
{
	return removable;
}
void    DebugMissionCompletedScreen::show(Machine* mach)
{
	missionCompleted.activate(null, 1);
}
void    DebugMissionCompletedScreen::hide(Machine* mach)
{
}
void    DebugMissionCompletedScreen::update(Machine* mach, double dt)
{
	if(missionCompleted.isActivated())
	{
		missionCompleted.update(dt);
	}
	else
	{
		removable = true;
		nextScreen = new EnterNameScreen(2140, 18);
	}
}
void    DebugMissionCompletedScreen::render(Machine* mach, Graphics* gr)
{
	if(missionCompleted.isActivated())
	{
		gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(255, 0, 0));
		missionCompleted.render(gr);
	}
	else
	{
		gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0, 255, 0));
	}
}


