////////////////////////////////////////////////////////////////////////////////////////////////////
//
// StatisticsScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/StatisticsScreen.h>
#include <src/Config.h>
#include <src/res/ResourceManager.h>
#include <src/base/Sprite.h>
#include <src/entities/Tank.h>

#include <mach/Mixer.h>
#include <mach/Keyboard.h>
#include <mach/Texture.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>

#define TIME_COUNTER		0.3
#define TIME_WAIT_FOR_EXIT	2.5

StatisticsScreen::StatisticsScreen(const std::string& stageName,
						Player* player1, const int* victims1, bool alive1)
: state(STATE_COUNTING)
, removable(false)
, currentEnemy(0)
, clock(TIME_COUNTER)

, showTotal(false)

, heroValues1(null)
, heroValues2(null)

, fontRed(null)
, fontWhite(null)
, fontOrange(null)

, tickSound(null)

, lineTexture(null)
{
	fontRed = res.findFont("Font.Red");
	fontWhite = res.findFont("Font.White");
	fontOrange = res.findFont("Font.Orange");

	lineTexture = res.findTexture("Line");

	stageText = "STAGE " + stageName;

	if(player1 != null)
		heroValues1 = new HeroValues(true, player1, victims1, alive1);
}
StatisticsScreen::StatisticsScreen(const std::string& stageName,
						Player* player1, const int* victims1, bool alive1,
						Player* player2, const int* victims2, bool alive2)
: state(STATE_COUNTING)
, removable(false)
, currentEnemy(0)
, clock(TIME_COUNTER)

, showTotal(false)

, heroValues1(null)
, heroValues2(null)

, fontRed(null)
, fontWhite(null)
, fontOrange(null)

, tickSound(null)

, lineTexture(null)
{
	fontRed = res.findFont("Font.Red");
	fontWhite = res.findFont("Font.White");
	fontOrange = res.findFont("Font.Orange");

	lineTexture = res.findTexture("Line");

	stageText = "STAGE " + stageName;

	if(player1 != null)
		heroValues1 = new HeroValues(true, player1, victims1, alive1);
	if(player2 != null)
		heroValues2 = new HeroValues(false, player2, victims2, alive2);
}
StatisticsScreen::~StatisticsScreen()
{
}
Screen* StatisticsScreen::getNext()
{
	return null;
}
bool    StatisticsScreen::isRemovable()
{
	return removable;
}
void    StatisticsScreen::show(Machine* mach)
{
}
void    StatisticsScreen::hide(Machine* mach)
{
}
void    StatisticsScreen::update(Machine* mach, double dt)
{
	switch(state)
	{
		case STATE_COUNTING:
			if(clock.update(dt))
			{
				bool b1 = incrementValue(heroValues1, currentEnemy);
				bool b2 = incrementValue(heroValues2, currentEnemy);
				
				if(b1 || b2)
					Mixer::playChannel(tickSound);
				
				if(!b1 && !b2)
				{
					currentEnemy++;
					if(currentEnemy == 4)
					{
						currentEnemy--;
						state = STATE_EXTRA_BONUS;
						showTotal = true;
					}
				}
			}
			break;
		case STATE_EXTRA_BONUS:
			if(clock.update(dt))
			{
				if((heroValues1 != null && heroValues1->alive) && (heroValues2 != null && heroValues2->alive))
				{
					if(heroValues1->currentScore > heroValues2->currentScore)
						heroValues1->addExtraBonus();
					else if(heroValues1->currentScore < heroValues2->currentScore)
						heroValues2->addExtraBonus();
				}
				else if(heroValues1 != null && heroValues1->alive)
				{
					heroValues1->addExtraBonus();
				}
				else if(heroValues2 != null && heroValues2->alive)
				{
					heroValues2->addExtraBonus();
				}
				state = STATE_IDLE;
				clock.reset(TIME_WAIT_FOR_EXIT);
			}
			break;
		case STATE_IDLE:
			if(clock.update(dt))
			{
				removable = true;
			}
			else if(Keyboard::isPressed(Key::ESCAPE))
			{
				removable = true;
			}
			break;
	}
}
void    StatisticsScreen::render(Machine* mach, Graphics* gr)
{
	int halfWidth = SCREEN_WIDTH/2;
	
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0,0,0));
	
	renderInfo(gr, heroValues1);
	renderInfo(gr, heroValues2);
	
	int y = 84;
	for(int i = 0; i < 4; i++, y += 24)
	{
		Sprite* sp = Config::tankSprites[
						(Tank::TANK_MODEL_ENEMY_1+i)
						+ (Tank::TANK_COLOR_GRAY*Tank::MAX_TANK_MODELS)];
		
		sp->render(gr, halfWidth - 16/2 + 1, y, 0);
		if(i <= currentEnemy)
		{
			renderValue(gr, heroValues1, y+4, i);
			renderValue(gr, heroValues2, y+4, i);
		}
	}
	gr->drawTexture(lineTexture, halfWidth - lineTexture->getWidth()/2, 173);
	
	//
	// Dibujar indicador de stage
	//
	fontWhite->render(gr, SCREEN_WIDTH/2 - fontWhite->textWidth(stageText.c_str())/2, 32, stageText.c_str());
}
void StatisticsScreen::renderInfo(Graphics* gr, HeroValues* hv)
{
	if(hv != null)
	{
		char sz[32];
		
		// Tipo de jugador
		sprintf(sz, "%c-PLAYER", (char)((int)'Z'+ ((hv->isPlayerOne)?+1:2)));
		renderColumn2(gr, hv, 48, fontRed, sz);
		
		// Puntaje total del jugador
		sprintf(sz, "%d", hv->getPlayerScore());
		renderColumn2(gr, hv, 64, fontOrange, sz);
		
		if(showTotal)
		{
			int value = 0;
			
			for(unsigned int i = 0; i < 4; i++)
				value += hv->values[i];
			
			sprintf(sz, "%d", value);
			renderColumn1(gr, hv, 176, fontWhite, sz);
			
			fontWhite->render(gr, 88-fontWhite->textWidth("TOTAL"), 176, "TOTAL");
		}
		if(hv->hasExtraBonus)
		{
			renderColumn2(gr, hv, 192+8, fontRed, "BONUS!  ");
			renderColumn2(gr, hv, 200+8, fontWhite, "1000 PTS");
		}
	}
}
void StatisticsScreen::renderArrow(Graphics* gr, HeroValues* hv, int y)
{
	int arrowDx = 8;
	
	if(!hv->isPlayerOne)
		Config::arrows->render(gr, (SCREEN_WIDTH/2)+arrowDx, y, 1);
	else
		Config::arrows->render(gr, (SCREEN_WIDTH/2)-arrowDx-8, y, 0);
}
void StatisticsScreen::renderValue(Graphics* gr, HeroValues* hv, int y, int index)
{
	if(hv != null)
	{
		char sz[16];
		int value = hv->tmpValues[index];
		
		renderArrow(gr, hv, y);
		
		sprintf(sz, "%d", value);
		renderColumn1(gr, hv, y, fontWhite, sz);
		
		sprintf(sz, "%d PTS", (value * ((index+1)*100)));
		renderColumn2(gr, hv, y, fontWhite, sz);
	}
}
void StatisticsScreen::renderColumn1(Graphics* gr, HeroValues* hv, int y, Font* f, const char* valueString)
{
	if(!hv->isPlayerOne)
		f->render(gr, (SCREEN_WIDTH/2)+16, y, valueString);
	else
		f->render(gr, (SCREEN_WIDTH/2)-16-f->textWidth(valueString), y, valueString);
}
void StatisticsScreen::renderColumn2(Graphics* gr, HeroValues* hv, int y, Font* f, const char* pointsString)
{
	int pointsDx = 24;
	if(!hv->isPlayerOne)
		f->render(gr, SCREEN_WIDTH-pointsDx-f->textWidth(pointsString), y, pointsString);
	else
		f->render(gr, 64+pointsDx-f->textWidth(pointsString), y, pointsString);
}
bool StatisticsScreen::incrementValue(HeroValues* hv, int index)
{
	if(hv != null)
		return hv->increment(index);
	return false;
}
