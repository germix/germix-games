////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Fruit
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Fruit_h___
#define ___Bonus_Fruit_h___
#include <src/entities/Bonus.h>

#include <gamelib/TimeClock.h>

class Bonus_Fruit : public Bonus
{
	TimeClock clock;
	int state;
	int blinkCount;
public:
	Bonus_Fruit(Scene* s, double x, double y, double dx, double dy, Texture* texture);
	~Bonus_Fruit();
public:
	void update(double dt);
	void render(Graphics* gr);
};


#endif
