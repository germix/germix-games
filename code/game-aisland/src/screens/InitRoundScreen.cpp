////////////////////////////////////////////////////////////////////////////////////////////////////
//
// InitRoundScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/InitRoundScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/HeroInfo.h>

#include <mach/String.h>
#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>
#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define TIME_HERO_WALK 0.1

InitRoundScreen::InitRoundScreen(int ___area, int ___round, HeroInfo* ___info)
: removable(false)
, nextScreen(null)

, info(___info)
, area(___area)
, round(___round)
, clock(2)

, font(res.findFont("Font.1"))
, livesMark(res.findTexture("LivesMark"))
, healthMark(res.findTexture("HealthMark"))

, heroWalk(res.findSpriteSheet("Hero")->getSprite("Walk"))
, heroWalkClock(TIME_HERO_WALK)
, heroWalkIndex(0)
{
}
InitRoundScreen::~InitRoundScreen()
{
}
Screen* InitRoundScreen::getNext()
{
	Screen* s = nextScreen;
	nextScreen = null;
	return s;
}
bool    InitRoundScreen::isRemovable()
{
	return removable;
}
void    InitRoundScreen::show(Machine* mach)
{
}
void    InitRoundScreen::hide(Machine* mach)
{
}
void    InitRoundScreen::update(Machine* mach, double dt)
{
	if(heroWalkClock.update(dt))
	{
		heroWalkIndex++;
		if(heroWalkIndex >= heroWalk->count())
			heroWalkIndex = 0;
	}
	if(clock.update(dt))
	{
		removable = true;
	}
}
void    InitRoundScreen::render(Machine* mach, Graphics* gr)
{
	String s;
	
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color());
	
	//
	// Score
	//
	s = String::fromInt(info->score);
	font->render(gr, 160 - font->textWidth(s.c_str()), 16, s.c_str());
	
	//
	// Vidas
	//
	gr->drawTexture(livesMark, 24, 24);
	s = String::fromInt(info->lives-1);
	font->render(gr, 24+16, 24, s.c_str());
	
	//
	// Health
	//
	{
		int x = 80;
		int y = 30;
		for(int i = 0; i < info->health; i++)
		{
			gr->drawTexture(healthMark, x, y);
			x += 5;
		}
	}
	
	//
	// Area/Ronda
	//
	s = "AREA   " + String::fromInt(area);
	font->render(gr, 96, 72, s.c_str());
	s = "ROUND  " + String::fromInt(round);
	font->render(gr, 96, 96, s.c_str());
	
	//
	// Hero & Lives
	//
	heroWalk->render(gr, 104, 168, heroWalkIndex, 0);
	font->render(gr, 104 + 8*3, 168 - 24, "X");
	font->render(gr, 104 + 8*6, 168 - 24, String::fromInt(info->lives).c_str());
}

