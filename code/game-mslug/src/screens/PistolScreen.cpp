////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PistolScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/PistolScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <string.h>

#include <mach/Keyboard.h>
#include <mach/Graphics.h>
#include <mach/Texture.h>
#include <mach/TextureLoader.h>

#include <gamelib/Font.h>

static struct
{
	int x;
	int y;
} startBubblePoints[] =
{
	{126,138},
	{147,122},
	{196,64},
	{144,144},
	{204,54},
	{168,84},
	{126,48},
	{180,112},
	{148,90},
	{96,80},
	{208,48},
};

static struct
{
	double	x;
	double	y;
	double	time;
	int		frame;
	bool	active;
} bubbles[5] =
{
};

#define MAX_BUBBLES (sizeof(bubbles)/sizeof(bubbles[0]))
#define MAX_START_BUBBLE_POINT (sizeof(startBubblePoints)/sizeof(startBubblePoints[0]))

PistolScreen::PistolScreen()
: removable(false)
, pistolTexture(null)
, bubblesTexture(null)
, backgroundTexture(null)
, offset(0)
, backgroundClock(0.06)
, nextBubbleClock(1.6)
, nextBubble(0)
, nextStartBubblePoint(0)
{
	memset(&bubbles, 0, sizeof(bubbles));
}
PistolScreen::~PistolScreen()
{
}
Screen* PistolScreen::getNext()
{
	return null;
}
bool    PistolScreen::isRemovable()
{
	return removable;
}
void    PistolScreen::show(Machine* mach)
{
	pistolTexture = TextureLoader::load("mslug/screens/pistol/Pistol.png");
	bubblesTexture = TextureLoader::load("mslug/screens/pistol/PistolBubbles.png");
	backgroundTexture = TextureLoader::load("mslug/screens/pistol/PistolBackground.png");

	font1 = res.findFont("Font.8x8.1");
	font2 = res.findFont("Font.8x8.2");
	fontTitle = res.findFont("Font.16x16.1");
}
void    PistolScreen::hide(Machine* mach)
{
	delete pistolTexture;
	delete bubblesTexture;
	delete backgroundTexture;
}
void    PistolScreen::update(Machine* mach, double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		removable = true;
	}
	else
	{
		if(backgroundClock.update(dt))
		{
			offset--;
			if(offset < -backgroundTexture->getHeight())
				offset = 0;
		}
		if(nextBubbleClock.update(dt))
		{
			bubbles[nextBubble].x = startBubblePoints[nextStartBubblePoint].x;
			bubbles[nextBubble].y = startBubblePoints[nextStartBubblePoint].y;
			bubbles[nextBubble].time = 0;
			bubbles[nextBubble].frame = 0;
			bubbles[nextBubble].active = true;

			nextBubble++;
			if(nextBubble >= MAX_BUBBLES)
				nextBubble = 0;
			nextStartBubblePoint++;
			if(nextStartBubblePoint >= MAX_START_BUBBLE_POINT)
				nextStartBubblePoint = 0;
		}
		for(int i = 0; i < MAX_BUBBLES; i++)
		{
			if(bubbles[i].active)
			{
				if(bubbles[i].frame < 12)
				{
					bubbles[i].time += dt;
					bubbles[i].frame = bubbles[i].time/0.1;
				}
				else
				{
					bubbles[i].y -= 70*dt;
					if(bubbles[i].y <= 0)
					{
						bubbles[i].active = false;
					}
				}
			}
		}
	}
}
void    PistolScreen::render(Machine* mach, Graphics* gr)
{
	gr->drawTexture(backgroundTexture, 0, offset);
	if(offset != 0)
	{
		gr->drawTexture(backgroundTexture, 0, backgroundTexture->getHeight() + offset);
	}
	gr->drawTexture(pistolTexture, 89, 28);

	for(int i = 0; i < 4; i++)
	{
		if(bubbles[i].active)
		{
			gr->drawTexture(bubblesTexture,
					bubbles[i].frame*10,
					0,
					bubbles[i].frame*10+10,
					10,
					(int)bubbles[i].x-5,
					(int)bubbles[i].y-5,
					(int)bubbles[i].x+5,
					(int)bubbles[i].y+5);
		}
	}
	static struct
	{
		int x;
		int y;
		const char* text;
	}labels[] =
	{
		{ 16-8, 160, "PROGRAMADORES:" },
		{ 32-8, 160+8, "GERMAN MARTINEZ" },
		{ 32-8, 160+8+8, "GERARDO PONCE" },
	};
	fontTitle->render(gr, SCREEN_WIDTH/2-(9*16)/2, 8-4, "ACERCA DE");
	
	for(int i = 0; i < (sizeof(labels)/sizeof(labels[0])); i++)
	{
		font1->render(gr, labels[i].x, labels[i].y, labels[i].text);
	}
	font2->render(gr, 6*8, 192+16, "FACULTAD DE INGENIERIA - UNLPAM");
}
