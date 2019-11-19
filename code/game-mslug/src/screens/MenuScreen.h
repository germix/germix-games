////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MenuScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MenuScreen_h___
#define ___MenuScreen_h___
#include <gamelib/Screen.h>
#include <gamelib/TimeClock.h>
#include <mach/Color.h>

class Texture;
class Font;
class Sound;

class MenuScreen : public Screen
{
	enum STATE
	{
		STATE_IDLE,
		STATE_FADE_OUT,
		STATE_NOTHING,
	};
	STATE			state;
	
	Texture*		button;
	Texture*		background;
	Font*			font1;
	Font*			font2;
	Sound*			changedSound;
	int				changedSoundChannel;
	Sound*			selectedSound;
	int				selectedSoundChannel;
	
	int				fadeValue;
	Color			fadeColor;
	TimeClock		fadeClock;
	
	Screen*			nextScreen;
	int				currentMenu;
public:
	MenuScreen();
	~MenuScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
