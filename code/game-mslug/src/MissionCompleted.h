////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MissionCompleted
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MissionCompleted_h___
#define ___MissionCompleted_h___
#include <gamelib/TimeClock.h>

#include <vector>

class Hero;
class Font;
class Sprite;
class Graphics;
class Sound;

class MissionCompleted
{
	enum STATE
	{
		STATE_FADE_1,
		STATE_HOSTAGES,
		STATE_FADE_2,
		STATE_MISSION_COMPLETED,
		STATE_WAIT_FOR_FINISHED,
	};
	STATE				state;
	bool				finished;
	bool				activated;
	
	//
	// Atributos para la animación cuando se completa la misión
	//
	Font*				font1;
	Font*				font2;
	Font*				font3;
	Font*				font4;
	Font*				font5;
	Font*				borders;
	
	int					fadeAlpha;
	TimeClock			fadeClock;

	Sprite*				salute;
	int					saluteFrame;
	TimeClock			saluteClock;

	int					hostagesCount;
	std::vector<int>	hostagesNames;
	std::vector<int>	hostagesRanks;
	int					lastHostageName;
	TimeClock			lastHostageClock;
	int					noPrisionesBlink;
	int					noPrisionesBlinkCount;

	Hero*				hero;
	TimeClock			waitForFinishedClock;
public:
	MissionCompleted();
	~MissionCompleted();
public:
	void update(double dt);
	void render(Graphics* gr);
	void clear();
	void activate(Hero* hero, int hostagesCount);
	bool isFinished() const { return finished; }
	bool isActivated() const { return activated; }
};

#endif
