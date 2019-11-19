////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PistolScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PistolScreen_h___
#define ___PistolScreen_h___
#include <gamelib/Screen.h>
#include <gamelib/TimeClock.h>

class Font;
class Texture;

class PistolScreen : public Screen
{
	bool			removable;
	Texture*		pistolTexture;
	Texture*		bubblesTexture;
	Texture*		backgroundTexture;

	int				offset;
	TimeClock		backgroundClock;
	TimeClock		nextBubbleClock;
	int				nextBubble;
	int				nextStartBubblePoint;

	Font*			font1;
	Font*			font2;
	Font*			fontTitle;
public:
	PistolScreen();
	~PistolScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
