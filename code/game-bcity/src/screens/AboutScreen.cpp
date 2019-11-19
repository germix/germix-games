////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AboutScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/AboutScreen.h>
#include <src/Map.h>
#include <src/Config.h>
#include <src/res/ResourceManager.h>

#include <mach/Keyboard.h>

#include <gamelib/Font.h>

AboutScreen::AboutScreen()
: removable(false)
, map(null)
{
	map = new Map("bcity/about.tmx");
	font = res.findFont("Font.White");
}
AboutScreen::~AboutScreen()
{
	delete map;
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
	else
	{
		map->update(dt);
	}
}
void    AboutScreen::render(Machine* mach, Graphics* gr)
{
	const char* s;
	
	map->render(gr);
	map->renderTopmost(gr);
	
	s = "PROGRAMADOR";
	font->render(gr, SCREEN_WIDTH/2 - font->textWidth(s)/2, SCREEN_HEIGHT/2 - 16, s);
	s = "GERMAN MARTINEZ";
	font->render(gr, SCREEN_WIDTH/2 - font->textWidth(s)/2, SCREEN_HEIGHT/2 + 8, s);
}

