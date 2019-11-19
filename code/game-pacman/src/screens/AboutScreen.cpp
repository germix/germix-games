////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AboutScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/AboutScreen.h>
#include <src/Config.h>
#include <src/resources/ResourceManager.h>
#include <src/tiled/TiledMap.h>

#include <mach/Keyboard.h>

#include <gamelib/Font.h>

AboutScreen::AboutScreen()
: removable(false)
{
	tiledMap = new TiledMap("pacman/screens/about.tmx");

	font = res.findFont("Font.White");
}
AboutScreen::~AboutScreen()
{
	delete tiledMap;
}
Screen* AboutScreen::getNext()
{
	return null;
}
bool    AboutScreen::isRemovable()
{
	return removable;
}
void    AboutScreen::show(Machine* mach)
{
}
void    AboutScreen::hide(Machine* mach)
{
}
void    AboutScreen::update(Machine* mach, double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		removable = true;
	}
}
void    AboutScreen::render(Machine* mach, Graphics* gr)
{
	tiledMap->render(gr, 0, 0);

	const char* s1 = "PROGRAMADOR";
	const char* s2 = "GERMAN MARTINEZ";
	font->render(gr, SCREEN_WIDTH/2 - font->textWidth(s1)/2, SCREEN_HEIGHT/2 - 8, s1);
	font->render(gr, SCREEN_WIDTH/2 - font->textWidth(s2)/2, SCREEN_HEIGHT/2 + 8, s2);
}
