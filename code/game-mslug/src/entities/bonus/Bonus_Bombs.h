////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Bombs | Bonus incrementar la munición de bombas
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Bombs_h___
#define ___Bonus_Bombs_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_Bombs : public Bonus
{
	bool activated;
public:
	static const char* NAME;
public:
	Bonus_Bombs(Scene* scene, double x, double y);
	~Bonus_Bombs();
public:
	void collide(Entity* other);
protected:
	void animate(double dt);
	void activate(Hero* hero);
};

#endif
