////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GameOverScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/GameOverScreen.h>
#include <src/Config.h>

#include <mach/Math.h>
#include <mach/Mixer.h>
#include <mach/Color.h>
#include <mach/Graphics.h>
#include <mach/Keyboard.h>
#include <mach/Texture.h>
#include <mach/TextureLoader.h>

GameOverScreen::GameOverScreen()
: state(STATE_FADING)
, removable(false)
, music(null)
, playingMusic(false)
, background(null)
, fadingValue(255)
, fadingClock(0.05)
{
}
GameOverScreen::~GameOverScreen()
{
}
Screen* GameOverScreen::getNext()
{
	return null;
}
bool    GameOverScreen::isRemovable()
{
	return removable;
}
void    GameOverScreen::show(Machine* mach)
{
	music = Mixer::loadMusic("mslug/screens/gameover/GameOver.ogg");
	background = TextureLoader::load("mslug/screens/gameover/GameOver.png");
}
void    GameOverScreen::hide(Machine* mach)
{
	Mixer::freeMusic(music);
	
	delete background;
}
void    GameOverScreen::update(Machine* mach, double dt)
{
	switch(state)
	{
		case STATE_FADING:
			if(fadingClock.update(dt))
			{
				fadingValue -= 10;
				fadingValue = Math::max(0, fadingValue);
				if(fadingValue == 0)
				{
					fadingValue = 0;
					state = STATE_NOTHING;
				}
				if(!playingMusic && fadingValue <= 150)
				{
					playingMusic = true;
					Mixer::playMusic(music);
				}
			}
			break;
		case STATE_NOTHING:
			if(Keyboard::isPressed(Key::ESCAPE) || Keyboard::isPressed(Key::RETURN) || Keyboard::isPressed(Key::KP_ENTER))
			{
				removable = true;
			}
			break;
	}
}
void    GameOverScreen::render(Machine* mach, Graphics* gr)
{
	gr->drawTexture(background, 0, 0);
	if(state == STATE_FADING)
	{
		gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0, 0, 0, fadingValue));
	}
}
