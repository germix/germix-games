////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Player
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Player_h___
#define ___Player_h___

class Player
{
	int				score;
	int				lifes;
	int				stars;
public:
	Player();
	~Player();
public:
	void reset();
	int getLifes() const
	{
		return lifes;
	}
	int getStars() const
	{
		return stars;
	}
	int getScore() const
	{
		return score;
	}
	void setLifes(int l)
	{
		lifes = l;
	}
	void setStars(int s)
	{
		stars = s;
	}
	void addScore(int s)
	{
		score += s;
	}
};

#endif
