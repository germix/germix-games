////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnterNameScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___EnterNameScreen_h___
#define ___EnterNameScreen_h___
#include <gamelib/Screen.h>
#include <gamelib/TimeClock.h>
#include <mach/Random.h>

class Font;
class Texture;

class EnterNameScreen : public Screen
{
	class StringEdit;
	
	enum STATE
	{
		STATE_FADE_IN,
		STATE_NORMAL,
		STATE_FADE_OUT,
	};
	enum SHOOTING_STAR_STATE
	{
		SHOOTING_STAR_STATE_WAITING,
		SHOOTING_STAR_STATE_FALLING,
	};
	STATE				state;
	bool				removable;

	Font*				font;

	Texture*			background;
	Texture*			shootingStar;
	double				shootingStarX;
	double				shootingStarY;
	SHOOTING_STAR_STATE	shootingStarState;
	TimeClock			shootingStarClock;
	Random				shootingStarRandom;

	StringEdit*			stringEdit;
	int					fadingValue;
	TimeClock			fadingClock;

	int					score;
	char				scoreText[32];
	int					hostages;
	char				hostagesText[32];
public:
	EnterNameScreen(int score, int hostages);
	~EnterNameScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
