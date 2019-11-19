////////////////////////////////////////////////////////////////////////////////////////////////////
//
// InitScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/InitScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <mach/Color.h>
#include <mach/Keyboard.h>
#include <mach/Graphics.h>
#include <mach/Texture.h>
#include <mach/TextureLoader.h>
#include <gamelib/Font.h>

#include <stdio.h>

#define TIME_ANIMATION			0.1
#define TIME_FADING_BLACK		1.7/1000.0
#define TIME_FADING_ENTER		1/1000.0

#define MAX_ANIMATION_TEXTURES	8

#define MAX_COLOR_CHANNEL_VALUE	40

InitScreen::InitScreen()
: state(STATE_FADING)
, removable(false)
, nextScreen(null)
, clock(TIME_FADING_BLACK)
, font(null)
, text("PRESIONE <ENTER>")
, fadingAlpha(0)
, titleTexture(null)
, animationIndex(0)
, animationTextures(null)
{
}
InitScreen::~InitScreen()
{
	if(titleTexture)
		delete titleTexture;
	if(animationTextures)
	{
		for(int i = 0; i < MAX_ANIMATION_TEXTURES; i++)
			delete animationTextures[i];
		delete [] animationTextures;
	}
}
Screen* InitScreen::getNext()
{
	return nextScreen;
}
bool    InitScreen::isRemovable()
{
	return removable;
}
void    InitScreen::show(Machine* mach)
{
	font = res.findFont("font.1");
	textPos.x = SCENE_X + (SCENE_WIDTH/2 - font->textWidth(text)/2);
	textPos.y = SCENE_Y + (SCENE_HEIGHT-20);
	
	titleTexture = TextureLoader::load("1943/images/intro/1943.png");
	animationTextures = new Texture*[MAX_ANIMATION_TEXTURES];
	for(int i = 0; i < MAX_ANIMATION_TEXTURES; i++)
	{
		char sz[64];
		sprintf(sz, "1943/images/intro/anim-%d.png", (i+1));
		animationTextures[i] = TextureLoader::load(sz);
	}
}
void    InitScreen::hide(Machine* mach)
{
}
void    InitScreen::update(Machine* mach, double dt)
{
	switch(state)
	{
		case STATE_FADING:
			if(clock.update(dt))
			{
				fadingAlpha++;
				if(fadingAlpha >= MAX_COLOR_CHANNEL_VALUE)
				{
					state = STATE_ANIMATING;
					clock.reset(TIME_ANIMATION);
					fadingDir = -1;
					fadingAlpha = 255;
				}
			}
			break;
		case STATE_ANIMATING:
			if(clock.update(dt))
			{
				if(animationIndex < MAX_ANIMATION_TEXTURES-1)
				{
					animationIndex++;
				}
				else
				{
					state =  STATE_WAITING;
					clock.reset(TIME_FADING_ENTER);
				}
			}
			break;
		case STATE_WAITING:
			if(clock.update(dt))
			{
				fadingAlpha += fadingDir*8;
				if(fadingAlpha <= 0)
				{
					fadingDir = +1;
					fadingAlpha = 0;
				}
				else if(fadingAlpha >= 255)
				{
					fadingDir = -1;
					fadingAlpha = 255;
				}
			}
			if(Keyboard::isPressed(Key::RETURN))
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
void    InitScreen::render(Machine* mach, Graphics* gr)
{
	if(state == STATE_FADING)
	{
		gr->fillRect(SCENE_X, SCENE_Y, SCENE_WIDTH, SCENE_HEIGHT, Color(fadingAlpha, fadingAlpha, fadingAlpha));
	}
	else
	{
		gr->fillRect(SCENE_X, SCENE_Y, SCENE_WIDTH, SCENE_HEIGHT, Color(MAX_COLOR_CHANNEL_VALUE, MAX_COLOR_CHANNEL_VALUE, MAX_COLOR_CHANNEL_VALUE));
		gr->drawTexture(animationTextures[animationIndex], SCENE_X, SCENE_Y);
		if(state == STATE_WAITING)
		{
			int x = 0;
			int y = 50;
			gr->drawTexture(
				titleTexture,
				SCENE_X + ((SCENE_WIDTH/2) - (titleTexture->getWidth()/2)),
				SCENE_Y + 270);
			
			font->render(gr, textPos.x, textPos.y, text, fadingAlpha);
		}
	}
}
