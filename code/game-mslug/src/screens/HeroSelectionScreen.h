////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroSelectionScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroSelectionScreen_h___
#define ___HeroSelectionScreen_h___
#include <gamelib/Screen.h>
#include <gamelib/TimeClock.h>
#include <vector>

class Sound;
class Texture;

class HeroSelectionScreen : public Screen
{
	enum STATE
	{
		STATE_FADE_IN,
		STATE_IDLE,
		STATE_FADE_OUT,
		STATE_NOTHING,
	};

	STATE							state;
	bool							removable;
	Screen*							nextScreen;
	
	//
	// Imagenes
	//
	Texture*						bar;
	Texture*						bricks;
	Texture*						background;
	
	//
	// Cursor de selección
	//
	TimeClock						cursorClock;
	int								cursorFrame;
	Texture*						cursorTexture;
	
	unsigned int					currentHero;
	Sound*							selectionSound;
	int								selectionSoundChannel;
	
	std::vector<class HeroProfile*>	heroes;
	
	int								fadeValue;
	TimeClock						fadeClock;

	int								selectedHeroSoundChannel;
public:
	HeroSelectionScreen();
	~HeroSelectionScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif

