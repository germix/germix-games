////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlayingScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/PlayingScreen.h>
#include <src/Config.h>
#include <src/Scene.h>
#include <src/entities/Pacman.h>
#include <src/resources/ResourceManager.h>

#include <string>
#include <stdlib.h>

#include <mach/Math.h>
#include <mach/Mixer.h>
#include <mach/Keyboard.h>
#include <mach/Color.h>
#include <mach/Texture.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>

PlayingScreen::PlayingScreen(const char* mapName)
: state(STATE_PLAY)
, removable(false)
, nextScreen(null)
, scene(null)
, pacman(null)
, paused(false)
, finished(false)
, font(null)
, textureHeart(null)
, texturePause(null)
, fadeoutAlpha(0)
, fadeoutClock(0.006)
{
	scene = new Scene((std::string("pacman/levels/") + mapName).c_str());
	pacman = scene->getPacman();
	
	font = res.findFont("Font.White");
	textureHeart = res.findTexture("Heart");
	texturePause = res.findTexture("Pause");
}
PlayingScreen::~PlayingScreen()
{
	delete scene;
}
Screen* PlayingScreen::getNext()
{
	return null;
}
bool    PlayingScreen::isRemovable()
{
	return removable;
}
void    PlayingScreen::show(Machine* mach)
{
}
void    PlayingScreen::hide(Machine* mach)
{
}
void    PlayingScreen::update(Machine* mach, double dt)
{
	if(finished)
	{
		if(Keyboard::isPressed(Key::ESCAPE))
		{
			removable = true;
		}
		return;
	}
	switch(state)
	{
		case STATE_PLAY:
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
				scene->update(dt);
				if(pacman->isWinner())
				{
					state = STATE_WINNER;
					Config::maxScore = Math::max(Config::maxScore, pacman->getScore());
				}
				else if(pacman->isGameOver())
				{
					state = STATE_GAMEOVER;
				}
			}
			break;
		case STATE_WINNER:
			if(!finished)
				ballons.update(dt);
		case STATE_GAMEOVER:
			if(!finished)
			{
				if(fadeoutClock.update(dt))
				{
					if(++fadeoutAlpha == 255)
					{
						finished = true;
					}
				}
			}
			break;
	}
}
void    PlayingScreen::render(Machine* mach, Graphics* gr)
{
	char sz[32];
	
	if(finished)
	{
		static char s1[32] = "";
		static char s2[32] = "";
		static const char* texts[] =
		{
			"PUNTAJE",
			s1,		// Score
			"",
			"",
			"PUNTAJE MAXIMO",
			s2,		// Max Score
		};
		gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0, 0, 0));
		
		int listH = 6*font->fontHeight();
		int listY = SCREEN_HEIGHT/2 - listH/2;
		
		itoa(pacman->getScore(), s1, 10);
		itoa(Config::maxScore, s2, 10);
		if(state == STATE_WINNER)
		{
			const char* s = "HAS GANADO!";
			int         x = SCREEN_WIDTH/2 - font->textWidth(s)/2;
			font->render(gr, x, listY-48, s);
		}
		else if(state == STATE_GAMEOVER)
		{
			const char* s = "GAME OVER";
			int         x = SCREEN_WIDTH/2 - font->textWidth(s)/2;
			font->render(gr, x, listY-48, s);
		}
		for(unsigned int i = 0; i < 6; i++, listY += font->fontHeight())
		{
			const char* s = texts[i];
			int         x = SCREEN_WIDTH/2 - font->textWidth(s)/2;
			
			font->render(gr, x, listY, s);
		}
	}
	else
	{
		//
		// Dibujar escena
		//
		scene->render(gr);
		
		gr->fillRect(0, MAP_HEIGHT, SCREEN_WIDTH, 16+8, Color(0,0,0));
		
		//
		// Dibujar puntaje
		//
		sprintf(sz, "Puntaje %d", pacman->getScore());
		font->render(0, 0, MAP_HEIGHT+8, sz);
		
		//
		// Dibujar vidas
		//
		{
			int x = MAP_WIDTH-16;
			int y = MAP_HEIGHT+4;
			for(int i = 0; i < pacman->getLives(); i++, x -= 16)
			{
				gr->drawTexture(textureHeart, x, y);
			}
		}
		if(state == STATE_WINNER)
		{
			ballons.render(gr);
		}

		if(fadeoutAlpha > 0)
		{
			gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0,0,0,fadeoutAlpha));
		}
		
		//
		// Pause
		//
		if(paused)
		{
			const char* text1 = "<ESC> CONTINUAR";
			const char* text2 = "<ENTER> SALIR DEL JUEGO";
			
			int y1 = (SCREEN_HEIGHT/2)-16;
			int y2 = (SCREEN_HEIGHT/2)+16;
			int width1 = font->textWidth(text1);
			int width2 = font->textWidth(text2);
			
			gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0, 0, 0, 100));
			
			gr->drawTexture(texturePause,
				SCREEN_WIDTH/2 - texturePause->getWidth()/2,
				SCREEN_HEIGHT/2 - texturePause->getHeight()/2);
			
			font->render(gr, SCREEN_WIDTH/2 - width1/2, y1, text1);
			font->render(gr, SCREEN_WIDTH/2 - width2/2, y2, text2);
		}
	}
}
