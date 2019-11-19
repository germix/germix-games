////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SelectMapScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/SelectMapScreen.h>
#include <src/Config.h>
#include <src/res/ResourceManager.h>
#include <src/Map.h>
#include <src/base/Sprite.h>

#include <mach/Math.h>
#include <mach/Keyboard.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>

#include <src/utils.h>
#include <src/base/Player.h>
#include <src/base/ListBox.h>
#include <src/screens/PlayingScreen.h>
#include <src/stages/SkirmishStagesProvider.h>

SelectMapScreen::SelectMapScreen(bool custom, Player* ___player1, Player* ___player2)
: removable(false)
, map(null)
, listBox(null)
, nextScreen(null)
, customMaps(custom)
, player1(___player1)
, player2(___player2)
{
	map = new Map("bcity/select.tmx");
	listBox = new ListBox(24+8, 24+8, 26, 22, custom ? getMapsFromCustomMapsFolder() : getMapsFromDefaultMapsFolder());
}
SelectMapScreen::~SelectMapScreen()
{
	delete map;
	delete listBox;
}
Screen* SelectMapScreen::getNext()
{
	Screen* s = nextScreen;
	nextScreen = null;
	return s;
}
bool    SelectMapScreen::isRemovable()
{
	return removable;
}
void    SelectMapScreen::show(Machine* mach)
{
}
void    SelectMapScreen::hide(Machine* mach)
{
}
void    SelectMapScreen::update(Machine* mach, double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		removable = true;
	}
	else if(Keyboard::isPressed(Key::RETURN) || Keyboard::isPressed(Key::KP_ENTER))
	{
		char sz[256];
		if(!customMaps)
			sprintf(sz, "bcity/maps/%s.tmx", listBox->getSelectedString().c_str());
		else
			sprintf(sz, "bcity/custommaps/%s.tmx", listBox->getSelectedString().c_str());
		
		//removable = true;
		nextScreen = new PlayingScreen(new SkirmishStagesProvider(sz), player1, player2);
	}
	else
	{
		listBox->update(dt);
	}
}
void    SelectMapScreen::render(Machine* mach, Graphics* gr)
{
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0,0,0));

	map->render(gr);
	
	listBox->render(gr);
}

