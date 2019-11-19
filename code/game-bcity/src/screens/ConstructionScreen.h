////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ConstructionScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ConstructionScreen_h___
#define ___ConstructionScreen_h___
#include <gamelib/Screen.h>

#include <gamelib/TimeClock.h>

class Font;
class Texture;

class ListBox;
class StringEdit;

class ConstructionScreen : public Screen
{
	enum STATE
	{
		STATE_EDIT,
		STATE_LOAD,
		STATE_SAVE,
	};

	STATE		state;
	bool		removable;
	int*		tiles;
	int			mapWidth;
	int			mapHeight;
	int			tileWidth;
	int			tileHeight;
	Texture*	cursor;
	int			cursorX;
	int			cursorY;
	int			cursorBlinkIndex;
	TimeClock	cursorBlinkClock;
	
	int			patternIndex;

	Font*		fontBlack;
	Font*		fontOrange;
	
	ListBox*	listBox;
	StringEdit*	stringEdit;
public:
	ConstructionScreen();
	~ConstructionScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
private:
	void updateEdit(double dt);
	void updateLoad(double dt);
	void updateSave(double dt);
	void newMap();
	void loadMap(const char* fileName);
	void saveMap(const char* fileName);
	void drawTile(Graphics* gr, int dx, int dy, int tileX, int tileY, int tileIndex);
	void replaceTiles();
	void replaceTiles(int idx, int curX, int curY);
};

#endif
