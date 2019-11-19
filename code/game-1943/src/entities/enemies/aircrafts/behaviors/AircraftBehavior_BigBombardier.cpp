////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AircraftBehavior_BigBombardier
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/aircrafts/behaviors/AircraftBehavior_BigBombardier.h>

#include <mach/Math.h>
#include <mach/Vector2f.h>

AircraftBehavior_BigBombardier::AircraftBehavior_BigBombardier(Scene* scene, int ___velocity, int ___enteringLimit, int ___horizontalMovementLength)
: state(STATE_NONE)
, velocity(___velocity)

, enteringLimit(___enteringLimit)

, referenceY(0)

, verticalMovementLength(70)

, horizontalMovementLength(___horizontalMovementLength)
, horizontalMovementOffset(0)
, horizontalMovementDirection(1.0)

, airLevel(-3)
, riseTime(0.3)
{
}
AircraftBehavior_BigBombardier::~AircraftBehavior_BigBombardier()
{
}
void AircraftBehavior_BigBombardier::update(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex)
{
	switch(state)
	{
		case STATE_NONE:
			state = STATE_ENTERING;
			break;
		case STATE_ENTERING:
			pos.y -= velocity * dt;
			if(pos.y < enteringLimit)
			{
				state = STATE_RISE;
			}
			break;
		case STATE_RISE:
			pos.y -= velocity * dt;
			if(riseTime.update(dt))
			{
				airLevel++;
				++spriteIndex;
				if(spriteIndex == 3)
				{
					spriteIndex = 5;
					state = STATE_MOVEMENT_HORZ;
					referenceY = pos.y;
				}
			}
			break;
		case STATE_MOVEMENT_HORZ:
			{
				double vOffset = -Math::PI + (horizontalMovementOffset * (Math::PI * 2)) / horizontalMovementLength;

				pos.y = referenceY + Math::sin(vOffset) * 10;
				pos.x += (velocity * dt) * horizontalMovementDirection;
				horizontalMovementOffset += velocity * dt;
				if(horizontalMovementOffset > horizontalMovementLength)
				{
					state = STATE_MOVEMENT_VERT;
					horizontalMovementOffset = 0;
					horizontalMovementDirection *= -1;
				}
			}
			break;
		case STATE_MOVEMENT_VERT:
			{
				pos.y -= velocity * dt;
				if((referenceY - pos.y) > verticalMovementLength)
				{
					state = STATE_MOVEMENT_HORZ;
					referenceY = pos.y;
				}
			}
			break;
		case STATE_OUTSIDE:
			break;
	}
}
int  AircraftBehavior_BigBombardier::getLevel() const
{
	return airLevel;
}
bool AircraftBehavior_BigBombardier::isRemovable() const
{
	return true;
}
