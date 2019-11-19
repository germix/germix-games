////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BossBattleship
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/battleships/BossBattleship.h>
#include <src/Config.h>

#include <mach/Math.h>
#include <mach/Texture.h>

double BossBattleship::ZigZag::update(double dt, double velocity)
{
	value += velocity * dt;
	if(value > length)
	{
		value = 0;
	}
	double angle = -Math::PI + (value * (Math::PI * 2)) / length;
	double offset = (Math::cos(angle)*(length));
	
	return offset;
}

BossBattleship::BossBattleship(Scene* s, double x, double y, const std::string& fname) : Battleship(s, x, y, fname)
, zigZag()
, referenceX(SCENE_WIDTH/2)
, initialHealth(0)
{
	zigZag.init(SCENE_WIDTH/2 - texture->getWidth()/2 - 20);
	initialHealth = getHealth();
}
BossBattleship::~BossBattleship()
{
}
void BossBattleship::update(double dt)
{
	if(isAlive())
	{
		double vVelocity = 25;			// Velocidad de movimiento vertical
		double hVelocity = 12;			// Velocidad de movimiento horizondal

		pos.y += (vVelocity*dt);
		pos.x = referenceX + zigZag.update(dt, hVelocity);
	}
	else
	{
		double vVelocity = 18;			// Velocidad de movimiento vertical
		double hVelocity = 2;			// Velocidad de movimiento horizondal

		pos.y += (vVelocity*dt);
		pos.x = referenceX + zigZag.update(dt, hVelocity);
	}
	updateComponents(dt);
}
int BossBattleship::getDestroyedPercent() const
{
	return (int)((100.0/(double)initialHealth)*(double)(initialHealth - getHealth()));
}
