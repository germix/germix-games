////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroInfo
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroInfo_h___
#define ___HeroInfo_h___

class HeroInfo
{
public:
	enum
	{
		MAX_HEALTH = 16,
	};

	//
	// Escena
	//
	bool	pot;
	int		score;
	int		lives;
	int		health;
	int		weapon;
	
/*
	//
	// Global
	//
	int		area = 1;	// TODO: eliminar
	int		round = 1;	// TODO: eliminar
//	int		totalScore = 0;
	
*/
public:
	HeroInfo()
		: pot(false)
		, score(0)
		, lives(3)
		, health(11)
		, weapon(0)
	{
	}
	HeroInfo(const HeroInfo& o)
		: pot(o.pot)
		, score(o.score)
		, lives(o.lives)
		, health(o.health)
		, weapon(o.weapon)
	{
	}
public:
	void reset()
	{
		health = 11;
		pot = false;
	}
public:
	HeroInfo& operator = (const HeroInfo& o)
	{
		pot = o.pot;
		score = o.lives;
		lives = o.lives;
		health = o.health;
		weapon = o.weapon;
		return *this;
	}
};

#endif
