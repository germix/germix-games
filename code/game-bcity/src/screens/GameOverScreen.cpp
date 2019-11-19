////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GameOverScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/GameOverScreen.h>
#include <src/Config.h>
#include <src/res/ResourceManager.h>

#include <mach/Mixer.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>

#include <src/screens/HiScoreScreen.h>

GameOverScreen::GameOverScreen(int score)
: removable(false)
, font(null)
, hiScore(score)
{
	font = res.findFont("Font.BigChars.1");
}
GameOverScreen::~GameOverScreen()
{
}
Screen* GameOverScreen::getNext()
{
	if(removable && hiScore > 0)
		return new HiScoreScreen(hiScore);
	return null;
}
bool    GameOverScreen::isRemovable()
{
	return removable;
}
void    GameOverScreen::show(Machine* mach)
{
	soundChannel = Mixer::playChannel(res.findSound("GameOver"));
}
void    GameOverScreen::hide(Machine* mach)
{
}
void    GameOverScreen::update(Machine* mach, double dt)
{
	if(!Mixer::isPlayingChannel(soundChannel))
	{
		removable = true;
	}
}
void    GameOverScreen::render(Machine* mach, Graphics* gr)
{
	const char* s;
	int         halfWidth = SCREEN_WIDTH/2;
	
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0,0,0));
	
	s = "GAME";
	font->render(gr, halfWidth - font->textWidth(s)/2, 64, s);
	s = "OVER";
	font->render(gr, halfWidth - font->textWidth(s)/2, 116, s);
}

