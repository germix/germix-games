////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AircraftBehavior_Kamikaze
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___AircraftBehavior_Kamikaze_h___
#define ___AircraftBehavior_Kamikaze_h___
#include <src/entities/enemies/aircrafts/behaviors/AircraftBehavior.h>

class Scene;

class AircraftBehavior_Kamikaze : public AircraftBehavior
{
	Scene*		scene;
	double		velocity;
public:
	AircraftBehavior_Kamikaze(Scene* scene, double velocity);
	~AircraftBehavior_Kamikaze();
public:
	void update(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex);
	int  getLevel() const;
	bool isRemovable() const;
};

#endif
