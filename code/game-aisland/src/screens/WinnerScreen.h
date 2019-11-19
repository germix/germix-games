////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WinnerScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___WinnerScreen_h___
#define ___WinnerScreen_h___
#include <gamelib/Screen.h>

#include <gamelib/TimeClock.h>

class Font;
class Texture;
class Sprite;
class SpriteSheet;

class WinnerScreen : public Screen
{
	enum STATE
	{
		STATE_WALKING,
		STATE_SAVING,
		STATE_FREE,
		STATE_LOVE,
		STATE_FINISHED,
	};
	bool				removable;
	STATE				state;

	Font*				font;
	
	double				heroX;
	SpriteSheet*		heroSheet;
	Sprite*				heroSprite;
	int					heroSpriteIndex;
	TimeClock			heroSpriteClock;
	
	SpriteSheet*		tinaSheet;
	Sprite*				tinaSprite;
	int					tinaSpriteIndex;
	TimeClock			tinaSpriteClock;
	
	int					savingIdleCounter;
	Texture*			happyCoupleTexture;
	double				happyCoupleHeartY;
	Texture*			happyCoupleHeartTexture;
	
	static const char* lines[];
public:
	WinnerScreen();
	virtual ~WinnerScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
