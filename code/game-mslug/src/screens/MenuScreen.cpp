////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MenuScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/MenuScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/screens/RankingScreen.h>
#include <src/screens/HeroSelectionScreen.h>
#include <src/screens/ControlsScreen.h>
#include <src/screens/PistolScreen.h>

#include <mach/Math.h>
#include <mach/Mixer.h>
#include <mach/Color.h>
#include <mach/Keyboard.h>
#include <mach/Graphics.h>
#include <mach/Texture.h>
#include <mach/TextureLoader.h>

#include <gamelib/Font.h>

#define HAS_MENU_ART
#define HAS_MENU_RANKING
#ifdef HAS_MENU_ART
#include <src/screens/ArtScreen.h>
#endif
#ifdef HAS_MENU_RANKING
#include <src/screens/RankingScreen.h>
#endif

static struct MenuScreenItem
{
	const char*		text;
	bool			removable;
}items[] =
{
	{ "Jugar",		false	},
	{ "Salir",		true	},
#ifdef HAS_MENU_ART
	{ "Arte",		false	},
#endif
#ifdef HAS_MENU_RANKING
	{ "Ranking",	false	},
#endif
	{ "Controles",	false	},
	{ "Acerca de",	false	},
};
#define MAX_ITEMS			(sizeof(items)/sizeof(items[0]))
#define TIME_FADE			0.06
enum
{
	MENUITEM_PLAY,
	MENUITEM_EXIT,
#ifdef HAS_MENU_ART
	MENUITEM_ART,
#endif
#ifdef HAS_MENU_RANKING
	MENUITEM_RANKING,
#endif
	MENUITEM_CONTROLS,
	MENUITEM_ABOUT,
};

MenuScreen::MenuScreen()
: state(STATE_IDLE)
, button(null)
, background(null)
, font1(null)
, font2(null)
, changedSound(null)
, changedSoundChannel(-1)
, selectedSound(null)
, selectedSoundChannel(-1)
, fadeValue(0)
, fadeColor()
, fadeClock(TIME_FADE)
, nextScreen(null)
, currentMenu(0)
{
}
MenuScreen::~MenuScreen()
{
}
Screen* MenuScreen::getNext()
{
	if(nextScreen)
	{
		Screen* ns = nextScreen;
		
		state = STATE_IDLE;
		fadeValue = 0;
		fadeColor = Color(0, 0, 0, 0);
		nextScreen = null;
		return ns;
	}
	return null;
}
bool    MenuScreen::isRemovable()
{
	return (state == STATE_NOTHING && items[currentMenu].removable);
}
void    MenuScreen::show(Machine* mach)
{
	font1 = res.findFont("Font.8x8.1");
	font2 = res.findFont("Font.8x8.2");
	button = TextureLoader::load("mslug/screens/menu/MenuButton.png");
	background = TextureLoader::load("mslug/screens/menu/Background.png");
	changedSound = Mixer::loadSound("mslug/screens/menu/MenuItemChanged.ogg");
	selectedSound = Mixer::loadSound("mslug/screens/menu/MenuItemSelected.ogg");
}
void    MenuScreen::hide(Machine* mach)
{
}
void    MenuScreen::update(Machine* mach, double dt)
{
	switch(state)
	{
		case STATE_IDLE:
			if(Keyboard::isPressed(Key::UP))
			{
				currentMenu--;
				if(currentMenu < 0)
					currentMenu = MAX_ITEMS-1;
				
				Mixer::haltChannel(changedSoundChannel);
				changedSoundChannel = Mixer::playChannel(changedSound);
			}
			else if(Keyboard::isPressed(Key::DOWN))
			{
				currentMenu++;
				if(currentMenu >= MAX_ITEMS)
					currentMenu = 0;
				
				Mixer::haltChannel(changedSoundChannel);
				changedSoundChannel = Mixer::playChannel(changedSound);
			}
			else if(Keyboard::isPressed(Key::RETURN) || Keyboard::isPressed(Key::KP_ENTER))
			{
				fadeValue = 0;
				fadeColor  = Color(0, 0, 0, Math::min(255, fadeValue));
				state = STATE_FADE_OUT;

				Mixer::playChannel(selectedSound);
			}
			break;
		case STATE_FADE_OUT:
			if(fadeClock.update(dt))
			{
				fadeValue += 20;
				fadeColor  = Color(0, 0, 0, Math::min(255, fadeValue));
				if(fadeValue >= 255)
				{
					state = STATE_NOTHING;
					fadeValue = 255;
					switch(currentMenu)
					{
						case MENUITEM_PLAY:		nextScreen = new HeroSelectionScreen();	break;
						case MENUITEM_EXIT:												break;
#ifdef HAS_MENU_ART
						case MENUITEM_ART:		nextScreen = new ArtScreen();			break;
#endif
#ifdef HAS_MENU_RANKING
						case MENUITEM_RANKING:	nextScreen = new RankingScreen();		break;
#endif
						case MENUITEM_CONTROLS:	nextScreen = new ControlsScreen();		break;
						case MENUITEM_ABOUT:	nextScreen = new PistolScreen();		break;
					}
				}
			}
			break;
		case STATE_NOTHING:
			break;
	}
}
void    MenuScreen::render(Machine* mach, Graphics* gr)
{
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color());
	
	gr->drawTexture(background, 0, 0);
	
	int menuX = 4;
	int menuY = 4;
	int menuSpace = 4;
//	int menuSpace = 8;
	int menuWidth = button->getWidth();
	int menuHeight = button->getHeight();

	for(int i = 0; i < MAX_ITEMS; i++)
	{
		const char* text = items[i].text;
		int         textWidth = font1->textWidth(text);
		
		gr->drawTexture(button, menuX, menuY);
		
		font1->render(gr, menuX + (menuWidth/2-textWidth/2), menuY + 8, text);
		
		if(i == currentMenu)
		{
			//font2->render(gr, menuX+8+4, menuY+8, ">");
			//font2->render(gr, menuX+menuWidth-8-8-4, menuY+8, "<");
			
			font2->render(gr, menuX+8, menuY+8, ">");
			font2->render(gr, menuX+menuWidth-8-8+2, menuY+8, "<");
		}
		// ...
		menuY += menuHeight + menuSpace;
	}
	if(state != STATE_IDLE)
	{
		gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, fadeColor);
	}
}
