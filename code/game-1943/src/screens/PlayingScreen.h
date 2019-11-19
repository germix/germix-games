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

class PlayingScreen : public Screen
{
	bool		removable;
	Screen*		nextScreen;
	Scene*		scene;
public:
	PlayingScreen();
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
