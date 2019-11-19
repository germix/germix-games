////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusManager
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/BonusManager.h>

#include <src/bonus/Bonus_Energy_POW.h>
#include <src/bonus/Bonus_Energy_Tank.h>
#include <src/bonus/Bonus_Energy_Yashichi.h>
#include <src/bonus/Bonus_SideFighter.h>
#include <src/bonus/Bonus_Star.h>
#include <src/bonus/Bonus_Weapon_3way.h>
#include <src/bonus/Bonus_Weapon_Auto.h>
#include <src/bonus/Bonus_Weapon_Laser.h>
#include <src/bonus/Bonus_Weapon_Shell.h>
#include <src/bonus/Bonus_Weapon_Shotgun.h>
static std::vector<Bonus*> bonus;

void BonusManager::init()
{
	bonus.push_back(new Bonus_Energy_POW());
	bonus.push_back(new Bonus_Energy_Tank());
	bonus.push_back(new Bonus_Energy_Yashichi());
	bonus.push_back(new Bonus_SideFighter());
	bonus.push_back(new Bonus_Star());
	bonus.push_back(new Bonus_Weapon_3way());
	bonus.push_back(new Bonus_Weapon_Auto());
	bonus.push_back(new Bonus_Weapon_Laser());
	bonus.push_back(new Bonus_Weapon_Shell());
	bonus.push_back(new Bonus_Weapon_Shotgun());
}
void BonusManager::clear()
{
	for(unsigned int i = 0; i < bonus.size(); i++)
	{
		delete bonus[i];
	}
	bonus.clear();
}
Bonus* BonusManager::findBonus(const String& name)
{
	for(unsigned int i = 0; i < bonus.size(); i++)
	{
		if(name == bonus[i]->name())
			return bonus[i];
	}
	return null;
}

