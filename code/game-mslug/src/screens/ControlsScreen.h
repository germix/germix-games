////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ControlsScreen
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ControlsScreen_h___
#define ___ControlsScreen_h___
#include <gamelib/Screen.h>
#include <gamelib/TimeClock.h>
#include <vector>

class Scene;
class Font;
class Texture;

class ControlsScreen : public Screen
{
	bool			removable;
	Scene*			scene;
	Font*			font1;
	Font*			font2;
	Texture*		background;
	Texture*		buttonsPressed[7];
	Texture*		buttonsReleased[7];
public:
	ControlsScreen();
	~ControlsScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
