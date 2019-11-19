////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugPlayingScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PlayingDebugScreen_h___
#define ___PlayingDebugScreen_h___
#include <gamelib/Screen.h>
#include <vector>

class Hud;
class Scene;
class Hero;

class DebugPlayingScreen : public Screen
{
protected:
	bool					removable;
	Hero*					hero;
	Scene*					scene;
	int						currentWeapon;
	Hud*					hud;
public:
	DebugPlayingScreen();
	~DebugPlayingScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
