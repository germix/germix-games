////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AircraftBehavior_VerticalS
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___AircraftBehavior_VerticalS_h___
#define ___AircraftBehavior_VerticalS_h___
#include <src/entities/enemies/aircrafts/behaviors/AircraftBehavior.h>

#include <gamelib/TimeClock.h>

class AircraftBehavior_VerticalS : public AircraftBehavior
{
	enum STATE
	{
		STATE_ADVANCE_1,
		STATE_DECELERATION_1,
		STATE_ACCELERATION_1,
		STATE_INVERT_ADVANCE,
		STATE_DECELERATION_2,
		STATE_ACCELERATION_2,
		STATE_ADVANCE_2,
	};
	STATE			state;
	
	TimeClock		clock;
	
	double			velocity;
	double			maxVelocity;
	int				milestone1;
	int				milestone2;
public:
	AircraftBehavior_VerticalS(int velocity);
	~AircraftBehavior_VerticalS();
public:
	void update(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex);
	int  getLevel() const;
	bool isRemovable() const;
};

#endif
