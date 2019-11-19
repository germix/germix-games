////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlayingMissionScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/PlayingMissionScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <src/scene/Scene.h>
#include <src/scene/MissionHud.h>
#include <src/entities/hero/Hero.h>
#include <src/Mission.h>

#include <mach/Mixer.h>
#include <mach/Color.h>
#include <mach/Graphics.h>
#include <mach/Keyboard.h>

#include <gamelib/Font.h>
#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#include <src/screens/GameOverScreen.h>
#include <src/screens/EnterNameScreen.h>

PlayingMissionScreen::PlayingMissionScreen(const char* ___heroName, const char* ___sceneName)
: state(STATE_FADE_IN)
, removable(false)
, nextScreen(null)

, fadeValue(255)
, fadeClock(0.01)

, hud(null)
, scene(null)
, mission(null)

, font1(null)
, font2(null)
, font5(null)
, paused(false)
, pausedTexture(null)
{
	heroName = String(___heroName).toLower();
	sceneName += "mslug/scenes/msxm1/";
	sceneName += ___sceneName;
	sceneName += ".xscene";
}
PlayingMissionScreen::~PlayingMissionScreen()
{
}
Screen* PlayingMissionScreen::getNext()
{
	return nextScreen;
}
bool    PlayingMissionScreen::isRemovable()
{
	return removable;
}
void    PlayingMissionScreen::show(Machine* mach)
{
	font1 = res.findFont("Font.8x8.1");
	font2 = res.findFont("Font.8x8.2");
	font5 = res.findFont("Font.25x25");
	
	pausedTexture = res.findTexture("Pause");

	hud = new MissionHud();
	scene = new Scene(Mission().load(sceneName.c_str()), true);
	scene->addEntity(new Hero(scene, 80, 0, heroName.c_str()));
}
void    PlayingMissionScreen::hide(Machine* mach)
{
	delete hud;
	delete scene;
	delete mission;
}
void    PlayingMissionScreen::update(Machine* mach, double dt)
{
	if(dt > 1) dt = 1.0;
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		paused = !paused;
		if(paused)
			Mixer::pause();
		else
			Mixer::resume();
	}
	if(Keyboard::isPressed(Key::RETURN))
	{
		if(paused)
			removable = true;
	}
	if(!paused)
	{
		Hero* hero;
		if(state != STATE_FADE_IN)
		{
			scene->update(dt);
			hud->update(scene, dt);
		}
		switch(state)
		{
			case STATE_FADE_IN:
				if(fadeClock.update(dt))
				{
					fadeValue -= 4;
					if(fadeValue < 0)
					{
						fadeValue = 0;
						state = STATE_PLAY_MISSION;
					}
				}
				break;
			case STATE_PLAY_MISSION:
				if(null != (hero = scene->getHero()))
				{
					if(hero->isLoser())
					{
						state = STATE_HERO_LOSER;
						fadeValue = 0;
					}
					else if(hero->isWinner())
					{
						state = STATE_HERO_WINNER;
						fadeValue = 0;
						missionCompleted.activate(hero, hero->getHostages());
					}
				}
				break;
			case STATE_HERO_LOSER:
				if(fadeClock.update(dt))
				{
					fadeValue += 2;
					if(fadeValue >= 255)
					{
						fadeValue = 255;
						removable = true;
						nextScreen = new GameOverScreen();
					}
				}
				break;
			case STATE_HERO_WINNER:
				missionCompleted.update(dt);
				if(missionCompleted.isFinished())
				{
					state = STATE_EXIT;
					fadeValue = 0;
					fadeClock.reset(0.01);
				}
				break;
			case STATE_EXIT:
				if(fadeValue < 255)
				{
					if(fadeClock.update(dt))
					{
						fadeValue += 4;
						if(fadeValue >= 255)
						{
							fadeValue = 255;
						}
					}
				}
				else
				{
					removable = true;
					if(null != (hero = scene->getHero()))
					{
						nextScreen = new EnterNameScreen(hero->getScore(), hero->getHostages());
					}
				}
				break;
		}
	}
}
void    PlayingMissionScreen::render(Machine* mach, Graphics* gr)
{
	if(fadeValue != 255)
	{
		scene->render(gr);
		hud->render(scene, gr);
	}
	switch(state)
	{
		case STATE_HERO_LOSER:
			if(fadeValue != 0)
			{
				gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(255-fadeValue,0,0,fadeValue));
			}
			break;
		case STATE_HERO_WINNER:
			missionCompleted.render(gr);
			break;
		case STATE_EXIT:
		case STATE_FADE_IN:
			if(fadeValue == 0 || state == STATE_EXIT)
			{
				font5->render(gr, 60, 60, "MISSION");
				font5->render(gr, 46, 108, "COMPLETE[");
			}
			if(fadeValue != 0)
			{
				gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0,0,0,fadeValue));
			}
			break;
	}
	if(paused)
	{
		gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0, 0, 0, 100));
	
		gr->drawTexture(pausedTexture, 30, 30);
		
		int midY = SCREEN_HEIGHT/2;
		const char* text0 = "* PAUSA *";
		const char* text1 = "<ESC> CONTINUAR";
		const char* text2 = "<ENTER> SALIR DEL JUEGO";
		
		int y0 = midY-64;
		int y1 = midY-16;
		int y2 = midY+16;
		int width0 = font2->textWidth(text0);
		int width1 = font1->textWidth(text1);
		int width2 = font1->textWidth(text2);
		
		font2->render(gr, SCREEN_WIDTH/2 - width0/2, y0, text0);
		font1->render(gr, SCREEN_WIDTH/2 - width1/2, y1, text1);
		font1->render(gr, SCREEN_WIDTH/2 - width2/2, y2, text2);
	}
}

