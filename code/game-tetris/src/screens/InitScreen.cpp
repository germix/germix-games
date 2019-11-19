////////////////////////////////////////////////////////////////////////////////////////////////////
//
// InitScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/InitScreen.h>
#include <src/Resources.h>

#include <mach/Mixer.h>
#include <mach/Point.h>
#include <mach/Color.h>
#include <mach/Texture.h>
#include <mach/Machine.h>
#include <mach/Graphics.h>
#include <mach/Keyboard.h>

#include <gamelib/Font.h>

#include <stdio.h>
#include <stdlib.h>

static struct
{
	int type;
	Point point;
}points[] =
{
	{ 1, Point(76 , 100 - 8),	},		// 1
	{ 2, Point(212, 100 - 8),	},		// 2
	{ 1, Point(212, 100 - 8),	},		// 3
	{ 3, Point(50 , 102 - 8),	},		// 4
	{ 2, Point(78 , 102 - 8),	},		// 5
	{ 2, Point(212, 102 - 8),	},		// 6
	{ 2, Point(44 , 102 - 8),	},		// 7
	{ 4, Point(138, 100 - 8),	},		// 8
	{ 2, Point(44 , 102 - 8),	},		// 9
	{ 1, Point(156, 102 - 8),	},		// 10
	{ 1, Point(156, 102 - 8),	},		// 11
	{ 1, Point(174, 102 - 8),	},		// 12
	// ...
	{ 4, Point(76 , 102 - 8),	},		// 13
	{ 3, Point(174, 102 - 8),	},		// 14
};

#define MAX_FIREWORKS (sizeof(points)/sizeof(points[0]))
#define IMAGES_PER_FIREWORKS 5

#define FIREWORKS_TIME_WAIT 1
#define FIREWORKS_TIME_SPLASH 0.05

#define FIREWORKS_STATE_WAIT 0
#define FIREWORKS_STATE_SPLASH 1
#define FIREWORKS_STATE_FINISHED 2

InitScreen::InitScreen()
: nextScreen(null)
{
	music = Mixer::loadMusic("tetris/audio/music/Intro.ogg");
	font = Resources::loadFont("font-1.xml");
	texture = Resources::loadTexture("InitScreen.png");
	removable = false;
	//
	// Cargar imágenes de fuegos artificiales
	//
	fireworks = (Texture**)malloc(sizeof(Texture*)*(4*5));
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			char fname[64];
			sprintf(fname, "fireworks/firework-%d-00%d.png", i+1, j+1);
			fireworks[(i*IMAGES_PER_FIREWORKS)+j] = Resources::loadTexture(fname);
		}
	}
	fireworksIndex = 0;
	fireworksFrame = 0;
	fireworksState = FIREWORKS_STATE_WAIT;
	fireworksClock.reset(0.2);
}
InitScreen::~InitScreen()
{
	free(fireworks);
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
	Mixer::playMusic(music, 1);
}
void    InitScreen::hide(Machine* mach)
{
}
void    InitScreen::update(Machine* mach, double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		removable = true;
	}
	switch(fireworksState)
	{
		case FIREWORKS_STATE_WAIT:
			if(fireworksClock.update(dt))
			{
				fireworksState = FIREWORKS_STATE_SPLASH;
				fireworksClock.reset(FIREWORKS_TIME_SPLASH);
			}
			break;
		case FIREWORKS_STATE_SPLASH:
			if(fireworksClock.update(dt))
			{
				if(++fireworksFrame >= IMAGES_PER_FIREWORKS)
				{
					fireworksFrame = 0;
					if(++fireworksIndex >= MAX_FIREWORKS)
					{
						fireworksState = FIREWORKS_STATE_FINISHED;
					}
					else
					{
						fireworksState = FIREWORKS_STATE_WAIT;
						fireworksClock.reset(FIREWORKS_TIME_WAIT);
					}
				}
			}
			break;
		default:
			if(Keyboard::isPressed(Key::RETURN))
			{
				removable = true;
			}
			break;
	}
}
void    InitScreen::render(Machine* mach, Graphics* gr)
{
	int w = mach->getScreenWidth();
	int h = mach->getScreenHeight();
	
	gr->fillRect(0, 0, w, h, Color());
	if(fireworksState == FIREWORKS_STATE_SPLASH)
	{
		Point pt = points[fireworksIndex].point;
		Texture* tex = fireworks[((points[fireworksIndex].type-1)*IMAGES_PER_FIREWORKS)+fireworksFrame];
		gr->drawTexture(tex, pt.x - tex->getWidth()/2, pt.y - tex->getHeight()/2);
	}
	gr->drawTexture(texture, 0, 0);
	
	if(fireworksState == FIREWORKS_STATE_FINISHED)
		font->render(gr, (w-font->textWidth("<ENTER>"))/2, 184, "<ENTER>");
}
