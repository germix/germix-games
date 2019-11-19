////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HiScoreScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/HiScoreScreen.h>
#include <src/Config.h>
#include <src/res/ResourceManager.h>

#include <stdlib.h>

#include <mach/Mixer.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>

HiScoreScreen::HiScoreScreen(int score)
: removable(false)
, soundChannel(-1)
, fontIndex(0)
, fontClock(0.02)
{
	charFonts[0] = res.findFont("Font.BigChars.1");
	charFonts[1] = res.findFont("Font.BigChars.2");
	charFonts[2] = res.findFont("Font.BigChars.3");
	charFonts[3] = res.findFont("Font.BigChars.4");
	
	numberFonts[0] = res.findFont("Font.BigNumbers.1");
	numberFonts[1] = res.findFont("Font.BigNumbers.2");
	numberFonts[2] = res.findFont("Font.BigNumbers.3");
	numberFonts[3] = res.findFont("Font.BigNumbers.4");
	
	itoa(score, scoreText, 10);
}
HiScoreScreen::~HiScoreScreen()
{
}
Screen* HiScoreScreen::getNext()
{
	return null;
}
bool    HiScoreScreen::isRemovable()
{
	return removable;
}
void    HiScoreScreen::show(Machine* mach)
{
	soundChannel = Mixer::playChannel(res.findSound("HiScore"));
}
void    HiScoreScreen::hide(Machine* mach)
{
}
void    HiScoreScreen::update(Machine* mach, double dt)
{
	if(!Mixer::isPlayingChannel(soundChannel))
	{
		removable = true;
	}
	else if(fontClock.update(dt))
	{
		if(++fontIndex == 4)
			fontIndex = 0;
	}
}
void    HiScoreScreen::render(Machine* mach, Graphics* gr)
{
	const char* s;
	int         halfWidth = SCREEN_WIDTH/2;
	
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0,0,0));
	
	s = "HISCORE";
	charFonts[fontIndex]->render(gr, halfWidth - charFonts[fontIndex]->textWidth(s)/2, 40, s);
	s = scoreText;
	numberFonts[fontIndex]->render(gr, halfWidth - numberFonts[fontIndex]->textWidth(s)/2, 96, s);
}

