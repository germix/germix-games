////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RankingScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/RankingScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/ranking/Ranking.h>

#include <mach/Math.h>
#include <mach/Color.h>
#include <mach/Graphics.h>
#include <mach/Texture.h>
#include <mach/TextureLoader.h>
#include <mach/Keyboard.h>

#include <gamelib/Font.h>

#include <string.h>

#define TIME_LISTING		0.09
#define TIME_STARTING		0.02

RankingScreen::RankingScreen()
: state(STATE_STARTING)
, clock(TIME_STARTING)
, removable(false)
, texture(null)
, textureWidth(0)
, textureHeight(0)
, drawValue(0)
, halfWidth(0)
, font1(null)
, font2(null)
, currentUser(0)
, rankingRecords(null)
, rankingRecordsCount(0)
{
}
RankingScreen::~RankingScreen()
{
	delete texture;
}
Screen* RankingScreen::getNext()
{
	return null;
}
bool    RankingScreen::isRemovable()
{
	return removable;
}
void    RankingScreen::show(Machine* mach)
{
	texture = TextureLoader::load("mslug/screens/ranking/Ranking1.png");
	textureWidth = texture->getWidth();
	textureHeight = texture->getHeight();
	halfWidth = textureWidth/2;
	
	font1 = res.findFont("Font.8x8.1");
	font2 = res.findFont("Font.16x16.1");
	
	// Load ranking scores
#if 0
	rankingRecords.push_back(new RankingRecord("Adrian", "01/01/2000", 100000));
	rankingRecords.push_back(new RankingRecord("Alberto", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Antonio", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Carlos", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Dario", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Esteban", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Franco", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Gastom", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Gerardo", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("German", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Jose", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Juan", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Leonel", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Luis", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Marcelo", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Mario", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Miguel", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Oscar", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Pablo", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Pedro", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Ricardo", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Roberto", "01/01/2000", 10));
	rankingRecords.push_back(new RankingRecord("Walter", "01/01/2000", 10));
#else
	rankingRecords = Ranking("mslug-ranking.xml").getRecords();
#endif
	rankingRecordsCount = Math::min(20, (int)rankingRecords.size());
}
void    RankingScreen::hide(Machine* mach)
{
}
void    RankingScreen::update(Machine* mach, double dt)
{
	switch(state)
	{
		case STATE_STARTING:
			if(clock.update(dt))
			{
				drawValue += 2;
				if(drawValue > halfWidth)
				{
					drawValue = halfWidth;
					state = STATE_LISTING;
					clock.reset(TIME_LISTING);
				}
			}
			break;
		case STATE_LISTING:
			if(clock.update(dt))
			{
				if(++currentUser >= rankingRecordsCount)
				{
					currentUser = rankingRecordsCount;
					state = STATE_NOTHING;
				}
			}
			break;
		case STATE_NOTHING:
			if(Keyboard::isPressed(Key::ESCAPE))
			{
				removable = true;
			}
			break;
	}
}
void    RankingScreen::render(Machine* mach, Graphics* gr)
{
	if(state == STATE_STARTING)
	{
		gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color());
	}
	gr->drawTexture(
			texture,

			0, 0,
			textureWidth,
			textureHeight,
			
			halfWidth-drawValue,
			0,
			halfWidth+drawValue,
			textureHeight);
	
	if(state != STATE_STARTING)
	{
		const char* title = "TOP TEN";
		int         wTitle = font2->textWidth(title);
		
		font2->render(gr, halfWidth - wTitle/2, 8-4, title);
		
		int y = 32-8;
		for(int i = 0; i < currentUser; i++)
		{
			char text[128];
			const RankingRecord& record = rankingRecords[i];
#if 0
			sprintf(text, " %2d  %8d%12s",
					i+1,
					record.score,
					record.name);
#else

//			sprintf(text, " %2d  %8d%12s   %s",
			sprintf(text, " %2d  %8d%12s  %s ",
					i+1,
					record.score,
					record.name,
					record.date);
#endif
			font1->render(gr, 0, y, text);
			
			y += 10;
		}
	}
}

