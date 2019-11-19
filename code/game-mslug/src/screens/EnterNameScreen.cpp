////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnterNameScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/EnterNameScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/ranking/Ranking.h>

#include <mach/Keyboard.h>
#include <mach/Graphics.h>
#include <mach/Texture.h>
#include <mach/TextureLoader.h>

#include <gamelib/Font.h>
#include <gamelib/TimeClock.h>

class EnterNameScreen::StringEdit
{
	int			max;
	Font*		font;
	char		text[12+1];
	int			cursor;
	bool		accepted;
	bool		blinkingOn;
	TimeClock	blinkingClock;
	int			blinkingCount;
public:
	StringEdit(Font* f)
		: max(12)
		, font(f)
		, cursor(0)
		, accepted(false)
		, blinkingOn(false)
		, blinkingClock(0.2)
		, blinkingCount(0)
	{
		text[0] = 0;
	}
public:
	bool update(double dt)
	{
		if(!accepted)
		{
			static struct
			{
				int k;
				char ch;
			}keys[] =
			{
				{ Key::LETTER_A, 'A' },
				{ Key::LETTER_B, 'B' },
				{ Key::LETTER_C, 'C' },
				{ Key::LETTER_D, 'D' },
				{ Key::LETTER_E, 'E' },
				{ Key::LETTER_F, 'F' },
				{ Key::LETTER_G, 'G' },
				{ Key::LETTER_H, 'H' },
				{ Key::LETTER_I, 'I' },
				{ Key::LETTER_J, 'J' },
				{ Key::LETTER_K, 'K' },
				{ Key::LETTER_L, 'L' },
				{ Key::LETTER_M, 'M' },
				{ Key::LETTER_N, 'N' },
				{ Key::LETTER_O, 'O' },
				{ Key::LETTER_P, 'P' },
				{ Key::LETTER_Q, 'Q' },
				{ Key::LETTER_R, 'R' },
				{ Key::LETTER_S, 'S' },
				{ Key::LETTER_T, 'T' },
				{ Key::LETTER_U, 'U' },
				{ Key::LETTER_V, 'V' },
				{ Key::LETTER_W, 'W' },
				{ Key::LETTER_X, 'X' },
				{ Key::LETTER_Y, 'Y' },
				{ Key::LETTER_Z, 'Z' },
			};
			if(cursor > 0)
			{
				if(Keyboard::isPressed(Key::BACKSPACE))
				{
					text[--cursor] = 0;
				}
			}
			if(cursor < max)
			{
				for(int i = 0; i < (sizeof(keys)/sizeof(keys[0])); i++)
				{
					if(Keyboard::isPressed(keys[i].k))
					{
						text[cursor++] = keys[i].ch;
						break;
					}
				}
				text[cursor] = 0;
			}
		}
		if(blinkingClock.update(dt))
		{
			if(blinkingCount < 10)
			{
				blinkingOn = !blinkingOn;
				if(accepted)
				{
					if(10 == ++blinkingCount)
					{
						blinkingOn = true;
					}
				}
			}
		}
		return (blinkingCount == 10);
	}
	void render(Graphics* gr, int x, int y)
	{
		if(accepted)
		{
			if(blinkingOn)
				font->render(gr, x, y, text);
		}
		else
		{
			font->render(gr, x, y, text);
			if(blinkingOn)
				font->render(gr, x+font->fontWidth()*cursor, y, (char)127);
		}
	}
	const char* getText() const
	{
		return text;
	}
	void accept()
	{
		if(!accepted && cursor > 0)
		{
			accepted = true;
			blinkingClock.reset(0.06);
		}
	}
};

EnterNameScreen::EnterNameScreen(int ___score, int ___hostages)
: state(STATE_FADE_IN)
, removable(false)
, font(null)
, background(null)
, shootingStar(null)
, shootingStarX(0)
, shootingStarY(0)
, shootingStarState(SHOOTING_STAR_STATE_WAITING)
, shootingStarClock(0.01)
, stringEdit(null)
, fadingValue(255)
, fadingClock(0.05)
, score(___score)
, hostages(___hostages)
{
	sprintf(scoreText, "PUNTAJE: %d", score);
	sprintf(hostagesText, "PRISIONEROS LIBERADOS: %d", hostages);
}
EnterNameScreen::~EnterNameScreen()
{
}
Screen* EnterNameScreen::getNext()
{
	return null;
}
bool    EnterNameScreen::isRemovable()
{
	return removable;
}
void    EnterNameScreen::show(Machine* mach)
{
	font = res.findFont("Font.8x8.1");
	background = TextureLoader::load("mslug/screens/entername/background.png");
	shootingStar = TextureLoader::load("mslug/screens/entername/shooting-star.png");

	stringEdit = new StringEdit(font);
}
void    EnterNameScreen::hide(Machine* mach)
{
	if(background)
		delete background;
	if(shootingStar)
		delete shootingStar;

	delete stringEdit;
}
void    EnterNameScreen::update(Machine* mach, double dt)
{
	switch(shootingStarState)
	{
		case SHOOTING_STAR_STATE_WAITING:
			if(shootingStarClock.update(dt))
			{
				shootingStarX = shootingStarRandom.nextInt(96, 304+80);
				shootingStarY = 0;
				if(shootingStarX >= SCREEN_WIDTH)
				{
					shootingStarX = SCREEN_WIDTH;
					shootingStarY = shootingStarRandom.nextInt(16, 80);
				}
				shootingStarState = SHOOTING_STAR_STATE_FALLING;
			}
			break;
		case SHOOTING_STAR_STATE_FALLING:
			shootingStarX -= dt*160;
			shootingStarY += dt*160;
			if(shootingStarX+15 < 0 || shootingStarY-15 > SCREEN_HEIGHT)
			{
				shootingStarState = SHOOTING_STAR_STATE_WAITING;
			}
			break;
	}
	if(state == STATE_NORMAL)
	{
		if(Keyboard::isPressed(Key::RETURN) || Keyboard::isPressed(Key::KP_ENTER))
		{
			stringEdit->accept();
		}
		else
		{
			if(stringEdit->update(dt))
			{
				state = STATE_FADE_OUT;
			}
		}
	}
	else if(state == STATE_FADE_IN)
	{
		if(fadingClock.update(dt))
		{
			fadingValue -= 10;
			if(fadingValue <= 0)
			{
				fadingValue = 0;
				state = STATE_NORMAL;
			}
		}
	}
	else if(state == STATE_FADE_OUT)
	{
		if(fadingClock.update(dt))
		{
			fadingValue += 10;
			if(fadingValue >= 255)
			{
				fadingValue = 255;
				removable = true;
				Ranking("mslug-ranking.xml").addRecord(stringEdit->getText(), score).save();
			}
		}
	}
}
void    EnterNameScreen::render(Machine* mach, Graphics* gr)
{
	gr->drawTexture(background, 0, 0);
	if(shootingStarState == SHOOTING_STAR_STATE_FALLING)
	{
		gr->drawTexture(shootingStar, (int)shootingStarX, (int)shootingStarY);
	}
	font->render(gr, 16, 112+32+16, scoreText);
	font->render(gr, 16, 128+32+16, hostagesText);
	
	stringEdit->render(gr, 16, 204);
	if(state != STATE_NORMAL)
	{
		gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0, 0, 0, fadingValue));
	}
}

