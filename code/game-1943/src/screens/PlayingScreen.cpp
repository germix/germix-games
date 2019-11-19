////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlayingScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/PlayingScreen.h>
#include <src/Scene.h>

#include <src/screens/GameOverScreen.h>
#include <src/screens/WinnerScreen.h>

#include <mach/Keyboard.h>

PlayingScreen::PlayingScreen()
: removable(false)
, nextScreen(null)
{
}
PlayingScreen::~PlayingScreen()
{
}
Screen* PlayingScreen::getNext()
{
	return nextScreen;
}
bool    PlayingScreen::isRemovable()
{
	return removable;
}
void    PlayingScreen::show(Machine* mach)
{
	scene = new Scene();
	scene->init();
}
void    PlayingScreen::hide(Machine* mach)
{
	delete scene;
}
void    PlayingScreen::update(Machine* mach, double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		removable = true;
	}
	else
	{
		scene->update(dt);
		switch(scene->getPlayerState())
		{
			case Scene::PLAYER_STATE_LOSER:
				removable = true;
				nextScreen = new GameOverScreen();
				break;
			case Scene::PLAYER_STATE_WINNER:
				removable = true;
				nextScreen = new WinnerScreen();
				break;
		}
	}
}
void    PlayingScreen::render(Machine* mach, Graphics* gr)
{
	scene->render(gr);
}
