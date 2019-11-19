////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AircraftBehavior_Patrol
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/aircrafts/behaviors/AircraftBehavior_Patrol.h>
#include <src/Utils.h>
#include <src/sprites/Sprite.h>
#include <src/entities/enemies/aircrafts/AircraftPath.h>

AircraftBehavior_Patrol::AircraftBehavior_Patrol(AircraftPath* ___path, double pathStart, double ___velocity)
: path(___path)
, traveled(pathStart)
, velocity(___velocity)
{
	path->ref();
}
AircraftBehavior_Patrol::~AircraftBehavior_Patrol()
{
	path->unref();
}
void AircraftBehavior_Patrol::update(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex)
{
	AircraftPath::MOVE_DATA* data;
	
	// ...
	traveled += (velocity*dt);
	// ...
	if(null != (data = path->getDataFromDistance(traveled)))
	{
		pos = data->pos;
		spriteIndex = Utils::spriteFromAngle(data->angle, 16);
		delete data;
	}
}
int  AircraftBehavior_Patrol::getLevel() const
{
	return 0;
}
bool AircraftBehavior_Patrol::isRemovable() const
{
	return true;
}
