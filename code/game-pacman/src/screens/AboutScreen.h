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

class Font;
class TiledMap;

class AboutScreen : public Screen
{
	bool			removable;
	Font*			font;
	TiledMap*		tiledMap;
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
