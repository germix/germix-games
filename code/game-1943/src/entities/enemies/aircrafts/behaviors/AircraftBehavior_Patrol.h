////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AircraftBehavior_Patrol
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___AircraftBehavior_Patrol_h___
#define ___AircraftBehavior_Patrol_h___
#include <src/entities/enemies/aircrafts/behaviors/AircraftBehavior.h>

class AircraftPath;

class AircraftBehavior_Patrol : public AircraftBehavior
{
	AircraftPath*		path;
	double				traveled;
	double				velocity;
public:
	AircraftBehavior_Patrol(AircraftPath* path, double pathStart, double velocity = 150.0);
	~AircraftBehavior_Patrol();
public:
	void update(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex);
	int  getLevel() const;
	bool isRemovable() const;
};

#endif
