////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SelectScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SelectScreen_h___
#define ___SelectScreen_h___
#include <gamelib/Screen.h>
#include <vector>
#include <mach/String.h>

class TiledMap;
class Font;
class Texture;

class SelectScreen : public Screen
{
protected:
	bool					removable;
	Screen*					nextScreen;
	
	const char*				title;
	TiledMap*				tiledMap;
	
	std::vector<String>		list;
	unsigned int			scrollPos;
	unsigned int			selectedItem;
	unsigned int			maxVisibleLines;

	Font*					font1;
	Font*					font2;
	Texture*				indicator;
	
public:
	SelectScreen(int maxVisibleLines, const char* title, const char* tmxName);
	~SelectScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
private:
	void select(int index);
protected:
	void scrollToItem();
protected:
	virtual void onExit() = 0;
//	virtual void onShow() = 0;
	virtual void onEnter(const String& selection) = 0;
	virtual void onSelectionChanged(int index, const String& selection) = 0;
};

#endif
