////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Fungus | Bonus hongo
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Fungus_h___
#define ___Bonus_Fungus_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_Fungus : public Bonus
{
public:
	static const char* NAME;
public:
	Bonus_Fungus(Scene* scene, double x, double y);
	~Bonus_Fungus();
protected:
	void animate(double dt);
	void activate(Hero* hero);
};

#endif
