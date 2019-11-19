////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlaySceneScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PlaySceneScreen_h___
#define ___PlaySceneScreen_h___
#include <gamelib/Screen.h>

#include <src/HeroInfo.h>

class Scene;

class PlaySceneScreen : public Screen
{
	HeroInfo	info;
	Scene*		scene;
	bool		removable;
public:
	PlaySceneScreen(int area, int round);
	virtual ~PlaySceneScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
