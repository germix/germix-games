////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SelectMapTypeScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/SelectMapTypeScreen.h>
#include <src/Config.h>
#include <src/res/ResourceManager.h>
#include <src/Map.h>
#include <src/base/ListBox.h>
#include <src/screens/SelectMapScreen.h>

#include <mach/Keyboard.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>

SelectMapTypeScreen::SelectMapTypeScreen(Player* ___player1, Player* ___player2)
: removable(false)
, map(null)
, listBox(null)
, nextScreen(null)
, font(res.findFont("Font.Orange"))
, player1(___player1)
, player2(___player2)
{
	map = new Map("bcity/select.tmx");
	listBox = new ListBox(48+8, 96+8, 20, 6, std::vector<String>());
	listBox->append("DEFAULT");
	listBox->append("PERSONALIZADOS");
}
SelectMapTypeScreen::~SelectMapTypeScreen()
{
	printf("~SelectMapTypeScreen()\n");
	delete map;
	delete listBox;
}
Screen* SelectMapTypeScreen::getNext()
{
	Screen* s = nextScreen;
	nextScreen = null;
	return s;
}
bool    SelectMapTypeScreen::isRemovable()
{
	return removable;
}
void    SelectMapTypeScreen::show(Machine* mach)
{
}
void    SelectMapTypeScreen::hide(Machine* mach)
{
}
void    SelectMapTypeScreen::update(Machine* mach, double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		removable = true;
	}
	else if(Keyboard::isPressed(Key::RETURN) || Keyboard::isPressed(Key::KP_ENTER))
	{
		//removable = true;
		if(listBox->getSelectedIndex() == 1)
			nextScreen = new SelectMapScreen(true, player1, player2);
		else
			nextScreen = new SelectMapScreen(false, player1, player2);
	}
	else
	{
		listBox->update(dt);
	}
}
void    SelectMapTypeScreen::render(Machine* mach, Graphics* gr)
{
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0,0,0));

	map->render(gr);
	
	listBox->render(gr);

	font->render(gr, SCREEN_WIDTH/2 - font->textWidth("ESCARAMUSAS")/2, 8*4, "ESCARAMUSAS");
}
