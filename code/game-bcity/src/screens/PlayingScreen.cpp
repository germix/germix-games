////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlayingScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/PlayingScreen.h>
#include <src/Config.h>
#include <src/base/Sprite.h>
#include <src/res/ResourceManager.h>
#include <src/Scene.h>
#include <src/stages/StagesProvider.h>
#include <src/entities/Bird.h>
#include <src/entities/tanks/HeroTank.h>
#include <src/screens/AllOverScreen.h>
#include <src/screens/GameOverScreen.h>
#include <src/screens/StatisticsScreen.h>

#include <vector>

#include <mach/Mixer.h>
#include <mach/Texture.h>
#include <mach/Graphics.h>

#include <tmx/TmxMap.h>
#include <tmx/TmxObject.h>
#include <tmx/layers/TmxObjectLayer.h>

#include <gamelib/Font.h>

#include <mach/Mouse.h>
#include <mach/Keyboard.h>
#include <src/entities/bonus/BonusClock.h>
#include <src/entities/bonus/BonusGrenade.h>
#include <src/entities/bonus/BonusHelmet.h>
#include <src/entities/bonus/BonusShovel.h>
#include <src/entities/bonus/BonusStar.h>
#include <src/entities/bonus/BonusTank.h>

PlayingScreen::PlayingScreen(StagesProvider* provider, Player* ___player1, Player* ___player2)
: state(STATE_LOAD)
, removable(false)
, map(null)
, scene(null)
, hero1(null)
, player1(___player1)
, hero2(null)
, player2(___player2)
, stage(0)
, stages(provider)
, nextScreen(null)
, openingClock(0.006)
, openingHeight(SCREEN_HEIGHT/2)
, tryExit(false)
{
	if(player1)
		player1->reset();
	if(player2)
		player2->reset();

	scene = new Scene();

	fontBlack = res.findFont("Font.Black");
	texturePauseTitle = res.findTexture("Pause");
	texturePauseBackground = res.findTexture("PauseBackground");
	textureGameOver = res.findTexture("GameOver");
	textureStageIndicator = res.findTexture("StageIndicator");
	texturePlayerIndicator1 = res.findTexture("PlayerIndicator1");
	texturePlayerIndicator2 = res.findTexture("PlayerIndicator2");

	introStage = res.findSound("IntroStage");
	introStageChannel = -1;
}
PlayingScreen::~PlayingScreen()
{
	printf("~PlayingScreen()\n");
}
Screen* PlayingScreen::getNext()
{
	Screen* s = nextScreen;
	nextScreen = null;
	return s;
}
bool    PlayingScreen::isRemovable()
{
	return removable;
}
void    PlayingScreen::show(Machine* mach)
{
	loadStage();
}
void    PlayingScreen::hide(Machine* mach)
{
}
void    PlayingScreen::update(Machine* mach, double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		tryExit = !tryExit;
		if(tryExit)
		{
			Mixer::pause();
		}
		else
		{
			Mixer::resume();
		}
	}
	if(Keyboard::isPressed(Key::RETURN))
	{
		if(tryExit)
		{
			removable = true;
			Mixer::halt();
		}
	}
	if(tryExit || removable)
	{
		return;
	}
	if(introStageChannel != -1 && !Mixer::isPlayingChannel(introStageChannel))
	{
		introStageChannel = -1;
		Mixer::playMusic(res.findMusic("Background"), -1);
	}
	switch(state)
	{
		case STATE_LOAD:
			break;
		case STATE_OPENING:
			if(openingClock.update(dt))
			{
				if(--openingHeight == 0)
				{
					state = STATE_PLAYING;
				}
			}
			break;
		case STATE_CLOSING:
			if(openingClock.update(dt))
			{
				if(++openingHeight >= SCREEN_HEIGHT/2)
				{
					if(scene->isGameOver())
					{
						removable = true;
						nextScreen = new GameOverScreen();
					}
					else if(stages != null && stages->hasStage())
					{
						state = STATE_LOAD;
					}
					else
					{
						removable = true;
						nextScreen = new AllOverScreen();
					}
					char sz[32];
					
					sprintf(sz, "%d", stage);
					
					nextScreen = new StatisticsScreen(
						sz,
						player1,
						hero1 != null ? hero1->getVictims() : null,
						!scene->isGameOver() && (hero1 != null && hero1->isAlive()),
						player2,
						hero2 != null ? hero2->getVictims() : null,
						!scene->isGameOver() && (hero2 != null && hero2->isAlive()));
				}
			}
			break;
		case STATE_PLAYING:
			scene->update(dt);
			if(scene->isGameOver() || scene->isLevelCompleted())
			{
				state = STATE_FADING_OUT_SOUND;
				Mixer::halt(600);

				if(scene->isGameOver())
				{
					gameOverY = SCREEN_HEIGHT;
				}
			}
			break;
		case STATE_FADING_OUT_SOUND:
			scene->update(dt);
			if(scene->isGameOver())
			{
				gameOverY -= dt*100;
				if(gameOverY <= (SCREEN_HEIGHT/2)+1)
				{
					gameOverY = (SCREEN_HEIGHT/2)+1;
					state = STATE_CLOSING;
				}
			}
			else
			{
				if(!Mixer::isFadingOut())
				{
					state = STATE_CLOSING;
				}
			}
			break;
	}
	if(Debug::spawnBonusByMouse)
	{
		if(Keyboard::isPressed(Key::TAB))
		{
			Config::currentBonus++;
			if(Config::currentBonus > 5) Config::currentBonus = 0;
		}
		if(Mouse::isButtonPressed(MouseButton_Left))
		{
			int x = Mouse::getX()-MAP_X;
			int y = Mouse::getY()-MAP_Y;
			if(x >= 0 && y >= 0 && x < MAP_WIDTH-16 && y < MAP_HEIGHT-16)
			{
				switch(Config::currentBonus)
				{
					case 0: scene->addEntity(new BonusClock(map, scene, x, y)); break;
					case 1: scene->addEntity(new BonusGrenade(map, scene, x, y)); break;
					case 2: scene->addEntity(new BonusHelmet(map, scene, x, y)); break;
					case 3: scene->addEntity(new BonusShovel(map, scene, x, y)); break;
					case 4: scene->addEntity(new BonusStar(map, scene, x, y)); break;
					case 5: scene->addEntity(new BonusTank(map, scene, x, y)); break;
				}
			}
		}
	}
}
void    PlayingScreen::render(Machine* mach, Graphics* gr)
{
	Color grayColor(128,128,128);
	
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, grayColor);
	
	//
	// Dibujar mapa y escenario
	//
	gr->translate(MAP_X, MAP_Y);
	
	scene->render(gr);
	
	gr->translate(-MAP_X, -MAP_Y);
	
	{
		int tx = MAP_X+MAP_WIDTH;
		int ty = MAP_Y;

		//
		// Dibujar el conjunto de enemigos
		//
		drawEnemySet(gr, tx+8, ty+8);
		
		//
		// Dibujar indicador de nivel
		//
		drawStageIndicator(gr, tx+8, ty+168);
		
		//
		// Dibujar indicadores de jugador
		//
		drawPlayerIndicator(gr, tx+8, ty+120, hero1, texturePlayerIndicator1);
		drawPlayerIndicator(gr, tx+8, ty+144, hero2, texturePlayerIndicator2);
		
		//
		// Dibujar puntajes de jugados
		//
		tx = MAP_X;
		ty = MAP_Y+MAP_HEIGHT;
		drawPlayerScore(gr, tx+80, ty, hero1, true);
		drawPlayerScore(gr, tx+128, ty, hero2, false);
	}
	if(scene->isGameOver())
	{
		gr->drawTexture(textureGameOver, SCREEN_WIDTH/2 - textureGameOver->getWidth()/2, gameOverY);
	}
	if(state == STATE_OPENING || state == STATE_CLOSING)// || state == STATE_ALL_OVER)
	{
		gr->fillRect(0, 0, SCREEN_WIDTH, openingHeight, grayColor);
		gr->fillRect(0, SCREEN_HEIGHT-openingHeight, SCREEN_WIDTH, openingHeight, grayColor);
	}

	if(tryExit)
	{
		int y1 = (SCREEN_HEIGHT/2)-16;
		int y2 = (SCREEN_HEIGHT/2)+16;

		gr->drawTexture(texturePauseBackground,
			SCREEN_WIDTH/2 - texturePauseBackground->getWidth()/2,
			SCREEN_HEIGHT/2 - texturePauseBackground->getHeight()/2);

		gr->drawTexture(texturePauseTitle,
			SCREEN_WIDTH/2 - texturePauseTitle->getWidth()/2,
			SCREEN_HEIGHT/2 - texturePauseTitle->getHeight()/2);

	}
}
void PlayingScreen::loadStage()
{
	TmxMap* tmx = stages->getStage();
	if(!tmx)
	{
		removable = true;
		return;
	}
	map = scene->load(tmx);
	
	//
	// Cargar objectos
	//
	TmxObject* obj;
	std::vector<TmxObject*> objs = tmx->getObjectLayer("objects")->getObjects();
	
	for(unsigned int i = 0; i < objs.size(); i++)
	{
		obj = objs[i];
		
		if(obj->getType() == "bird")
		{
			scene->addEntity(new Bird(map, scene, obj->getX(), obj->getY()));
		}
		else if(obj->getType() == "player1")
		{
			if(player1 != null)
			{
				scene->addEntity(hero1 = new HeroTank(player1, map, scene, obj->getX(), obj->getY(), Tank::TANK_COLOR_BROWN));
			}
		}
		else if(obj->getType() == "player2")
		{
			if(player2 != null)
			{
				scene->addEntity(hero2 = new HeroTank(player2, map, scene, obj->getX(), obj->getY(), Tank::TANK_COLOR_GREEN));
			}
		}
	}
	delete tmx;

	// ...
	stage++;
	state = STATE_OPENING;

	introStageChannel = Mixer::playChannel(introStage);
}
void PlayingScreen::drawEnemySet(Graphics* gr, int x, int y)
{
	for(int i = 0; i < scene->getEnemyCount(); i++)
	{
		if(i != 0 && (i&1) == 0)
			y += 8;
		Config::tanksIndicator->render(gr, x+(i&1)*8, y, 0);
	}
}
void PlayingScreen::drawStageIndicator(Graphics* gr, int x, int y)
{
	char sz[16];
	
	gr->drawTexture(textureStageIndicator, x, y);
	
	sprintf(sz, "%d", stage);
	if(stage >= 10)
		fontBlack->render(gr, x, y+16, sz);
	else
		fontBlack->render(gr, x+8, y+16, sz);
}
void PlayingScreen::drawPlayerScore(Graphics* gr, int x, int y, HeroTank* hero, bool toLeft)
{
	if(hero != null)
	{
		char sz[16];
		
		sprintf(sz, "%d", hero->getScore());
		
		if(!toLeft)
			fontBlack->render(gr, x, y, sz);
		else
			fontBlack->render(gr, x - fontBlack->textWidth(sz), y, sz);
	}
}
void PlayingScreen::drawPlayerIndicator(Graphics* gr, int x, int y, HeroTank* hero, Texture* texture)
{
	if(hero != null)
	{
		char sz[16];
		
		gr->drawTexture(texture, x, y);
		
		sprintf(sz, "%d", hero->getLifes());
		
		if(strlen(sz) > 1)
		{
			fontBlack->render(gr, x, y+8, sz);
		}
		else
		{
			fontBlack->render(gr, x+8, y+8, sz);
			Config::tanksIndicator->render(gr, x, y+8, 1);
		}
	}
}
