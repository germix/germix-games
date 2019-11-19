////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlaySceneScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/PlaySceneScreen.h>
#include <src/Scene.h>

#include <mach/Keyboard.h>

PlaySceneScreen::PlaySceneScreen(int area, int round)
: scene(new Scene(info, area, round))
, removable(false)
{
}
PlaySceneScreen::~PlaySceneScreen()
{
	delete scene;
}
Screen* PlaySceneScreen::getNext()
{
	return null;
}
bool    PlaySceneScreen::isRemovable()
{
	return removable;
}
void    PlaySceneScreen::show(Machine* mach)
{
}
void    PlaySceneScreen::hide(Machine* mach)
{
}
void    PlaySceneScreen::update(Machine* mach, double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		removable = true;
	}
	else
	{
		scene->update(dt);
		if(scene->isFinished())
		{
			removable = true;
		}
	}
}
void    PlaySceneScreen::render(Machine* mach, Graphics* gr)
{
	scene->render(gr);
}

