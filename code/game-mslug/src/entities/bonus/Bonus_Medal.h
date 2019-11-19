////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Medal | Bonus medalla
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Medal_h___
#define ___Bonus_Medal_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_Medal : public Bonus
{
public:
	static const char* NAME;
public:
	Bonus_Medal(Scene* scene, double x, double y);
	~Bonus_Medal();
protected:
	void animate(double dt);
	void activate(Hero* hero);
};

#endif
