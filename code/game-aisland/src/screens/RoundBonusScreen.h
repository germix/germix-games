////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RoundBonusScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___RoundBonusScreen_h___
#define ___RoundBonusScreen_h___
#include <gamelib/Screen.h>
#include <gamelib/TimeClock.h>

class Font;
class Texture;
class Sound;
class HeroInfo;

class RoundBonusScreen : public Screen
{
	enum STATE
	{
		STATE_WAIT_1,
		STATE_ADD_BONUS,
		STATE_WAIT_2,
		STATE_ADD_SCORE_1,
		STATE_WAIT_3,
		STATE_WAIT_4,
		STATE_ADD_SCORE_2,
		STATE_WAIT_5,
		STATE_ADD_SCORE_3,
		STATE_FINISHED,
	};
	bool				removable;
	STATE				state;

	HeroInfo*			info;
	TimeClock			clock;
	
	Font*				font;
	Texture*			pot;
	Texture*			livesMark;
	Texture*			healthMark;
	
	int					bonus;
	int					potBonus;
	int					maxBonus;

	Sound*				soundAddScore;
	Sound*				soundPotBonus;
	
public:
	RoundBonusScreen(HeroInfo* i);
	virtual ~RoundBonusScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
