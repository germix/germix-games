////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RoundBonusScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/RoundBonusScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/HeroInfo.h>

#include <mach/Mixer.h>
#include <mach/String.h>
#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>

#define WAIT_TIME		0.8
#define SCORE_TIME		0.05

RoundBonusScreen::RoundBonusScreen(HeroInfo* i)
: removable(false)
, state(STATE_WAIT_1)
, info(i)
, clock(WAIT_TIME)

, font(res.findFont("Font.1"))
, pot(res.findTexture("Pot"))
, livesMark(res.findTexture("LivesMark"))
, healthMark(res.findTexture("HealthMark"))

, bonus(0)
, potBonus(0)
, maxBonus(0)

, soundAddScore(res.findSound("AddScore"))
, soundPotBonus(res.findSound("PotBonus"))
{
}
RoundBonusScreen::~RoundBonusScreen()
{
}
Screen* RoundBonusScreen::getNext()
{
	return null;
}
bool    RoundBonusScreen::isRemovable()
{
	return removable;
}
void    RoundBonusScreen::show(Machine* mach)
{
}
void    RoundBonusScreen::hide(Machine* mach)
{
}
void    RoundBonusScreen::update(Machine* mach, double dt)
{
	switch(state)
	{
		case STATE_WAIT_1:
			if(clock.update(dt))
			{
				state = STATE_ADD_BONUS;
				clock.reset(SCORE_TIME);
			}
			break;
		case STATE_ADD_BONUS:
			if(clock.update(dt))
			{
				bonus += 20;
				if((bonus % 140) == 0)
				{
					info->health--;
					if(info->health == 0)
					{
						state = STATE_WAIT_2;
						clock.reset(WAIT_TIME);
					}
				}
			}
			break;
		case STATE_WAIT_2:
			if(clock.update(dt))
			{
				state = STATE_ADD_SCORE_1;
				clock.reset(SCORE_TIME);
				maxBonus = bonus;
			}
			break;
		case STATE_ADD_SCORE_1:
			if(clock.update(dt))
			{
				Mixer::playChannel(soundAddScore);
				bonus -= 20;
				info->score += 20;
				if(bonus == 0)
				{
					state = STATE_WAIT_3;
					clock.reset(WAIT_TIME);
				}
			}
			break;
		case STATE_WAIT_3:
			if(clock.update(dt))
			{
				if(!info->pot)
				{
					state = STATE_FINISHED;
				}
				else
				{
					state = STATE_WAIT_4;
					Mixer::playChannel(soundPotBonus);
					bonus = maxBonus;
					potBonus = maxBonus;
				}
			}
			break;
		case STATE_WAIT_4:
			if(clock.update(dt))
			{
				state = STATE_ADD_SCORE_2;
				clock.reset(SCORE_TIME);
			}
			break;
		case STATE_ADD_SCORE_2:
			if(clock.update(dt))
			{
				Mixer::playChannel(soundAddScore);
				bonus -= 20;
				info->score += 20;
				if(bonus == 0)
				{
					state = STATE_WAIT_5;
					clock.reset(WAIT_TIME);
				}
			}
			break;
		case STATE_WAIT_5:
			if(clock.update(dt))
			{
				state = STATE_ADD_SCORE_3;
				clock.reset(SCORE_TIME);
			}
			break;
		case STATE_ADD_SCORE_3:
			if(clock.update(dt))
			{
				Mixer::playChannel(soundAddScore);
				potBonus -= 20;
				info->score += 20;
				if(potBonus == 0)
				{
					state = STATE_FINISHED;
					clock.reset(WAIT_TIME);
				}
			}
			break;
		case STATE_FINISHED:
			if(clock.update(dt))
			{
				removable = true;
			}
			break;
	}
}
void    RoundBonusScreen::render(Machine* mach, Graphics* gr)
{
	String s;
	
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color());
	
	//
	// Vidas
	//
	gr->drawTexture(livesMark, 24, 24);
	s = String::fromInt(info->lives-1);
	font->render(gr, 24+16, 24, s.c_str());
	
	//
	// Score
	//
	s = String::fromInt(info->score);
	font->render(gr, 160 - font->textWidth(s.c_str()), 16, s.c_str());
	
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
	// Round Bonus
	//
	font->render(gr, 80, 72, "ROUND BONUS");
	s = String::fromInt(bonus);
	font->render(gr, 160 - font->textWidth(s.c_str()), 96, s.c_str());
	
	//
	// Pot Bonus
	//
	if(info->pot)
	{
		font->render(gr, 80, 128, "POT   BONUS");
		s = String::fromInt(potBonus);
		font->render(gr, 160 - font->textWidth(s.c_str()), 152, s.c_str());
		
		gr->drawTexture(pot, 112, 176);
	}
}

