////////////////////////////////////////////////////////////////////////////////////////////////////
//
// StatisticsScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___StatisticsScreen_h___
#define ___StatisticsScreen_h___
#include <gamelib/Screen.h>
#include <gamelib/TimeClock.h>

#include <string>
#include <vector>

#include <src/base/Player.h>

class Font;
class Sound;
class Texture;

class Player;

class StatisticsScreen : public Screen
{
	enum STATE
	{
		STATE_COUNTING,
		STATE_EXTRA_BONUS,
		STATE_IDLE,
	};
	class HeroValues
	{
	public:
		int				values[4];
		int				tmpValues[4];
		int				currentScore;
		
		Player*			player;
		bool			isPlayerOne;

		bool			alive;
		bool			hasExtraBonus;
		
	public:
		HeroValues(bool one, Player* p, const int* v, bool ___alive)
			: currentScore(0)
			, player(p)
			, isPlayerOne(one)
			, alive(___alive)
			, hasExtraBonus(false)
		{
			for(unsigned int i = 0; i < 4; i++)
			{
				values[i] = v[i];
				tmpValues[i] = 0;
				currentScore += ((i+1)*100) * v[i];
			}
		}
	public:
		bool increment(int idx)
		{
			if(tmpValues[idx] < values[idx])
			{
				tmpValues[idx]++;
				return true;
			}
			return false;
		}
		void addExtraBonus()
		{
			hasExtraBonus = true;
			player->addScore(1000);
		}
		int getPlayerScore() const
		{
			return player->getScore();
		}
	};
	STATE			state;
	
	bool			removable;
	int				currentEnemy;
	
	TimeClock		clock;
	
	bool 			showTotal;

	HeroValues*		heroValues1;
	HeroValues*		heroValues2;
	
	std::string		stageText;

	Font*			fontRed;
	Font*			fontWhite;
	Font*			fontOrange;
	
	Sound*			tickSound;

	Texture*		lineTexture;
public:
	StatisticsScreen(const std::string& stageName,
						Player* player1, const int* victims1, bool alive1);
	StatisticsScreen(const std::string& stageName,
						Player* player1, const int* victims1, bool alive1,
						Player* player2, const int* victims2, bool alive2);
	~StatisticsScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
private:
	void renderInfo(Graphics* gr, HeroValues* hv);
	void renderArrow(Graphics* gr, HeroValues* hv, int y);
	void renderValue(Graphics* gr, HeroValues* hv, int y, int index);
	void renderColumn1(Graphics* gr, HeroValues* hv, int y, Font* f, const char* valueString);
	void renderColumn2(Graphics* gr, HeroValues* hv, int y, Font* f, const char* pointsString);
	bool incrementValue(HeroValues* hv, int index);
};

#endif
