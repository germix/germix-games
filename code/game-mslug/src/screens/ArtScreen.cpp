////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ArtScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/ArtScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <stdio.h>

#include <mach/Keyboard.h>
#include <mach/Graphics.h>
#include <mach/Texture.h>
#include <mach/TextureLoader.h>

#include <gamelib/Font.h>

ArtScreen::ArtScreen()
: removable(false)
, currentTexture(0)
{
}
ArtScreen::~ArtScreen()
{
}
Screen* ArtScreen::getNext()
{
	return null;
}
bool    ArtScreen::isRemovable()
{
	return removable;
}
void    ArtScreen::show(Machine* mach)
{
	font = res.findFont("Font.16x16.2");
	fontTitle = res.findFont("Font.16x16.1");
	textures[0] = TextureLoader::load("mslug/screens/art/art-01.png");
	textures[1] = TextureLoader::load("mslug/screens/art/art-02.png");
	textures[2] = TextureLoader::load("mslug/screens/art/art-03.png");
	textures[3] = TextureLoader::load("mslug/screens/art/art-04.png");
	textures[4] = TextureLoader::load("mslug/screens/art/art-05.png");
	textures[5] = TextureLoader::load("mslug/screens/art/art-06.png");
	textures[6] = TextureLoader::load("mslug/screens/art/art-07.png");
	textures[7] = TextureLoader::load("mslug/screens/art/art-08.png");
	textures[8] = TextureLoader::load("mslug/screens/art/art-09.png");
	textures[9] = TextureLoader::load("mslug/screens/art/art-10.png");
	textures[10] = TextureLoader::load("mslug/screens/art/art-11.png");
	textures[11] = TextureLoader::load("mslug/screens/art/art-12.png");
}
void    ArtScreen::hide(Machine* mach)
{
	for(int i = 0; i < 12; i++)
	{
		delete textures[i];
	}
}
void    ArtScreen::update(Machine* mach, double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		removable = true;
	}
	else if(Keyboard::isPressed(Key::LEFT))
	{
		if(currentTexture > 0)
			currentTexture--;
	}
	else if(Keyboard::isPressed(Key::RIGHT))
	{
		if(currentTexture < 12-1)
			currentTexture++;
	}
}
void    ArtScreen::render(Machine* mach, Graphics* gr)
{
	char text[] = "  00/00  ";
	gr->drawTexture(textures[currentTexture], 0, 0);

	fontTitle->render(gr, SCREEN_WIDTH/2-(4*16)/2, 8-4, "ARTE");
#if 0
	sprintf(text, "%c %02d/12 %c",
		(currentTexture == 0) ? ' ' : 135,
		currentTexture+1,
		(currentTexture == 11) ? ' ' : 136);

	font->render(gr, SCREEN_WIDTH/2 - (9*16)/2, 208, text);
#else
	sprintf(text, "%02d/12", currentTexture+1);

	font->render(gr, SCREEN_WIDTH/2 - (5*16)/2, 208, text);
#endif
}
