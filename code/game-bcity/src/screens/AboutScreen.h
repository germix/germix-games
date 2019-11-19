////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AboutScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___AboutScreen_h___
#define ___AboutScreen_h___
#include <gamelib/Screen.h>

class Map;
class Font;

class AboutScreen : public Screen
{
	bool	removable;
	Map*	map;
	Font*	font;
public:
	AboutScreen();
	~AboutScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
