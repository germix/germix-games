////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Fruit
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Fruit.h>

Bonus_Fruit::Bonus_Fruit(Scene* s, double x, double y, double dx, double dy, Texture* texture) : Bonus(s, x, y, dx, dy, texture)
{
	clock.reset(3.2);
	state = 0;
	blinkCount = 0;
}
Bonus_Fruit::~Bonus_Fruit()
{
}
void Bonus_Fruit::update(double dt)
{
	if(state == 0)
	{
		if(clock.update(dt))
		{
			state = 1;
			clock.reset(0.07);
		}
	}
	else
	{
		if(clock.update(dt))
		{
			blinkCount++;
			if(blinkCount == 16)
			{
				removable = true;
			}
		}
	}
}
void Bonus_Fruit::render(Graphics* gr)
{
	if(!(blinkCount&1))
	{
		Bonus::render(gr);
	}
}

