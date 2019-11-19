////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AdventureScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___AdventureScreen_h___
#define ___AdventureScreen_h___
#include <gamelib/Screen.h>

#include <src/HeroInfo.h>

#include <queue>

class Scene;
class Font;
class Texture;

class AdventureScreen : public Screen
{
	HeroInfo				info;
	int						area;
	int						round;
	Scene*					scene;
	bool					removable;
	std::queue<Screen*>		nextScreens;
	bool					needLoadScene;
	bool					paused;
	Font*					pausedFont;
	Texture*				pausedBackground;
public:
	AdventureScreen();
	virtual ~AdventureScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
