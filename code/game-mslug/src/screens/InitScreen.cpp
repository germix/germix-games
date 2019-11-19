////////////////////////////////////////////////////////////////////////////////////////////////////
//
// InitScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/InitScreen.h>
#include <src/ResourceManager.h>
#include <src/Config.h>
#include <src/screens/MenuScreen.h>

#include <mach/Mixer.h>
#include <mach/Color.h>
#include <mach/Texture.h>
#include <mach/TextureLoader.h>
#include <mach/Graphics.h>
#include <mach/Keyboard.h>

#include <stdio.h>

#include <gamelib/Font.h>

#define MAX_LETTERS					9

#define TIME_FADING					5.0/100.0
#define TIME_ANIMATING				4.0/100.0
#define TIME_TEXT_FADING			7.0/100.0
#define TIME_METALSLUG				30.0/100.0
#define VELOCITY_FOR_LETTERS		400.0

class InitScreenLetter
{
public:
	double		posX;
	double		posY;
	int			finalX;
	bool		clash;
	Texture*	texture;
	
	int			width;
	int			height;
	int			xImage1;
	int			xImage2;
public:
	InitScreenLetter(int index, int x, int y)
	{
		char sz[256];
		sprintf(sz, "mslug/screens/intro/Letter-%d.png", (index+1));

		posX = SCREEN_WIDTH;
		posY = (double)y;
		finalX = x;
		clash = false;
		texture = TextureLoader::load(sz);
		width = texture->getWidth()/2;
		height = texture->getHeight();
		xImage1 = 0;
		xImage2 = width;
	}
	~InitScreenLetter()
	{
		delete texture;
	}
};
InitScreen::InitScreen()
{
	nextScreen = null;
}
InitScreen::~InitScreen()
{
	if(letters)
	{
		for(int i = 0; i < MAX_LETTERS; i++)
			delete letters[i];
		delete [] letters;
	}
	if(clashSound)
		Mixer::freeSound(clashSound);
	if(enterSound)
		Mixer::freeSound(enterSound);
	if(metalSlugSound)
		Mixer::freeSound(metalSlugSound);
}
Screen* InitScreen::getNext()
{
	return nextScreen;
}
bool    InitScreen::isRemovable()
{
	return (state == STATE_NOTHING);
}
void    InitScreen::show(Machine* mach)
{
	state = STATE_FADE_IN;
	clock.reset(TIME_FADING);

	fadeDir = -1;
	fadeValue = 255;

	clashSound = Mixer::loadSound("mslug/screens/intro/Intro-Clash.ogg");
	enterSound = Mixer::loadSound("mslug/screens/menu/MenuItemSelected.ogg");
	metalSlugSound = Mixer::loadSound("mslug/screens/intro/Intro-MetalSlug.ogg");

	font = res.findFont("Font.8x8.1");
	text = "PRESIONE <ENTER>";
	textPos = Point(SCREEN_WIDTH/2 - font->textWidth(text)/2, SCREEN_HEIGHT - 20);
	letters = new InitScreenLetter*[MAX_LETTERS];

	letters[0] = new InitScreenLetter(0, 26, 15);
	letters[1] = new InitScreenLetter(1, 104, 33);
	letters[2] = new InitScreenLetter(2, 143, 33);
	letters[3] = new InitScreenLetter(3, 174, 33);
	letters[4] = new InitScreenLetter(4, 221, 33);
	
	letters[5] = new InitScreenLetter(5, 56, 110);
	letters[6] = new InitScreenLetter(6, 102, 109);
	letters[7] = new InitScreenLetter(7, 143, 110);
	letters[8] = new InitScreenLetter(8, 191, 110);
	currentLetter = 0;
	
	nextScreen = null;
}
void    InitScreen::hide(Machine* mach)
{
}
void    InitScreen::update(Machine* mach, double dt)
{
	switch(state)
	{
		case STATE_FADE_IN:
			if(clock.update(dt))
			{
				fadeValue -= 10;
				if(fadeValue <= 0)
				{
					fadeValue = 0;
					state = STATE_ANIMATING;
					clock.reset(TIME_ANIMATING);
				}
			}
			break;
		case STATE_ANIMATING:
			{
				InitScreenLetter* l = letters[currentLetter];
				l->posX -= (double)(VELOCITY_FOR_LETTERS*dt);
				if(l->posX < l->finalX)
				{
					l->posX = (double)l->finalX;
					l->clash = true;
					state = STATE_CLASH;
					
					Mixer::playChannel(clashSound);
				}
			}
			break;
		case STATE_CLASH:
			if(clock.update(dt))
			{
				letters[currentLetter]->clash = false;
				
				if(++currentLetter >= MAX_LETTERS)
				{
					state = STATE_METALSLUG;
					clock.reset(TIME_METALSLUG);
					currentLetter = MAX_LETTERS-1;
				}
				else
				{
					state = STATE_ANIMATING;
				}
			}
			break;
		case STATE_METALSLUG:
			if(clock.update(dt))
			{
				state = STATE_WAITING_FOR_ENTER;
				Mixer::playChannel(metalSlugSound);
				clock.reset(TIME_TEXT_FADING);
			}
			break;
		case STATE_WAITING_FOR_ENTER:
			if(clock.update(dt))
			{
				fadeValue += fadeDir*60;
				if(fadeValue <= 30)
				{
					fadeDir = +1;
					fadeValue = 30;
				}
				else if(fadeValue >= 255)
				{
					fadeDir = -1;
					fadeValue = 255;
				}
			}
			if(Keyboard::isPressed(Key::ESCAPE))
			{
				state = STATE_NOTHING;
			}
			else if(Keyboard::isPressed(Key::RETURN) || Keyboard::isPressed(Key::KP_ENTER))
			{
				state = STATE_NOTHING;
				nextScreen = new MenuScreen();
				Mixer::playChannel(enterSound);
			}
			break;
		case STATE_NOTHING:
			break;
	}
}
void    InitScreen::render(Machine* mach, Graphics* gr)
{
	if(state == STATE_NOTHING)
	{
		return;
	}
	if(state == STATE_FADE_IN)
	{
		gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(fadeValue, fadeValue, fadeValue));
	}
	else
	{
		gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color());
		for(int i = 0; i <= currentLetter; i++)
		{
			InitScreenLetter* l = letters[i];
			int               xImage = l->clash ? l->xImage2 : l->xImage1;
			
			gr->drawTexture(
					l->texture,

					xImage,
					0,
					xImage+l->width,
					l->height,

					(int)l->posX,
					(int)l->posY,
					(int)l->posX+l->width,
					(int)l->posY+l->height
					);
		}
		if(state == STATE_WAITING_FOR_ENTER)
		{
			font->render(gr, textPos.x, textPos.y, text, fadeValue);
		}
	}
}
