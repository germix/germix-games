////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AircraftBehavior_Kamikaze
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/aircrafts/behaviors/AircraftBehavior_Kamikaze.h>
#include <src/Utils.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>

#include <mach/Math.h>
#include <mach/Vector2f.h>

AircraftBehavior_Kamikaze::AircraftBehavior_Kamikaze(Scene* ___scene, double ___velocity)
: scene(___scene)
, velocity(___velocity)
{
}
AircraftBehavior_Kamikaze::~AircraftBehavior_Kamikaze()
{
}
void AircraftBehavior_Kamikaze::update(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex)
{
	Hero* hero = scene->getHero();
	if(hero->isAlive())
	{
		Vector2f sp = pos;
		Vector2f ep = hero->position();
		double dx = (ep.x-sp.x);
		double dy = (ep.y-sp.y);
		double angle = Math::atan2(dy, dx);
		double length = Math::sqrt((dx*dx)+(dy*dy));
		
		if(length > 8)
		{
			Utils::move(pos, angle, velocity*dt);
			spriteIndex = Utils::spriteFromAngle(angle, 16);
		}
	}
	else
	{
		// TODO Mover el avion fuera de la pantalla
	}
}
int  AircraftBehavior_Kamikaze::getLevel() const
{
	return 0;
}
bool AircraftBehavior_Kamikaze::isRemovable() const
{
	return true;
}
