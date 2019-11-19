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

class Font;
class Texture;
class TiledMap;

class MenuScreen : public Screen
{
	bool				removable;
	Screen*				nextScreen;

	TiledMap*			tiledMap;
	
	int					currentItem;
	
	Font*				font;
	Texture*			imageTitle;
	Texture*			imageArrowLeft;
	Texture*			imageArrowRight;
	
	static const char*	itemTexts[];
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
