////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ControlsScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/ControlsScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <mach/Keyboard.h>
#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>

ControlsScreen::ControlsScreen()
: removable(false)
, font1(res.findFont("Font.1"))
, font2(res.findFont("Font.2"))
{
}
ControlsScreen::~ControlsScreen()
{
}
Screen* ControlsScreen::getNext()
{
	return null;
}
bool    ControlsScreen::isRemovable()
{
	return removable;
}
void    ControlsScreen::show(Machine* mach)
{
}
void    ControlsScreen::hide(Machine* mach)
{
}
void    ControlsScreen::update(Machine* mach, double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		removable = true;
	}
}
void    ControlsScreen::render(Machine* mach, Graphics* gr)
{
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color());
	
	font2->render(gr, (SCREEN_WIDTH-font2->textWidth("CONTROLES"))/2, 8, "CONTROLES");
	
	int x = 16;
	int y = 64;
	font1->render(gr, x, y, "X - SALTAR");
	font1->render(gr, x, y+16, "Z - FUERZA/ATACAR");
}

