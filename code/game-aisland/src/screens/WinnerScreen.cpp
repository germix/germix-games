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

#include <mach/Mixer.h>
#include <mach/Keyboard.h>
#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>
#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define TIME_TINA_FREE		1.5
#define TIME_TINA_IDLE		0.2
#define TIME_HERO_WALK		0.1
#define TIME_HERO_IDLE		0.15

const char* WinnerScreen::lines[] = 
{
	"FELICIDADES!",
	"HAS SALVADO",
	"A TU ADORABLE TINA",
};

WinnerScreen::WinnerScreen()
: removable(false)
, state(STATE_WALKING)

, font(res.findFont("Font.1"))

, heroX(-32)
, heroSheet(res.findSpriteSheet("Hero"))
, heroSprite(null)
, heroSpriteIndex(0)
, heroSpriteClock(TIME_HERO_WALK)

, tinaSheet(res.findSpriteSheet("Tina"))
, tinaSprite(null)
, tinaSpriteIndex(0)
, tinaSpriteClock(TIME_TINA_IDLE)

, savingIdleCounter(0)
, happyCoupleTexture(res.findTexture("HappyCouple"))
, happyCoupleHeartY(120)
, happyCoupleHeartTexture(res.findTexture("HappyCoupleHeart"))

{
	heroSprite = heroSheet->getSprite("Walk");
	tinaSprite = tinaSheet->getSprite("Idle");

	Mixer::playMusic(res.findMusic("Winner"));
}
WinnerScreen::~WinnerScreen()
{
}
Screen* WinnerScreen::getNext()
{
	return null;
}
bool    WinnerScreen::isRemovable()
{
	return removable;
}
void    WinnerScreen::show(Machine* mach)
{
}
void    WinnerScreen::hide(Machine* mach)
{
	Mixer::halt();
}
void    WinnerScreen::update(Machine* mach, double dt)
{
	switch(state)
	{
		case STATE_FINISHED:
			if(Keyboard::isPressed(Key::ESCAPE))
			{
				removable = true;
			}
			break;
		case STATE_LOVE:
			happyCoupleHeartY -= (dt * 20);
			if(happyCoupleHeartY < -16)
			{
				state = STATE_FINISHED;
			}
			break;
		case STATE_FREE:
			if(heroSpriteClock.update(dt))
			{
				heroSpriteIndex++;
				if(heroSpriteIndex >= heroSprite->count())
					heroSpriteIndex = 0;
			}
			if(tinaSpriteClock.update(dt))
			{
				tinaSpriteIndex++;
				if(tinaSpriteIndex >= tinaSprite->count())
				{
					state = STATE_LOVE;
				}
			}
			break;
		case STATE_SAVING:
			if(heroSpriteClock.update(dt))
			{
				heroSpriteIndex++;
				if(heroSpriteIndex >= heroSprite->count())
				{
					heroSpriteIndex = 0;
					savingIdleCounter++;
					if(savingIdleCounter == 8)
					{
						state = STATE_FREE;
						tinaSprite = tinaSheet->getSprite("Free");
						tinaSpriteIndex = 0;
						tinaSpriteClock.reset(TIME_TINA_FREE);
					}
				}
			}
			if(tinaSpriteClock.update(dt))
			{
				tinaSpriteIndex++;
				if(tinaSpriteIndex >= tinaSprite->count())
					tinaSpriteIndex = 0;
			}
			break;
		case STATE_WALKING:
			if(heroSpriteClock.update(dt))
			{
				heroSpriteIndex++;
				if(heroSpriteIndex >= heroSprite->count())
					heroSpriteIndex = 0;
			}
			if(tinaSpriteClock.update(dt))
			{
				tinaSpriteIndex++;
				if(tinaSpriteIndex >= tinaSprite->count())
					tinaSpriteIndex = 0;
			}
			heroX += (dt * 45);
			if(heroX >= 120)
			{
				heroX = (int)120;
				state = STATE_SAVING;
				heroSprite = heroSheet->getSprite("Idle");
				heroSpriteIndex = 0;
				heroSpriteClock.reset(TIME_HERO_IDLE);
			}
			break;
		default:
			break;
	}
}
void    WinnerScreen::render(Machine* mach, Graphics* gr)
{
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(31, 0, 175));
	
	int y = 32;
	for(int i = 0; i < 3; i++)
	{
		font->render(gr, SCREEN_WIDTH/2 - font->textWidth(lines[i])/2, y, lines[i]);
		y += (i == 0) ? 24 : 16;
	}
	if(state != STATE_LOVE && state != STATE_FINISHED)
	{
		tinaSprite->render(gr, 136, 168, tinaSpriteIndex, 0);
		heroSprite->render(gr, (int)heroX, 168, heroSpriteIndex, 0);
	}
	else
	{
		gr->drawTexture(happyCoupleTexture, 112, 136);
		gr->drawTexture(happyCoupleHeartTexture, 120, (int)happyCoupleHeartY);
	}
}

