////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroScore
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroScore_h___
#define ___HeroScore_h___

class HeroScore
{
	int value;
public:
	HeroScore();
	~HeroScore();
public:
	void reset();
	int  getScore() const;
	void addScore(int s);
};

#endif