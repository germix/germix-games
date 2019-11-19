////////////////////////////////////////////////////////////////////////////////////////////////////
//
// InitScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___InitScreen_h___
#define ___InitScreen_h___
#include <gamelib/Screen.h>
#include <gamelib/TimeClock.h>
#include <src/base/Player.h>

class Font;
class Texture;
class Sprite;

class InitScreen : public Screen
{
	enum STATE
	{
		STATE_SCROLLING,
		STATE_MENU,
	};
	enum MENUITEM
	{
		MENUITEM_PLAY,
		MENUITEM_EXIT,
		MENUITEM_ABOUT,
		MENUITEM_SKIRMISH,
		MENUITEM_CONSTRUCTION,
		MAX_MENUITEMS,
	};
	
	STATE				state;
	bool				removable;
	Screen*				nextScreen;

	Font*				font;
	Texture*			logo;
	
	int 				offsetY;
	TimeClock			scrollClock;
	
	int					menuItem;
	Sprite*				menuIndicator;

	Player				player;
	
	static const char*	items[];
public:
	InitScreen();
	~InitScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
