////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlayingScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PlayingScreen_h___
#define ___PlayingScreen_h___
#include <gamelib/Screen.h>

class Scene;
class Pacman;
class Font;
class Texture;

#include <src/Ballons.h>

class PlayingScreen : public Screen
{
	enum STATE
	{
		STATE_PLAY,
		STATE_WINNER,
		STATE_GAMEOVER,
	};
	STATE				state;
	bool				removable;
	Screen*				nextScreen;
	
	Scene*				scene;
	Pacman*				pacman;

	bool				paused;
	bool				finished;

	Font*				font;
	Texture*			textureHeart;
	Texture*			texturePause;
	
	Ballons				ballons;
	
	int					fadeoutAlpha;
	TimeClock			fadeoutClock;
public:
	PlayingScreen(const char* mapName = "classic.tmx");
	~PlayingScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
