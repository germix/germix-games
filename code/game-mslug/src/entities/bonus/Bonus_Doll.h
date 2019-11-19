////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Doll | Bonus muñeca
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Doll_h___
#define ___Bonus_Doll_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_Doll : public Bonus
{
public:
	static const char* NAME;
public:
	Bonus_Doll(Scene* scene, double x, double y);
	~Bonus_Doll();
protected:
	void animate(double dt);
	void activate(Hero* hero);
};

#endif
