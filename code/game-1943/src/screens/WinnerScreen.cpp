////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WinnerScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/WinnerScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/screens/PlayingScreen.h>

#include <mach/Mixer.h>
#include <mach/Color.h>
#include <mach/Graphics.h>
#include <mach/Texture.h>
#include <mach/TextureLoader.h>
#include <mach/Keyboard.h>

#include <gamelib/Font.h>

#define MESSAGE_WIN				"JUEGO GANADO"
#define MESSAGE_PRESS_ENTER		"<ENTER> JUGAR OTRA VEZ"
#define MESSAGE_PRESS_ESCAPE	"<ESCAPE> SALIR DEL JUEGO"

WinnerScreen::WinnerScreen()
: removable(false)
, nextScreen(null)
, font1(null)
, font2(null)
, texture(null)
, alphaFlicker()
{
}
WinnerScreen::~WinnerScreen()
{
}
Screen* WinnerScreen::getNext()
{
	return nextScreen;
}
bool    WinnerScreen::isRemovable()
{
	return removable;
}
void    WinnerScreen::show(Machine* mach)
{
	font1 = res.findFont("font.4");
	font2 = res.findFont("font.2");
	texture = res.findTexture("winner");
	
	// ...
	Mixer::playMusic(res.findMusic("winner"));
}
void    WinnerScreen::hide(Machine* mach)
{
}
void    WinnerScreen::update(Machine* mach, double dt)
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
void    WinnerScreen::render(Machine* mach, Graphics* gr)
{
	gr->drawTexture(texture, SCENE_X, SCENE_Y);
	
	font1->render(gr, SCENE_X + (SCENE_WIDTH-font1->textWidth(MESSAGE_WIN))/2, 100, MESSAGE_WIN, alphaFlicker.value());
	font2->render(gr, SCENE_X + (SCENE_WIDTH-font2->textWidth(MESSAGE_PRESS_ENTER))/2, 170, MESSAGE_PRESS_ENTER);
	font2->render(gr, SCENE_X + (SCENE_WIDTH-font2->textWidth(MESSAGE_PRESS_ESCAPE))/2, 200, MESSAGE_PRESS_ESCAPE);
}
