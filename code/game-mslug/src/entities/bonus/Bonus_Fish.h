////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Fish | Bonus pescado
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Fish_h___
#define ___Bonus_Fish_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_Fish : public Bonus
{
public:
	static const char* NAME;
public:
	Bonus_Fish(Scene* scene, double x, double y);
	~Bonus_Fish();
protected:
	void animate(double dt);
	void activate(Hero* hero);
};

#endif
