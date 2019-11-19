////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroSelectionScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/HeroSelectionScreen.h>
#include <src/Config.h>
#include <src/screens/PlayingMissionScreen.h>

#include <mach/Mixer.h>
#include <mach/Color.h>
#include <mach/Graphics.h>
#include <mach/Keyboard.h>
#include <mach/Texture.h>
#include <mach/TextureLoader.h>

#include <string>
#include <tinyxml2/tinyxml2.h>

using namespace tinyxml2;

class HeroProfile
{
public:
	std::string		name;
	Texture*		face;
	Texture*		title;
	Sound*			sound;
	std::string		spriteSheet;
public:
	HeroProfile() : face(0), title(0), sound(0)
	{
	}
	~HeroProfile()
	{
		if(face)
			delete face;
		if(title)
			delete title;
		if(sound)
			Mixer::freeSound(sound);
	}
};

#define MAX_CURSOR_FRAMES			11

#define FACE_IMAGE_WIDTH			48
#define FACE_IMAGE_HEIGHT			64

#define ANIMATION_TIME_FADE			0.07
#define ANIMATION_TIME_CURSOR		0.05

HeroSelectionScreen::HeroSelectionScreen()
: state(STATE_FADE_IN)
, removable(false)
, nextScreen(null)
, bar(null)
, bricks(null)
, background(null)
, cursorClock(ANIMATION_TIME_CURSOR)
, cursorFrame(0)
, cursorTexture(null)
, currentHero(0)
, selectionSound(null)
, selectionSoundChannel(-1)
, heroes()
, fadeValue(255)
, fadeClock(ANIMATION_TIME_FADE)
, selectedHeroSoundChannel(-1)
{
}
HeroSelectionScreen::~HeroSelectionScreen()
{
}
Screen* HeroSelectionScreen::getNext()
{
	return nextScreen;
}
bool    HeroSelectionScreen::isRemovable()
{
	return removable;
}
void    HeroSelectionScreen::show(Machine* mach)
{
	bar = TextureLoader::load("mslug/screens/selection/HeroSelect-Bar1.png");
	bricks = TextureLoader::load("mslug/screens/selection/HeroSelect-Bricks2.png");
	background = TextureLoader::load("mslug/screens/selection/HeroSelect-Background.png");
	
	cursorTexture = TextureLoader::load("mslug/screens/selection/HeroSelect-Arrow.png");
	selectionSound = Mixer::loadSound("mslug/screens/selection/HeroSelect.ogg");

	//
	// Cargar heroes
	//
	XMLDocument  doc;
	XMLElement*  elem;
	std::string  base;
	HeroProfile* hero;
	const char*  value;
	
	if(XML_SUCCESS == doc.LoadFile("mslug/heroes/Heroes.xml"))
	{
		if(null != (elem = doc.FirstChildElement("Heroes")))
		{
			base = "mslug/heroes";
			for(elem = elem->FirstChildElement("Hero"); elem != null; elem = elem->NextSiblingElement())
			{
				hero = new HeroProfile();
				
				elem->QueryStringAttribute("name", &value);
				hero->name = value;
				elem->QueryStringAttribute("face", &value);
				hero->face = TextureLoader::load((base + value).c_str());
				elem->QueryStringAttribute("title", &value);
				hero->title = TextureLoader::load((base + value).c_str());
				elem->QueryStringAttribute("sound", &value);
				hero->sound = Mixer::loadSound((base + value).c_str());
				elem->QueryStringAttribute("spriteSheet", &value);
				hero->spriteSheet = (base + value).c_str();
				
				heroes.push_back(hero);
			}
		}
	}
}
void    HeroSelectionScreen::hide(Machine* mach)
{
	delete bar;
	delete bricks;
	delete background;
	delete cursorTexture;
	Mixer::freeSound(selectionSound);
	
	for(unsigned int i = 0; i < heroes.size(); i++)
	{
		delete heroes[i];
	}
	heroes.clear();
}
void    HeroSelectionScreen::update(Machine* mach, double dt)
{
	switch(state)
	{
		case STATE_FADE_IN:
			if(fadeClock.update(dt))
			{
				fadeValue -= 20;
				if(fadeValue < 0)
				{
					state = STATE_IDLE;
					fadeValue = 0;
				}
			}
			break;
		case STATE_IDLE:
			if(Keyboard::isPressed(Key::ESCAPE))
			{
				removable = true;
			}
			else if(Keyboard::isPressed(Key::LEFT))
			{
				if(currentHero > 0)
				{
					currentHero--;
					cursorClock.reset();
					cursorFrame = 0;
					
					Mixer::haltChannel(selectionSoundChannel);
					selectionSoundChannel = Mixer::playChannel(selectionSound);
				}
			}
			else if(Keyboard::isPressed(Key::RIGHT))
			{
				if(currentHero < heroes.size()-1)
				{
					currentHero++;
					cursorClock.reset();
					cursorFrame = 0;
					
					Mixer::haltChannel(selectionSoundChannel);
					selectionSoundChannel = Mixer::playChannel(selectionSound);
				}
			}
			else if(Keyboard::isPressed(Key::RETURN) || Keyboard::isPressed(Key::KP_ENTER))
			{
				state = STATE_FADE_OUT;
				selectedHeroSoundChannel = Mixer::playChannel(heroes[currentHero]->sound);
			}
			break;
		case STATE_FADE_OUT:
			if(fadeClock.update(dt))
			{
				fadeValue += 20;
				if(fadeValue >= 255)
				{
					state = STATE_NOTHING;
					fadeValue = 255;
				}
			}
			break;
		case STATE_NOTHING:
			if(!Mixer::isPlayingChannel(selectedHeroSoundChannel))
			{
				removable = true;
				nextScreen = new PlayingMissionScreen(heroes[currentHero]->name.c_str(), "msxm1");
			}
			break;
	}
	if(cursorClock.update(dt))
	{
		cursorFrame++;
		if(cursorFrame >= MAX_CURSOR_FRAMES)
			cursorFrame = 0;
	}
}
void    HeroSelectionScreen::render(Machine* mach, Graphics* gr)
{
	gr->drawTexture(background, 0, 0);
	
	if(!heroes.empty())
	{
		//
		// Dibujar heroes
		//
		int frameY = 32+16+8+8;
		int frameWidth = SCREEN_WIDTH/heroes.size();
		
		for(unsigned int i = 0; i < heroes.size(); i++)
		{
			int frameX = i*frameWidth;
			int imageX;
			int imageY;
			
			//
			// Dibujar ladrillos
			//
			imageY = frameY;
			imageX = frameX+(frameWidth/2)-bricks->getWidth()/2;
			gr->drawTexture(bricks, imageX, imageY);
			
			//
			// Dibujar héroe
			//
			HeroProfile* hero = heroes[i];
			
			imageY = frameY+8;
			imageX = frameX+((frameWidth/2)-FACE_IMAGE_WIDTH/2);
			
			if(i == currentHero)
			{
				gr->drawTexture
				(
					hero->face,
					
					FACE_IMAGE_WIDTH*1,
					0,
					FACE_IMAGE_WIDTH*2,
					FACE_IMAGE_HEIGHT,
					
					imageX,
					imageY,
					imageX+FACE_IMAGE_WIDTH,
					imageY+FACE_IMAGE_HEIGHT
				);
				
				//
				// Dibujar barra de selección
				//
				gr->drawTexture(bar, SCREEN_WIDTH/2-bar->getWidth()/2, 192);
				gr->drawTexture(hero->title, SCREEN_WIDTH/2-hero->title->getWidth()/2, 192+4);
			}
			else
			{
				gr->drawTexture
				(
					hero->face,
					
					FACE_IMAGE_WIDTH*0,
					0,
					FACE_IMAGE_WIDTH*1,
					FACE_IMAGE_HEIGHT,

					imageX,
					imageY,
					imageX+FACE_IMAGE_WIDTH,
					imageY+FACE_IMAGE_HEIGHT
				);
			}
		}
		//
		// Dibujar cursor de selección
		//
		int curX = ((currentHero*frameWidth)+frameWidth/2) - 8;
		int curY = (frameY+FACE_IMAGE_HEIGHT+12);
		int curWidth = cursorTexture->getWidth() / MAX_CURSOR_FRAMES;
		int curHeight = cursorTexture->getHeight();
		gr->drawTexture
		(
			cursorTexture,
			
			(cursorFrame*curWidth),
			0,
			(cursorFrame*curWidth) + curWidth,
			curHeight,
			
			curX,
			curY,
			curX+curWidth,
			curY+curHeight);
	}
	if(state != STATE_IDLE)
	{
		gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0, 0, 0, fadeValue));
	}
}
