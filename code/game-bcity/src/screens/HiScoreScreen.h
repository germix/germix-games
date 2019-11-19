////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HiScoreScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HiScoreScreen_h___
#define ___HiScoreScreen_h___
#include <gamelib/Screen.h>

#include <gamelib/TimeClock.h>

class Font;

class HiScoreScreen : public Screen
{
	bool		removable;
	char		scoreText[24];
	int			soundChannel;
	
	int			fontIndex;
	TimeClock	fontClock;
	Font*		charFonts[4];
	Font*		numberFonts[4];
public:
	HiScoreScreen(int score);
	~HiScoreScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
