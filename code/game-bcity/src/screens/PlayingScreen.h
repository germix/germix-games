////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlayingScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PlayingScreen_h___
#define ___PlayingScreen_h___
#include <gamelib/Screen.h>

#include <gamelib/TimeClock.h>

class TmxMap;

class Font;
class Sound;
class Music;
class Texture;

class Map;
class Scene;
class Player;
class HeroTank;
class StagesProvider;

class PlayingScreen : public Screen
{
	enum STATE
	{
		STATE_LOAD,
		STATE_OPENING,
		STATE_CLOSING,
		STATE_PLAYING,
		STATE_FADING_OUT_SOUND,
	};
	STATE				state;
	bool				removable;
	
	Map*				map;
	Scene*				scene;
	
	HeroTank*			hero1;
	Player*				player1;
	HeroTank*			hero2;
	Player*				player2;
	
	int					stage;			// Número de la etapa
	StagesProvider*		stages;
	
	Screen*				nextScreen;
	
	TimeClock			openingClock;
	int					openingHeight;

	Font*				fontRed;
	Font*				fontBlack;
	Texture*			textureGameOver;
	Texture*			textureStageIndicator;
	Texture*			texturePlayerIndicator1;
	Texture*			texturePlayerIndicator2;

	double				gameOverY;

	bool				tryExit;
	Texture*			texturePauseTitle;
	Texture*			texturePauseBackground;

	Sound*				introStage;
	int					introStageChannel;
public:
	PlayingScreen(StagesProvider* provider, Player* player1, Player* player2);
	~PlayingScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
private:
	void loadStage();
	void drawEnemySet(Graphics* gr, int x, int y);
	void drawStageIndicator(Graphics* gr, int x, int y);
	void drawPlayerScore(Graphics* gr, int x, int y, HeroTank* hero, bool toLeft);
	void drawPlayerIndicator(Graphics* gr, int x, int y, HeroTank* hero, Texture* texture);
};

#endif
