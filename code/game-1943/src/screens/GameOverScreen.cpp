////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GameOverScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/GameOverScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/screens/PlayingScreen.h>

#include <mach/Mixer.h>
#include <mach/Color.h>
#include <mach/Graphics.h>
#include <mach/Keyboard.h>

#include <gamelib/Font.h>

#define MESSAGE_GAME_OVER		"GAME OVER"
#define MESSAGE_PRESS_ENTER		"<ENTER> JUGAR OTRA VEZ"
#define MESSAGE_PRESS_ESCAPE	"<ESCAPE> SALIR DEL JUEGO"

GameOverScreen::GameOverScreen()
: removable(false)
, nextScreen(null)
, font1(null)
, font2(null)
, alphaFlicker()
{
}
GameOverScreen::~GameOverScreen()
{
}
Screen* GameOverScreen::getNext()
{
	return nextScreen;
}
bool    GameOverScreen::isRemovable()
{
	return removable;
}
void    GameOverScreen::show(Machine* mach)
{
	font1 = res.findFont("font.3");
	font2 = res.findFont("font.2");
	
	// ...
	Mixer::playMusic(res.findMusic("loser"));
}
void    GameOverScreen::hide(Machine* mach)
{
}
void    GameOverScreen::update(Machine* mach, double dt)
{
	if(Keyboard::isPressed(Key::RETURN))
	{
		Mixer::halt();
		removable = true;
		nextScreen = new PlayingScreen();
	}
	else if(Keyboard::isPressed(Key::ESCAPE))
	{
		Mixer::halt();
		removable = true;
	}
	alphaFlicker.update(dt);
}
void    GameOverScreen::render(Machine* mach, Graphics* gr)
{
	gr->fillRect(SCENE_X, SCENE_Y, SCENE_WIDTH, SCENE_HEIGHT, Color(64,64,64));
	font1->render(gr, SCENE_X + (SCENE_WIDTH-font1->textWidth(MESSAGE_GAME_OVER))/2, 100, MESSAGE_GAME_OVER, alphaFlicker.value());
	font2->render(gr, SCENE_X + (SCENE_WIDTH-font2->textWidth(MESSAGE_PRESS_ENTER))/2, 170, MESSAGE_PRESS_ENTER);
	font2->render(gr, SCENE_X + (SCENE_WIDTH-font2->textWidth(MESSAGE_PRESS_ESCAPE))/2, 200, MESSAGE_PRESS_ESCAPE);
}
