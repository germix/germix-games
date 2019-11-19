////////////////////////////////////////////////////////////////////////////////////////////////////
//
// InitGameScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/InitGameScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <mach/Mixer.h>
#include <mach/String.h>
#include <mach/Color.h>
#include <mach/Graphics.h>
#include <mach/Keyboard.h>

#include <gamelib/Font.h>
#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#include <src/screens/ControlsScreen.h>
#include <src/screens/AdventureScreen.h>

#define TIME_LEFT				0.004
#define TIME_TYPED				0.14
#define TIME_HERO_WALK			0.1

//#define USE_MENU_CONTROLS

class InitGameScreen::TypedText
{
	unsigned int	max;
	String			text;
public:
	TypedText(const String& txt) : max(0), text(txt)
	{
		max = 0;
		text = txt;
	}
	~TypedText()
	{
	}
public:
	bool update()
	{
		if(max < text.size())
		{
			max++;
			return false;
		}
		return true;
	}
	void render(Graphics* gr, Font* font, int y)
	{
		font->render(
				gr,
				SCREEN_WIDTH/2 - (font->fontWidth()*max)/2,
				y,
				text.substr(0, max).c_str());
	}
};

const char* InitGameScreen::menuStrings[] = 
{
	"JUGAR",
#ifdef USE_MENU_CONTROLS
	"CONTROLES",
#endif
	"SALIR"
};
enum
{
	MENU_PLAY,
#ifdef USE_MENU_CONTROLS
	MENU_CONTROLS,
#endif
	MENU_EXIT,
	MAX_MENU
};

#include <windows.h>

InitGameScreen::InitGameScreen()
: removable(false)
, nextScreen(null)

, state(STATE_LEFT)
, font(res.findFont("Font.1"))
, background(res.findTexture("InitScreen"))
, backgroundX(SCREEN_WIDTH)

, typedTextsMax(0)

, clock(TIME_LEFT)
, heroWalk(res.findSpriteSheet("Hero")->getSprite("Walk"))
, heroWalkClock(TIME_HERO_WALK)
, heroWalkIndex(0)

, menuSound(res.findSound("MenuItemSelected"))
, menuSelectedIndex(0)
, menuSelectionTexture(res.findTexture("Bonus.Ax"))

{
	typedTexts[0] = new TypedText("REMAKE");
	typedTexts[1] = new TypedText("POR");
	typedTexts[2] = new TypedText("GERMAN MARTINEZ");

#if 0
	state = STATE_0;
	//clock.reset(20);
#else
	Mixer::playMusic(res.findMusic("Intro"));
#endif
}
InitGameScreen::~InitGameScreen()
{
	delete typedTexts[0];
	delete typedTexts[1];
	delete typedTexts[2];
}
Screen* InitGameScreen::getNext()
{
	Screen* s = nextScreen;
	nextScreen = null;
	return s;
}
bool    InitGameScreen::isRemovable()
{
	return removable;
}
void    InitGameScreen::show(Machine* mach)
{
}
void    InitGameScreen::hide(Machine* mach)
{
	Mixer::halt();
}
void    InitGameScreen::update(Machine* mach, double dt)
{
	if(heroWalkClock.update(dt))
	{
		heroWalkIndex++;
		if(heroWalkIndex >= heroWalk->count())
			heroWalkIndex = 0;
	}
	switch(state)
	{
		case STATE_0:
			if(Keyboard::isPressed(Key::ESCAPE))
			{
				state = STATE_LEFT;
				clock.reset(TIME_LEFT);
				Mixer::playMusic(res.findMusic("Intro"));
			}
			break;
		case STATE_LEFT:
			if(Keyboard::isPressed(Key::ESCAPE))
			{
				backgroundX = 0;
				state = STATE_ABOUT;
				clock.reset(TIME_TYPED);
			}
			else
			{
				if(clock.update(dt))
				{
					backgroundX--;
					if(backgroundX == 0)
					{
						state = STATE_ABOUT;
						clock.reset(TIME_TYPED);
					}
				}
			}
			break;
		case STATE_ABOUT:
#if 1
			if(Keyboard::isPressed(Key::ESCAPE))
			{
				state = STATE_NORMAL;
			}
#endif
			if(clock.update(dt))
			{
				if(typedTexts[typedTextsMax]->update())
					typedTextsMax++;
				if(typedTextsMax == 3)
				{
					state = STATE_WATING;
					clock.reset(4);
					typedTextsMax = 2;
				}
			}
			break;
		case STATE_WATING:
			if(clock.update(dt))
			{
				state = STATE_NORMAL;
			}
			break;
		case STATE_NORMAL:
			if(Keyboard::isPressed(Key::UP))
			{
				if(menuSelectedIndex > 0)
				{
					menuSelectedIndex--;
					Mixer::playChannel(menuSound);
				}
			}
			if(Keyboard::isPressed(Key::DOWN))
			{
				if(menuSelectedIndex < MAX_MENU-1)
				{
					menuSelectedIndex++;
					Mixer::playChannel(menuSound);
				}
			}
			if(Keyboard::isPressed(Key::RETURN) || Keyboard::isPressed(Key::KP_ENTER))
			{
				switch(menuSelectedIndex)
				{
					case MENU_PLAY:
						nextScreen = new AdventureScreen();
						break;
#ifdef USE_MENU_CONTROLS
					case MENU_CONTROLS:
						nextScreen = new ControlsScreen();
						break;
#endif
					case MENU_EXIT:
						removable = true;
						break;
				}
			}
			break;
	}
}
void    InitGameScreen::render(Machine* mach, Graphics* gr)
{
//	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color());
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(31, 0, 175));

	gr->drawTexture(background, (int)backgroundX, 0);
	
	heroWalk->render(gr, (int)backgroundX + 32, 88, heroWalkIndex, backgroundX > 0 ? Sprite::FLIP_X : 0);
	switch(state)
	{
		case STATE_LEFT:
			break;
		case STATE_ABOUT:
		case STATE_WATING:
			{
				int y = 100;
				for(int i = 0; i <= typedTextsMax; i++)
				{
					typedTexts[i]->render(gr, font, y);
					y += 16;
				}
			}
			break;
		case STATE_NORMAL:
			{
				int x = 112-8-8+16;
				int y = 152-8;
				for(int i = 0; i < MAX_MENU; i++, y += 16)
				{
					font->render(gr, x, y, menuStrings[i]);
					if(i == menuSelectedIndex)
						gr->drawTexture(menuSelectionTexture, x - 16-8, y-4);
				}
			}
			break;
	}
}

