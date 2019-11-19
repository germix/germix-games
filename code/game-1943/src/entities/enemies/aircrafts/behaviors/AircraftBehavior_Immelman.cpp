////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AircraftBehavior_Immelman
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/aircrafts/behaviors/AircraftBehavior_Immelman.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/sprites/Sprite.h>

#include <mach/Math.h>
#include <mach/Vector2f.h>

AircraftBehavior_Immelman::AircraftBehavior_Immelman(Scene* ___scene, double ___velocity)
: scene(___scene)
, state(STATE_NORMAL_ADVANCE)
, angle(Math::toRadians(90.0))
, velocity(___velocity)
, maxVelocity(___velocity)
, timeElapsed(0)
, removable(false)
{
}
AircraftBehavior_Immelman::~AircraftBehavior_Immelman()
{
}
void AircraftBehavior_Immelman::update(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex)
{
	switch(state)
	{
		case STATE_NORMAL_ADVANCE:
			updateForNormalAdvance(pos, dt, sprite, spriteIndex);
			break;
		case STATE_PITCH_DECELERATION:
			updateForPitchDeceleration(pos, dt, sprite, spriteIndex);
			break;
		case STATE_PITCH_ACCELERATION:
			updateForPitchAcceleration(pos, dt, sprite, spriteIndex);
			break;
		case STATE_INVERT_RETURN:
			updateForInvertReturn(pos, dt, sprite, spriteIndex);
			break;
		case STATE_ROLL_RETURN:
			updateForRollReturn(pos, dt, sprite, spriteIndex);
			break;
		case STATE_NORMAL_RETURN:
			updateForNormalReturn(pos, dt, sprite, spriteIndex);
			break;
	}
}
int  AircraftBehavior_Immelman::getLevel() const
{
	return 0;
}
bool AircraftBehavior_Immelman::isRemovable() const
{
	return removable;
}
void AircraftBehavior_Immelman::move(Vector2f& pos, double len)
{
	pos.x += (Math::cos(angle)*len);
	pos.y += (Math::sin(angle)*len);
}
void AircraftBehavior_Immelman::updateForNormalAdvance(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex)
{
	move(pos, maxVelocity*dt);
	Hero* hero = scene->getHero();
	if(hero != null && hero->isAlive())
	{
		if(scene->getHero()->rect().getMinY() < sprite->rect(pos).getMaxY()+16)
		{
			state = STATE_PITCH_DECELERATION;
			if(++spriteIndex >= sprite->count)
			{
				spriteIndex = 0;
			}
			timeElapsed = 0;
		}
	}
}
void AircraftBehavior_Immelman::updateForPitchDeceleration(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex)
{
	timeElapsed += dt;
	if(timeElapsed > 0.5)
	{
		state = STATE_PITCH_ACCELERATION;
		timeElapsed -= 0.5;
		angle = Math::toRadians(360.0-90.0);
	}
	else
	{
		double dv = maxVelocity*timeElapsed;
		
		if(dv > (maxVelocity)/2/2)
		{
			spriteIndex = 2;
		}
		velocity = maxVelocity - dv;
		if(velocity < 0)
			velocity = 0;
		move(pos, velocity*dt);
	}
}
void AircraftBehavior_Immelman::updateForPitchAcceleration(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex)
{
	timeElapsed += dt;
	if(timeElapsed > 0.5)
	{
		state = STATE_INVERT_RETURN;
		timeElapsed -= 0.5;
		angle = Math::toRadians(360.0-90.0);
	}
	else
	{
		double dv = maxVelocity*timeElapsed;
		
		if(dv > (maxVelocity)/2/2)
		{
			spriteIndex = 4;
		}
		velocity = dv;
		if(velocity > maxVelocity)
			velocity = maxVelocity;
		
		move(pos, velocity*dt);
	}
}
void AircraftBehavior_Immelman::updateForInvertReturn(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex)
{
	timeElapsed += dt;
	if(timeElapsed > 1.0)	// Un segundo
	{
		state = STATE_ROLL_RETURN;
		timeElapsed = 0;
	}
	else
	{
		move(pos, maxVelocity*dt);
	}
}
void AircraftBehavior_Immelman::updateForRollReturn(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex)
{
	timeElapsed += dt;
	if(timeElapsed > 0.1)
	{
		timeElapsed -= 0.1;
		if((spriteIndex+1) < sprite->count)
		{
			if(++spriteIndex == 8)
			{
				state = STATE_NORMAL_RETURN;
			}
		}
	}
	move(pos, maxVelocity*dt);
}
void AircraftBehavior_Immelman::updateForNormalReturn(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex)
{
	move(pos, maxVelocity*dt);
	
	if(pos.y < 0)
	{
		removable = true;		// Puede ser removido una vez que comienza a retornar
	}
}

