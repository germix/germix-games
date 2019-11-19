////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WeaponHandler
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/WeaponHandler.h>
#include <src/entities/hero/weapons/Weapon.h>
#include <src/ResourceManager.h>

#include <mach/Mixer.h>

WeaponHandler::WeaponHandler()
: weapon(null)
, strong(false)
, initialTime(0)
, triggerTime(0)
, delayTime(0)
, continuityTime(0)
, sound(res.findSound("shoot"))
{
}
WeaponHandler::~WeaponHandler()
{
	delete weapon;
}
bool WeaponHandler::trigger(Scene* scene, double x, double y, bool initialTrigger, double pressedTime, bool isReinforced)
{
	if(weapon != null)
	{
		bool shoot = false;
		
		if(initialTrigger)
		{
			shoot = true;
			initialTime = pressedTime;
			triggerTime = pressedTime;
		}
		else
		{
			if(continuityTime < 0)
			{
				if((pressedTime-triggerTime) > delayTime)
				{
					shoot = true;
					triggerTime = pressedTime;
				}
			}
			else
			{
				if((pressedTime-initialTime) < continuityTime)
				{
					if((pressedTime-triggerTime) > delayTime)
					{
						shoot = true;
						triggerTime = pressedTime;
					}
				}
			}
		}
		if(shoot)
		{
			Mixer::playChannel(sound);
			weapon->shoot(scene, x, y, strong, isReinforced);
		}
		return true;
	}
	return false;
}
void WeaponHandler::setWeapon(Weapon* w)
{
	if(weapon)
		delete weapon;
	if(w == null)
	{
		weapon = null;
		strong = false;
		delayTime = 0;
		continuityTime = 0;
	}
	else
	{
		if(weapon == null)
		{
			strong = false;
		}
		else
		{
			if(weapon == w)
				strong = true;
			else
				strong = false;
		}
		weapon = w;
		delayTime = w->delay();
		continuityTime = w->continuity();
	}
}
