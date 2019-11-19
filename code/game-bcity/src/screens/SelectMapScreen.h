////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SelectMapScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SelectMapScreen_h___
#define ___SelectMapScreen_h___
#include <gamelib/Screen.h>

class Map;
class Player;
class Font;
class ListBox;

class SelectMapScreen : public Screen
{
	bool					removable;
	Map*					map;
	ListBox*				listBox;
	Screen*					nextScreen;
	bool					customMaps;
	Player*					player1;
	Player*					player2;
public:
	SelectMapScreen(bool custom, Player* player1, Player* player2);
	~SelectMapScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
