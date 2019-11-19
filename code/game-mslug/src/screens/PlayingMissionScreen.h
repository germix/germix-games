////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlayingMissionScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PlayingMissionScreen_h___
#define ___PlayingMissionScreen_h___
#include <gamelib/Screen.h>
#include <gamelib/TimeClock.h>

#include <src/MissionCompleted.h>

#include <mach/String.h>

class Hud;
class Scene;
class Mission;

class Font;
class Sprite;
class Texture;

class PlayingMissionScreen : public Screen
{
	enum STATE
	{
		STATE_FADE_IN,
		STATE_PLAY_MISSION,
		STATE_HERO_LOSER,
		STATE_HERO_WINNER,
		STATE_EXIT,
	};
	enum PAUSE
	{
		PAUSE_NONE,
		PAUSE_NORMAL,
		PAUSE_TRY_EXIT,
	};
	STATE				state;
	bool				removable;
	Screen*				nextScreen;
	
	bool				fadeIn;
	int					fadeValue;
	TimeClock			fadeClock;
	
	Hud*				hud;
	Scene*				scene;
	Mission*			mission;


	Font*				font1;
	Font*				font2;
	Font*				font5;

	bool				paused;
	Texture*			pausedTexture;
	
	MissionCompleted	missionCompleted;

	String				heroName;
	String				sceneName;
public:
	PlayingMissionScreen(const char* heroName = "marco", const char* sceneName = "msxm1");
	~PlayingMissionScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
