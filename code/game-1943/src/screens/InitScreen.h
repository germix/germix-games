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
class Texture;

class InitScreen : public Screen
{
	enum STATE
	{
		STATE_FADING,
		STATE_ANIMATING,
		STATE_WAITING,
	};
	STATE				state;
	bool				removable;
	Screen*				nextScreen;
	
	TimeClock			clock;
	
	//
	// ...
	//
	Font*				font;
	const char*			text;
	Point				textPos;
	int					fadingDir;
	int					fadingAlpha;
	Texture*			titleTexture;
	int					animationIndex;
	Texture**			animationTextures;
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
