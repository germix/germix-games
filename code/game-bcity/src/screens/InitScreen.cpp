////////////////////////////////////////////////////////////////////////////////////////////////////
//
// InitScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/InitScreen.h>
#include <src/Config.h>
#include <src/res/ResourceManager.h>
#include <src/screens/AboutScreen.h>
#include <src/screens/PlayingScreen.h>
#include <src/screens/SelectMapScreen.h>
#include <src/screens/SelectMapTypeScreen.h>
#include <src/screens/ConstructionScreen.h>
#include <src/stages/CampaignStagesProvider.h>
#include <src/base/Sprite.h>
#include <src/entities/Tank.h>

#include <mach/Keyboard.h>
#include <mach/Texture.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>

const char* InitScreen::items[] =
{
	"JUGAR",
	"SALIR",
	"ACERCA DE",
	"ESCARAMUZA",
	"CONSTRUCCION",
};

InitScreen::InitScreen()
: state(STATE_SCROLLING)
, removable(false)
, nextScreen(null)

, font(null)
, logo(null)

, offsetY(SCREEN_HEIGHT)
, scrollClock(0.008)

, menuItem(0)
{
	font = res.findFont("Font.White");
	logo = res.findTexture("Title");

	menuIndicator = Config::tankSprites[Tank::TANK_MODEL_HERO_1 + (Tank::TANK_COLOR_BROWN*Tank::MAX_TANK_MODELS)];
}
InitScreen::~InitScreen()
{
}
Screen* InitScreen::getNext()
{
	Screen* s = nextScreen;
	nextScreen = null;
	return s;
}
bool    InitScreen::isRemovable()
{
	return removable;
}
void    InitScreen::show(Machine* mach)
{
	player.reset();
}
void    InitScreen::hide(Machine* mach)
{
}
void    InitScreen::update(Machine* mach, double dt)
{
	switch(state)
	{
		case STATE_SCROLLING:
			if(scrollClock.update(dt))
			{
				if(--offsetY <= 0)
				{
					state = STATE_MENU;
					offsetY = 0;
				}
			}
			break;
		case STATE_MENU:
			if(Keyboard::isPressed(Key::UP))
			{
				if(--menuItem < 0) menuItem = MAX_MENUITEMS-1;
			}
			else if(Keyboard::isPressed(Key::DOWN))
			{
				if(++menuItem >= MAX_MENUITEMS) menuItem = 0;
			}
			else if(Keyboard::isPressed(Key::RETURN) || Keyboard::isPressed(Key::KP_ENTER))
			{
				switch(menuItem)
				{
					case MENUITEM_PLAY:
						nextScreen = new PlayingScreen(new CampaignStagesProvider(), &player, null);
						break;
					case MENUITEM_EXIT:
						removable = true;
						break;
					case MENUITEM_ABOUT:
						nextScreen = new AboutScreen();
						break;
					case MENUITEM_SKIRMISH:
						nextScreen = new SelectMapTypeScreen(&player, null);
						break;
					case MENUITEM_CONSTRUCTION:
						nextScreen = new ConstructionScreen();
						break;
				}
			}
			/*
			else if(Keyboard::isPressed(Key::ESCAPE))
			{
				removable = true;
			}
			*/
			break;
	}
}
void    InitScreen::render(Machine* mach, Graphics* gr)
{
	const int startMenuTexts = 128;
	
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0,0,0));
	
	gr->drawTexture(logo, SCREEN_WIDTH/2 - logo->getWidth()/2, offsetY + 40);
	
	menuIndicator->render(gr, 64, offsetY + startMenuTexts + menuItem*16 - 4, 6);
	
	for(int i = 0, y = startMenuTexts; i < MAX_MENUITEMS; i++, y += 16)
	{
		font->render(gr, 88, offsetY+y, items[i]);
	}
}

