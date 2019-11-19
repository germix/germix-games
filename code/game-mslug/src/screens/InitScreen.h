////////////////////////////////////////////////////////////////////////////////////////////////////
//
// InitScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___InitScreen_h___
#define ___InitScreen_h___
#include <mach/Point.h>
#include <gamelib/Screen.h>
#include <gamelib/TimeClock.h>

class Font;
class Sound;
class Screen;
class InitScreenLetter;

class InitScreen : public Screen
{
	enum STATE
	{
		STATE_FADE_IN,
		STATE_ANIMATING,
		STATE_CLASH,
		STATE_METALSLUG,
		STATE_WAITING_FOR_ENTER,
		STATE_NOTHING,
	};
	STATE				state;
	TimeClock			clock;

	//
	// Sonidos
	//
	Sound*				clashSound;
	Sound*				enterSound;
	Sound*				metalSlugSound;
	
	//
	// Fadding
	//
	int					fadeDir;
	int					fadeValue;
	
	//
	// ...
	//
	Font*				font;
	const char*			text;
	Point				textPos;
	InitScreenLetter**	letters;
	int					currentLetter;

	Screen*				nextScreen;
public:
	InitScreen();
	~InitScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
