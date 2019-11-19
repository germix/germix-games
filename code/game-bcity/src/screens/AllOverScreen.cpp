////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AllOverScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/AllOverScreen.h>
#include <src/Config.h>
#include <src/res/ResourceManager.h>

#include <mach/Graphics.h>

#include <gamelib/Font.h>

AllOverScreen::AllOverScreen()
: state(STATE_IDLE)
, removable(false)
, font(null)
, clock(2)
, fadeout(0)
{
	font = res.findFont("Font.BigChars.1");
}
AllOverScreen::~AllOverScreen()
{
}
Screen* AllOverScreen::getNext()
{
	return null;
}
bool    AllOverScreen::isRemovable()
{
	return removable;
}
void    AllOverScreen::show(Machine* mach)
{
}
void    AllOverScreen::hide(Machine* mach)
{
}
void    AllOverScreen::update(Machine* mach, double dt)
{
	switch(state)
	{
		case STATE_IDLE:
			if(clock.update(dt))
			{
				clock.reset(0.005);
				state = STATE_FADEOUT;
			}
			break;
		case STATE_FADEOUT:
			if(clock.update(dt))
			{
				if(++fadeout >= 255)
				{
					fadeout = 255;
					removable = true;
				}
			}
			break;
	}
}
void    AllOverScreen::render(Machine* mach, Graphics* gr)
{
	const char* s;
	int         halfWidth = SCREEN_WIDTH/2;
	
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0,0,0));
	
	s = "ALL";
	font->render(gr, halfWidth - font->textWidth(s)/2, 64, s);
	s = "OVER";
	font->render(gr, halfWidth - font->textWidth(s)/2, 116, s);
	
	if(state == STATE_FADEOUT)
	{
		gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0,0,0,fadeout));
	}
}

