////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MenuScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/MenuScreen.h>
#include <src/Config.h>
#include <src/resources/ResourceManager.h>
#include <src/screens/AboutScreen.h>
#include <src/screens/SelectMapScreen.h>
#include <src/screens/SelectThemeScreen.h>
#include <src/tiled/TiledMap.h>

#include <mach/Texture.h>
#include <mach/Graphics.h>
#include <mach/Keyboard.h>

#include <gamelib/Font.h>

const char* MenuScreen::itemTexts[] =
{
	"JUGAR",
	"SALIR",
	"TEMAS",
	"ACERCA DE",
};
#define MAX_ITEMS (sizeof(itemTexts)/sizeof(itemTexts[0]))

enum
{
	MENU_PLAY,
	MENU_EXIT,
	MENU_THEMES,
	MENU_ABOUT,
};

MenuScreen::MenuScreen()
: removable(false)
, nextScreen(null)
, tiledMap(null)
, currentItem(0)
, font(null)
, imageTitle(null)
, imageArrowLeft(null)
, imageArrowRight(null)
{
	tiledMap = new TiledMap("pacman/screens/main-menu.tmx");

	font = res.findFont("Font.White");
	imageTitle = res.findTexture("Title");
	imageArrowLeft = res.findTexture("ArrowLeft");
	imageArrowRight = res.findTexture("ArrowRight");
}
MenuScreen::~MenuScreen()
{
	delete tiledMap;
}
Screen* MenuScreen::getNext()
{
	Screen* s = nextScreen;
	nextScreen = null;
	return s;
}
bool    MenuScreen::isRemovable()
{
	return removable;
}
void    MenuScreen::show(Machine* mach)
{
}
void    MenuScreen::hide(Machine* mach)
{
}
void    MenuScreen::update(Machine* mach, double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		removable = true;
	}
	else if(Keyboard::isPressed(Key::UP))
	{
		currentItem--;
		if(currentItem < 0)
			currentItem = 0;
	}
	else if(Keyboard::isPressed(Key::DOWN))
	{
		currentItem++;
		if(currentItem >= MAX_ITEMS)
			currentItem = MAX_ITEMS-1;
	}
	else if(Keyboard::isPressed(Key::RETURN) || Keyboard::isPressed(Key::KP_ENTER))
	{
		switch(currentItem)
		{
			case MENU_PLAY:		nextScreen = new SelectMapScreen();		break;
			case MENU_EXIT:		removable = true;						break;
			case MENU_THEMES:	nextScreen = new SelectThemeScreen();	break;
			case MENU_ABOUT:	nextScreen = new AboutScreen();			break;
		}
	}
}
void    MenuScreen::render(Machine* mach, Graphics* gr)
{
	tiledMap->render(gr, 0, 0);
	
	int x = SCREEN_WIDTH/2 - imageTitle->getWidth()/2;
	int y = SCREEN_HEIGHT/2 - imageTitle->getHeight()/2;
	gr->drawTexture(imageTitle, x, y-50);
	
	y += 30;
	for(int i = 0; i < MAX_ITEMS; i++)
	{
		int txtw = font->textWidth(itemTexts[i]);
		int txtx = SCREEN_WIDTH/2 - txtw/2;
		font->render(gr, txtx, y, itemTexts[i]);
		if(i == currentItem)
		{
			gr->drawTexture(imageArrowRight, txtx-16, y);
			gr->drawTexture(imageArrowLeft, txtx+txtw+8, y);
		}
		y += 16;
	}
}
