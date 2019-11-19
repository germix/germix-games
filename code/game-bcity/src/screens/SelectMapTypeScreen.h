////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SelectMapTypeScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SelectMapTypeScreen_h___
#define ___SelectMapTypeScreen_h___
#include <gamelib/Screen.h>

class Map;
class Player;
class Font;
class ListBox;

class SelectMapTypeScreen : public Screen
{
	bool		removable;
	Map*		map;
	ListBox*	listBox;
	Screen*		nextScreen;
	Font*		font;

	Player*		player1;
	Player*		player2;
public:
	SelectMapTypeScreen(Player* player1, Player* player2);
	~SelectMapTypeScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
