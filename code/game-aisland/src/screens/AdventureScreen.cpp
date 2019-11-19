////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AdventureScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/AdventureScreen.h>
#include <src/Scene.h>
#include <src/HeroInfo.h>
#include <src/entities/hero/Hero.h>
#include <src/screens/InitRoundScreen.h>
#include <src/screens/WinnerScreen.h>
#include <src/screens/GameOverScreen.h>
#include <src/screens/RoundBonusScreen.h>

#include <src/Config.h>
#include <src/ResourceManager.h>

#include <mach/Mixer.h>
#include <mach/Texture.h>
#include <mach/Keyboard.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>

AdventureScreen::AdventureScreen()
: area(1)
, round(1)
, scene(null)
, removable(false)
, paused(false)
, needLoadScene(false)
{
	nextScreens.push(new InitRoundScreen(area, round, &info));

	pausedFont = res.findFont("Font.1");
	pausedBackground = res.findTexture("Pause");
}
AdventureScreen::~AdventureScreen()
{
	delete scene;
}
Screen* AdventureScreen::getNext()
{
	if(!nextScreens.empty())
	{
		Screen* ns = nextScreens.front();
		nextScreens.pop();
		return ns;
	}
	return null;
}
bool    AdventureScreen::isRemovable()
{
	return removable;
}
void    AdventureScreen::show(Machine* mach)
{
	if(!scene)
	{
		scene = new Scene(info, area, round);
	}
	else if(needLoadScene)
	{
		needLoadScene = false;
		scene->loadScene(area, round);
	}
}
void    AdventureScreen::hide(Machine* mach)
{
}
void    AdventureScreen::update(Machine* mach, double dt)
{
	if(!nextScreens.empty())
		return;
	if(Keyboard::isPressed(Key::ESCAPE))
	{
#if 0
		removable = true;
		return;
#else
		paused = !paused;
		if(paused)
			Mixer::pause();
		else
			Mixer::resume();
#endif
	}
	if(paused)
	{
		if(Keyboard::isPressed(Key::RETURN))
		{
			removable = true;
		}
		return;
	}
	scene->update(dt);

	if(scene->isFinished())
	{
		if(scene->isCompleted())
		{
			if(++round == 5)
			{
	#if 0
				area++;
				round = 1;
				if(area == 9)
				{
				}
	#endif
				nextScreens.push(new WinnerScreen());
				removable = true;
			}
			else
			{
				needLoadScene = true;
				nextScreens.push(new RoundBonusScreen(&info));
				nextScreens.push(new InitRoundScreen(area, round, &info));
			}
		}
		else
		{
			if(--info.lives == 0)
			{
				nextScreens.push(new GameOverScreen(area, round, info.score));
				removable = true;
			}
			else
			{
				scene->restart();
				nextScreens.push(new InitRoundScreen(area, round, &info));
			}
		}
	}
}
void    AdventureScreen::render(Machine* mach, Graphics* gr)
{
	//if(scene->isPlaying())
	{
		scene->render(gr);
	}
	if(paused)
	{
		gr->drawTexture(
			pausedBackground,
			(SCREEN_WIDTH-pausedBackground->getWidth())/2,
			(SCREEN_HEIGHT-pausedBackground->getHeight())/2,
			150);
		
		pausedFont->render
		(
			gr,
			SCREEN_WIDTH/2 - pausedFont->textWidth("* PAUSA *")/2,
			SCREEN_HEIGHT/2,
			"* PAUSA *"
		);
	}
}
