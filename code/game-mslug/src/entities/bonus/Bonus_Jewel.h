////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Jewel | Bonus joya
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Jewel_h___
#define ___Bonus_Jewel_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_Jewel : public Bonus
{
public:
	Bonus_Jewel(Scene* scene, double x, double y, const char* s);
	~Bonus_Jewel();
protected:
	void animate(double dt);
	void activate(Hero* hero);
};

#endif
