////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MissionCompleted
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/MissionCompleted.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/entities/hero/Hero.h>

#include <mach/Random.h>
#include <mach/Mixer.h>
#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>
#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#include <set>

static const char* HOSTAGES_RANKS[] = // https://www.military-ranks.org/army
{
	"PVT",		// Private
	"PFC",		// Private First Class
	"SPC",		// Specialist
	"CPL",		// Corporal
	"SGT",		// Sergeant
	"SSG",		// Staff Sergeant
	"SFC",		// Sergeant First Class
	"MSG",		// Master Sergeant
	"1SG",		// First Sergeant
	"SGM",		// Sergeant Major
	"CSM",		// Command Sergeant Major
	"SMA",		// Sergeant Major of the Army
	// ---
	"WO1",		// Warrant Officer 1
	"CW2",		// Chief Warrant Officer 2
	"CW3",		// Chief Warrant Officer 3
	"CW4",		// Chief Warrant Officer 4
	"CW5",		// Chief Warrant Officer 5
	"2LT",		// Second Lieutenant
	"1LT",		// First Lieutenant
	"CPT",		// Captain
	"MAJ",		// Major
	"LTC",		// Lieutenant Colonel
	"COL",		// Colonel
	" BG",		// Brigadier General
	" MG",		// Major General
	"LTG",		// Lieutenant General
	"GEN",		// General
	" GA",		// General of the Army
};
static const char* HOSTAGES_NAMES[] =
{
	"Warner",
	"Griogorovich",
	"Valcan",
	"Cronos",
	"Hamachan",
	"Van",
	"Siegfried",
	"Hsiung",
	"Cotton",
	"Eugen",
	"Carnegie",
	"Ehrlich",
	"Jason",
	"Jong",
	"Schwarz",
	"Pippolytus",
	"Kalinin",
	"Silvanus",
	"Garfield",
	"Araki",
	"Yagami",
	"Palamedes",
	"Hyachinth",
	"Deianira",
	"Godai",
	"Winckler",
	"Icarus",
	"Sullivan",
	"Akimoto",
	"Oceanides",
	"Zamchevsky",
	"Fahrenheit",
	"Tanaka",
	"Georgie",
	"Leumann",
	"Griffis",
	"Neisebach",
	"Kujirai",
	"Tokugawa",
	"Kozlov",
	"Okui",
	"Meleager",
	"Simpson",
	"Eichendorff",
	"Sato",
	"James",
	"Orikasa",
	"Ninomiya",
	"Jefferson",
	"Strowberry",
	"Sawai",
	"Cassell",
	"Boltec",
	"Takahara",
	"Sanger",
	"Yamada",
	"Koiso",
	"Konev",
	"Tennoh",
	"Borodin",
	"Melpomene",
	"Neoptolemus",
	"Adams",
	"Lancelot",
	"Eliot",
	"Keenan",
	"Morikawa",
	"Faraday",
	"Diogenes",
	"Hatoyama",
	"Rokuta",
	"Philemon",
	"Daff",
	"Hattori",
	"Williams",
	"Namihira",
};

#define MAX_HOSTAGES_NAMES		(sizeof(HOSTAGES_NAMES)/sizeof(HOSTAGES_NAMES[0]))
#define MAX_HOSTAGES_RANKS		(sizeof(HOSTAGES_RANKS)/sizeof(HOSTAGES_RANKS[0]))

#define TIME_FADE				0.001
#define TIME_SALUTE				0.06
#define TIME_LAST_HOSTAGE		0.35
#define TIME_WAIT_FOR_FINISHED	1.8

MissionCompleted::MissionCompleted()
: state(STATE_FADE_1)
, finished(false)
, activated(false)
, font1(null)
, font2(null)
, font3(null)
, font4(null)
, font5(null)
, borders(null)

, fadeAlpha(0)
, fadeClock(TIME_FADE)

, salute(null)
, saluteFrame(0)
, saluteClock(TIME_SALUTE)

, hostagesCount(0)
, hostagesNames()
, hostagesRanks()
, lastHostageName(-1)
, lastHostageClock(TIME_LAST_HOSTAGE)
, noPrisionesBlink(0)
, noPrisionesBlinkCount(0)

, hero(0)
, waitForFinishedClock(TIME_WAIT_FOR_FINISHED)
{
}
MissionCompleted::~MissionCompleted()
{
}
void MissionCompleted::update(double dt)
{
	switch(state)
	{
		case STATE_FADE_1:
			if(fadeClock.update(dt))
			{
				fadeAlpha += 2;
				if(fadeAlpha >= 120)
				{
					fadeAlpha = 120;
					state = STATE_HOSTAGES;
				}
			}
			break;
		case STATE_HOSTAGES:
			if(saluteFrame < 9)
			{
				if(saluteClock.update(dt))
				{
					if(++saluteFrame >= 9)
					{
						saluteFrame = 9;
					}
				}
			}
			if(hostagesCount == 0)
			{
				if(lastHostageClock.update(dt))
				{
					noPrisionesBlink = (++noPrisionesBlink)&1;
					noPrisionesBlinkCount++;
					if(noPrisionesBlinkCount == 10)
					{
						state = STATE_FADE_2;
					}
				}
			}
			else
			{
				if(lastHostageName < hostagesCount-1)
				{
					if(lastHostageClock.update(dt))
					{
						lastHostageName++;
						if(hero)
						{
							hero->addScore(10000);
						}
					}
				}
				else
				{
					if(waitForFinishedClock.update(dt))
					{
						state = STATE_FADE_2;
					}
				}
			}
			break;
		case STATE_FADE_2:
			if(fadeClock.update(dt))
			{
				fadeAlpha -= 4;
				if(fadeAlpha <= 0)
				{
					fadeAlpha = 0;
					state = STATE_MISSION_COMPLETED;
					Mixer::playChannel(res.findSound("MissionCompleted"));
				}
			}
			break;
		case STATE_MISSION_COMPLETED:
			if(waitForFinishedClock.update(dt))
			{
				hero = null;
				finished = true;
				activated = false;
			}
			break;
	}
}
void MissionCompleted::render(Graphics* gr)
{
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0, 0, 0, fadeAlpha));
	switch(state)
	{
		case STATE_HOSTAGES:
			{
				int baseX = 16;
				int baseY = 48;
				
				int x = baseX;
				int y = baseY;
				int width = 17;
				int height = 19;
				
				//
				// Dibujar esquinas
				//
				borders->render(gr, x, y, (char)0);
				borders->render(gr, x + (width*8), y, (char)1);
				borders->render(gr, x, y + (height*8), (char)2);
				borders->render(gr, x + (width*8), y + (height*8), (char)3);
				
				//
				// Dibujar líneas verticales
				//
				for(int i = 1; i < height; i++)
				{
					borders->render(gr, x, y + (i*8), (char)6);
					borders->render(gr, x + (width*8), y + (i*8), (char)7);
				}
				//
				// Dibujar líneas horizontales
				//
				for(int i = 1; i < width; i++)
				{
					borders->render(gr, x + (i*8), y, (char)5);
					borders->render(gr, x + (i*8), y + (height*8), (char)4);
				}
				//
				// Dibujar línea central
				//
				borders->render(gr, x + (1*8), y + (11*8), (char)8);
				for(int i = 2; i < width-1; i++)
				{
					borders->render(gr, x + (i*8), y + (11*8), (char)9);
				}
				borders->render(gr, x + ((width-1)*8), y + (11*8), (char)10);
				
				//
				// Saludo del rehén
				//
				salute->render(gr, 39, 96, saluteFrame, Sprite::FLIP_X);
				
				//
				// Dibujar lista de nombres
				//
				x = x + (1*8);
				y = y + (12*8);
				int startLine = 0;
				int visibleLines = 7-1;
				if(lastHostageName >= visibleLines)
				{
					startLine = (lastHostageName-visibleLines);
				}
				for(int i = startLine; i <= lastHostageName; i++)
				{
					char text[20];
					char* p = text;
					const char* rank = HOSTAGES_RANKS[hostagesRanks[i]];
					const char* name = HOSTAGES_NAMES[hostagesNames[i]];
					
					while(*rank)
						*p++ = *rank++;
					*p++ = '.';
					while(*name)
						*p++ = *name++;
					*p++ = '\0';
					
					font1->render(gr, x, y + ((i-startLine)*8), text);
				}
				//
				// Dibujar puntaje por rehénes
				//
				font4->render(gr, 72, 56, "1P");
				if(hostagesCount == 0)
				{
					if(noPrisionesBlink == 1)
					{
						font3->render(gr, 40, 120, "NO PRIOSIONER");
					}
				}
				else if(lastHostageName != -1)
				{
					char text[8];
					sprintf(text, "%02d", lastHostageName+1);
					int    wText = font4->textWidth(text);
					
					font4->render(gr, 64, 80, text);
					font2->render(gr, 96, 88, (char)132);
					font2->render(gr, 104, 88, "10000");
					
					sprintf(text, "%d", (lastHostageName+1)*10000);
					wText = font4->textWidth(text);
					font4->render(gr, 144 - wText, 104, text);
				}
			}
			break;
		case STATE_MISSION_COMPLETED:
			font5->render(gr, 60, 60, "MISSION");
			font5->render(gr, 46, 108, "COMPLETE[");
			break;
	}
}
void MissionCompleted::clear()
{
	hostagesNames.clear();
	hostagesRanks.clear();
}
void MissionCompleted::activate(Hero* h, int hc)
{
	if(!activated)
	{
		if(!font1)
		{
			font1 = res.findFont("Font.8x8.1");
			font2 = res.findFont("Font.8x8.3");
			font3 = res.findFont("Font.8x16.3");
			font4 = res.findFont("Font.16x16.3");
			font5 = res.findFont("Font.25x25");
			borders = res.findFont("Font.Borders");
			// ...
			salute = res.findSpriteSheet("Hostage")->getSprite("Salute");
		}
		state = STATE_FADE_1;
		finished = false;
		activated = true;
		fadeAlpha = 0;
		fadeClock.reset(TIME_FADE);
		saluteFrame = 0;
		saluteClock.reset(TIME_SALUTE);
		hostagesCount = hc;
		hostagesNames.clear();
		hostagesRanks.clear();
		lastHostageName = -1;
		lastHostageClock.reset(TIME_LAST_HOSTAGE);
		noPrisionesBlink = 0;
		noPrisionesBlinkCount = 0;
		hero = h;
		waitForFinishedClock.reset(STATE_WAIT_FOR_FINISHED);
		
		// ...
		std::set<int> set;
		Random rand;
		
		//
		// Nombres aleatorios
		//
		while(set.size() < hostagesCount)
		{
			set.insert(rand.nextInt(MAX_HOSTAGES_NAMES-1));
		}
		hostagesNames.clear();
		for(std::set<int>::const_iterator it = set.begin(); it != set.end(); it++)
		{
			hostagesNames.push_back(*it);
		}
		//
		// Rangos aleatorios
		//
		hostagesRanks.clear();
		for(unsigned int i = 0; i < hostagesCount; i++)
		{
			hostagesRanks.push_back(rand.nextInt(MAX_HOSTAGES_RANKS-1));
		}
	}
}


