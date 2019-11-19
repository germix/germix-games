////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GameOverScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___GameOverScreen_h___
#define ___GameOverScreen_h___
#include <gamelib/Screen.h>

class Font;

class GameOverScreen : public Screen
{
	bool	removable;
	Font*	font;
	int		hiScore;
	int		soundChannel;
public:
	GameOverScreen(int score = 0);
	~GameOverScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
