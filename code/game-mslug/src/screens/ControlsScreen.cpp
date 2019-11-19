////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ControlsScreen
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/ControlsScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <mach/Keyboard.h>
#include <mach/Graphics.h>
#include <mach/Texture.h>
#include <mach/TextureLoader.h>

#include <gamelib/Font.h>

#include <src/scene/Map.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>

class ControlsMap : public Map
{
	int x;
	int y;
	int width;
	int height;
	Font* borders;
public:
	ControlsMap(int _x, int _y, int _width, int _height)
		: x(_x)
		, y(_y)
		, width(_width)
		, height(_height)
	{
		borders = res.findFont("Font.Borders");
	}
public:
	virtual int getX() const
	{
		return x;
	}
	virtual int getY() const
	{
		return y;
	}
	virtual int getWidth() const
	{
		return (width+1)*8;
	}
	virtual int getHeight() const
	{
		return (height+1)*8;
	}
	virtual Vector2f getSuggestedSceneScroll(Entity* entity) const
	{
		return Vector2f();
	}
	virtual void update(Scene* scene, double dt)
	{
	}
	virtual void renderBackground(Graphics* gr, int sx, int sy) const
	{
	}
	virtual void renderForeground(Graphics* gr, int sx, int sy) const
	{
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
	}

	virtual unsigned int checkCollision(
								Entity* entity,
								Vector2f& newPosition,
								Vector2f& newVelocity,
								const Vector2f& oldPosition,
								const Vector2f& oldVelocity,
								unsigned int terrainType) const
	{
		if(newPosition.y >= y+height)
		{
			newVelocity.y = 0;
			newPosition.y = y+height;
			
			return COLLISION_FLAG_BOTTOM;
		}
		return 0;
	}
};
ControlsScreen::ControlsScreen()
: removable(false)
, scene(null)
, font1(null)
, font2(null)
, background(null)
{
}
ControlsScreen::~ControlsScreen()
{
}
Screen* ControlsScreen::getNext()
{
	return null;
}
bool    ControlsScreen::isRemovable()
{
	return removable;
}
void    ControlsScreen::show(Machine* mach)
{
	font1 = res.findFont("Font.8x8.2");
	font2 = res.findFont("Font.16x16.1");
	background = TextureLoader::load("mslug/screens/controls/background.png");

#if 0
	buttonsPressed[0] = TextureLoader::load("mslug/screens/controls/button-shot-pressed.png");
	buttonsPressed[1] = TextureLoader::load("mslug/screens/controls/button-jump-pressed.png");
	buttonsPressed[2] = TextureLoader::load("mslug/screens/controls/button-bomb-pressed.png");
	buttonsPressed[3] = TextureLoader::load("mslug/screens/controls/button-arrow_up-pressed.png");
	buttonsPressed[4] = TextureLoader::load("mslug/screens/controls/button-arrow_down-pressed.png");
	buttonsPressed[5] = TextureLoader::load("mslug/screens/controls/button-arrow_left-pressed.png");
	buttonsPressed[6] = TextureLoader::load("mslug/screens/controls/button-arrow_right-pressed.png");
	buttonsReleased[0] = TextureLoader::load("mslug/screens/controls/button-shot.png");
	buttonsReleased[1] = TextureLoader::load("mslug/screens/controls/button-jump.png");
	buttonsReleased[2] = TextureLoader::load("mslug/screens/controls/button-bomb.png");
	buttonsReleased[3] = TextureLoader::load("mslug/screens/controls/button-arrow_up.png");
	buttonsReleased[4] = TextureLoader::load("mslug/screens/controls/button-arrow_down.png");
	buttonsReleased[5] = TextureLoader::load("mslug/screens/controls/button-arrow_left.png");
	buttonsReleased[6] = TextureLoader::load("mslug/screens/controls/button-arrow_right.png");
#else
	buttonsPressed[0] = TextureLoader::load("mslug/screens/controls/button-arrow_up-pressed.png");
	buttonsPressed[1] = TextureLoader::load("mslug/screens/controls/button-arrow_down-pressed.png");
	buttonsPressed[2] = TextureLoader::load("mslug/screens/controls/button-arrow_left-pressed.png");
	buttonsPressed[3] = TextureLoader::load("mslug/screens/controls/button-arrow_right-pressed.png");
	buttonsPressed[4] = TextureLoader::load("mslug/screens/controls/button-shot-pressed.png");
	buttonsPressed[5] = TextureLoader::load("mslug/screens/controls/button-jump-pressed.png");
	buttonsPressed[6] = TextureLoader::load("mslug/screens/controls/button-bomb-pressed.png");
	buttonsReleased[0] = TextureLoader::load("mslug/screens/controls/button-arrow_up.png");
	buttonsReleased[1] = TextureLoader::load("mslug/screens/controls/button-arrow_down.png");
	buttonsReleased[2] = TextureLoader::load("mslug/screens/controls/button-arrow_left.png");
	buttonsReleased[3] = TextureLoader::load("mslug/screens/controls/button-arrow_right.png");
	buttonsReleased[4] = TextureLoader::load("mslug/screens/controls/button-shot.png");
	buttonsReleased[5] = TextureLoader::load("mslug/screens/controls/button-jump.png");
	buttonsReleased[6] = TextureLoader::load("mslug/screens/controls/button-bomb.png");
#endif
	{
		int x = 160-32-16-16-8;
		int y = 112-16;
		int w = (18+2+2+2+1);
		scene = new Scene(new ControlsMap(
			x,
			y,
			w,
			12+2), false);
		scene->addEntity(new Hero(scene, (w*8)/2, 0, "marco", true));
	}
}
void    ControlsScreen::hide(Machine* mach)
{
	delete background;
	for(int i = 0; i < 7; i++)
	{
		delete buttonsPressed[i];
		delete buttonsReleased[i];
	}
	delete scene;
}
void    ControlsScreen::update(Machine* mach, double dt)
{
	if(Keyboard::isDown(Key::ESCAPE))
	{
		removable = true;
	}
	else
	{
		scene->update(dt);
	}
}
void    ControlsScreen::render(Machine* mach, Graphics* gr)
{
#if 0
	int x = 16;
	int y = 48;
	static int keys[] =
	{
		Key::LETTER_A,
		Key::LETTER_S,
		Key::LETTER_D,
		Key::UP,
		Key::DOWN,
		Key::LEFT,
		Key::RIGHT,
	};
	static char* texts[] = 
	{
		"A",
		"S",
		"D",
		"UP",
		"DOWN",
		"LEFT",
		"RIGHT",
	};
	gr->drawTexture(background, 0, 0);
	font2->render(gr, SCREEN_WIDTH/2-(9*16)/2, 16, "CONTROLES");
	for(int i = 0; i < 7; i++)
	{
		if(Keyboard::isDown(keys[i]))
			gr->drawTexture(buttonsPressed[i], x, y);
		else
			gr->drawTexture(buttonsReleased[i], x, y);

		font1->render(gr, x+3*10, y + 4, texts[i]);

		y += 16 + 8;
	}
#else
	static int keys[] =
	{
		Key::UP,
		Key::DOWN,
		Key::LEFT,
		Key::RIGHT,
		Key::LETTER_A,
		Key::LETTER_S,
		Key::LETTER_D,
	};
	static struct
	{
		int x;
		int y;
	}pos[7] =
	{
		{ 48-12, 112 },
		{ 48-12, 144 },
		{ 32-12, 128 },
		{ 64-12, 128 },
		{ 24-12, 176 },
		{ 48-12, 176 },
		{ 72-12, 176 },
	};
	static char* texts[] = 
	{
		"A",
		"S",
		"D",
	};
	gr->drawTexture(background, 0, 0);
	font2->render(gr, SCREEN_WIDTH/2-(9*16)/2, 8-4, "CONTROLES");
	for(int i = 0; i < 7; i++)
	{
		if(Keyboard::isDown(keys[i]))
			gr->drawTexture(buttonsPressed[i], pos[i].x, pos[i].y);
		else
			gr->drawTexture(buttonsReleased[i], pos[i].x, pos[i].y);
	}
	for(int i = 0; i < 3; i++)
	{
		font1->render(gr, pos[i+4].x+4, pos[i+4].y+16+4, texts[i]);
	}
#endif
	scene->render(gr);
}
