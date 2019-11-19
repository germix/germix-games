////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GameOverScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/GameOverScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/HeroInfo.h>

#include <mach/String.h>
#include <mach/Mixer.h>
#include <mach/Keyboard.h>
#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>

GameOverScreen::GameOverScreen(int ___area, int ___round, int ___score)
: removable(false)
, area(___area)
, round(___round)
, score(___score)
, font(res.findFont("Font.1"))
, livesMark(res.findTexture("LivesMark"))
{
	Mixer::playMusic(res.findMusic("GameOver"));
}
GameOverScreen::~GameOverScreen()
{
}
Screen* GameOverScreen::getNext()
{
	return null;
}
bool    GameOverScreen::isRemovable()
{
	return removable;
}
void    GameOverScreen::show(Machine* mach)
{
}
void    GameOverScreen::hide(Machine* mach)
{
	Mixer::halt();
}
void    GameOverScreen::update(Machine* mach, double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		removable = true;
	}
}
void    GameOverScreen::render(Machine* mach, Graphics* gr)
{
	String s;
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color());
	
	//
	// Score
	//
	s = String::fromInt(score);
	font->render(gr, SCREEN_WIDTH/2 - font->textWidth(s.c_str()), 16, s.c_str());
	
	//
	// Vidas
	//
	gr->drawTexture(livesMark, 24, 24);
	font->render(gr, 24+16, 24, "0");
	
	//
	// Area/Ronda
	//
	s = "AREA   " + String::fromInt(area);
	font->render(gr, 96, 72, s.c_str());
	s = "ROUND  " + String::fromInt(round);
	font->render(gr, 96, 96, s.c_str());
	
	//
	// Game Over
	//
//	font->render(gr, 88, 136, "GAME OVER");
	font->render(gr, SCREEN_WIDTH/2 - font->textWidth("GAME OVER")/2, 136, "GAME OVER");
}

