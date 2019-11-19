////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Teddy | Bonus osito Teddy
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Teddy_h___
#define ___Bonus_Teddy_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_Teddy : public Bonus
{
public:
	static const char* NAME;
public:
	Bonus_Teddy(Scene* scene, double x, double y);
	~Bonus_Teddy();
protected:
	void animate(double dt);
	void activate(Hero* hero);
};

#endif
