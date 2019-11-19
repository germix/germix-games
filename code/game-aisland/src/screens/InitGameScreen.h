////////////////////////////////////////////////////////////////////////////////////////////////////
//
// InitGameScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___InitGameScreen_h___
#define ___InitGameScreen_h___
#include <gamelib/Screen.h>
#include <gamelib/TimeClock.h>

class Font;
class Sound;
class Sprite;
class Texture;

class InitGameScreen : public Screen
{
	enum STATE
	{
		STATE_0,
		STATE_LEFT,
		STATE_ABOUT,
		STATE_NORMAL,
		STATE_WATING,
	};
	class TypedText;
	
	bool				removable;
	Screen*				nextScreen;
	
	STATE				state;
	Font*				font;
	Texture*			background;
	int					backgroundX;
	
	TypedText*			typedTexts[3];
	int					typedTextsMax;
	
	TimeClock			clock;
	Sprite*				heroWalk;
	TimeClock			heroWalkClock;
	int					heroWalkIndex;
	
	Sound*				menuSound;
	int					menuSelectedIndex;
	Texture*			menuSelectionTexture;

	static const char* menuStrings[];
public:
	InitGameScreen();
	virtual ~InitGameScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
