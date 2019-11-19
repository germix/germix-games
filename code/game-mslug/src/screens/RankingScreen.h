////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RankingScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___RankingScreen_h___
#define ___RankingScreen_h___
#include <gamelib/Screen.h>
#include <gamelib/TimeClock.h>
#include <vector>

#include <src/ranking/RankingRecord.h>

class Font;
class Texture;

class RankingScreen : public Screen
{
	enum STATE
	{
		STATE_STARTING,
		STATE_LISTING,
		STATE_NOTHING,
	};
	STATE						state;
	TimeClock					clock;
	bool						removable;
	Texture*					texture;
	int							textureWidth;
	int							textureHeight;
	int							drawValue;
	int							halfWidth;
	
	Font*						font1;
	Font*						font2;
	
	int							currentUser;
	
	std::vector<RankingRecord>	rankingRecords;
	int							rankingRecordsCount;

public:
	RankingScreen();
	~RankingScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
