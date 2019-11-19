////////////////////////////////////////////////////////////////////////////////////////////////////
//
// InitRoundScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___InitRoundScreen_h___
#define ___InitRoundScreen_h___
#include <gamelib/Screen.h>
#include <gamelib/TimeClock.h>

class Font;
class Sprite;
class Texture;
class HeroInfo;

class InitRoundScreen : public Screen
{
	bool				removable;
	Screen*				nextScreen;
	
	HeroInfo*			info;
	int					area;
	int					round;
	TimeClock			clock;

	Font*				font;
	Texture*			livesMark;
	Texture*			healthMark;
	
	Sprite*				heroWalk;
	TimeClock			heroWalkClock;
	int					heroWalkIndex;
	
public:
	InitRoundScreen(int area, int round, HeroInfo* info);
	virtual ~InitRoundScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
