////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AircraftBehavior_VerticalS
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/aircrafts/behaviors/AircraftBehavior_VerticalS.h>
#include <src/sprites/Sprite.h>

#include <mach/Vector2f.h>

AircraftBehavior_VerticalS::AircraftBehavior_VerticalS(int velocity)
: state(STATE_ADVANCE_1)
, clock()
, velocity(170)
, maxVelocity(170)
, milestone1(150)
, milestone2(70)
{
}
AircraftBehavior_VerticalS::~AircraftBehavior_VerticalS()
{
}
void AircraftBehavior_VerticalS::update(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex)
{
	switch(state)
	{
		case STATE_ADVANCE_1:
			if(pos.x > milestone1)
			{
				state = STATE_DECELERATION_1;
				clock.reset(0.5);
				if((spriteIndex+1) < sprite->count)
				{
					spriteIndex++;
				}
			}
			else
			{
				pos.x += (velocity*dt);
			}
			break;
		case STATE_DECELERATION_1:
			if(clock.update(dt))
			{
				state = STATE_ACCELERATION_1;
				clock.reset(0.5);
			}
			else
			{
				double dv = maxVelocity*clock.time();
			
				if(dv > (maxVelocity)/2/2)
				{
					spriteIndex = 2;
				}
				velocity = maxVelocity - dv;
				if(velocity < 0)
					velocity = 0;
				
				pos.x += velocity*dt;
			}
			break;
		case STATE_ACCELERATION_1:
			if(clock.update(dt))
			{
				state = STATE_INVERT_ADVANCE;
				velocity = maxVelocity;
			}
			else
			{
				double dv = maxVelocity*clock.time();
				
				if(dv > (maxVelocity)/2/2)
				{
					spriteIndex = 4;
				}
				velocity = dv;
				if(velocity > maxVelocity)
					velocity = maxVelocity;
				
				pos.x -= velocity*dt;
			}
			break;
		case STATE_INVERT_ADVANCE:
			if(pos.x < milestone2)
			{
				state = STATE_DECELERATION_2;
				clock.reset(0.5);
				if((spriteIndex+1) < sprite->count)
				{
					spriteIndex++;
				}
			}
			else
			{
				pos.x -= (velocity*dt);
			}
			break;
		case STATE_DECELERATION_2:
			if(clock.update(dt))
			{
				state = STATE_ACCELERATION_2;
				clock.reset(0.5);
			}
			else
			{
				double dv = maxVelocity*clock.time();
			
				if(dv > (maxVelocity)/2/2)
				{
					spriteIndex = 6;
				}
				velocity = maxVelocity - dv;
				if(velocity < 0)
					velocity = 0;
				
				pos.x -= velocity*dt;
			}
			break;
		case STATE_ACCELERATION_2:
			if(clock.update(dt))
			{
				state = STATE_ADVANCE_2;
				velocity = maxVelocity;
				if((spriteIndex+1) < sprite->count)
				{
					spriteIndex++;
				}
			}
			else
			{
				double dv = maxVelocity*clock.time();
				
				if(dv > (maxVelocity)/2/2)
				{
					spriteIndex = 7;
				}
				velocity = dv;
				if(velocity > maxVelocity)
					velocity = maxVelocity;
				
				pos.x += velocity*dt;
			}
			break;
		case STATE_ADVANCE_2:
			pos.x += (velocity*dt);
			break;
	}
}
int  AircraftBehavior_VerticalS::getLevel() const
{
	return 0;
}
bool AircraftBehavior_VerticalS::isRemovable() const
{
	return true;
}

