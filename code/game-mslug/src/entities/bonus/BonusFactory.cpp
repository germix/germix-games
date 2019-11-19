////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusFactory | Factoría de bonus
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/BonusFactory.h>
#include <src/entities/bonus/Bonus_Bombs.h>
#include <src/entities/bonus/Bonus_WeaponH.h>
#include <src/entities/bonus/Bonus_WeaponR.h>
#include <src/entities/bonus/Bonus_WeaponS.h>
#include <src/entities/bonus/Bonus_Coin.h>
#include <src/entities/bonus/Bonus_Medal.h>
#include <src/entities/bonus/Bonus_Treasure.h>
#include <src/entities/bonus/Bonus_JewelRed.h>
#include <src/entities/bonus/Bonus_JewelBlue.h>
#include <src/entities/bonus/Bonus_JewelYellow.h>
#include <src/entities/bonus/Bonus_Pig.h>
#include <src/entities/bonus/Bonus_Cat.h>
#include <src/entities/bonus/Bonus_Fish.h>
#include <src/entities/bonus/Bonus_Frog.h>
#include <src/entities/bonus/Bonus_Monkey.h>
#include <src/entities/bonus/Bonus_Chicken.h>
#include <src/entities/bonus/Bonus_Poop.h>
#include <src/entities/bonus/Bonus_Letter.h>
#include <src/entities/bonus/Bonus_Doll.h>
#include <src/entities/bonus/Bonus_Teddy.h>
#include <src/entities/bonus/Bonus_Fungus.h>
#include <src/entities/bonus/Bonus_Banana.h>

#include <string.h>

const char* BonusFactory::bonus[] =
{
	Bonus_Bombs::NAME,
	Bonus_WeaponH::NAME,
	Bonus_WeaponR::NAME,
	Bonus_WeaponS::NAME,
	Bonus_Coin::NAME,
	Bonus_Medal::NAME,
	Bonus_Treasure::NAME,
	Bonus_JewelRed::NAME,
	Bonus_JewelBlue::NAME,
	Bonus_JewelYellow::NAME,
	Bonus_Pig::NAME,
	Bonus_Cat::NAME,
	Bonus_Fish::NAME,
	Bonus_Frog::NAME,
	Bonus_Monkey::NAME,
	Bonus_Chicken::NAME,
	Bonus_Poop::NAME,
	Bonus_Letter::NAME,
	Bonus_Doll::NAME,
	Bonus_Teddy::NAME,
	Bonus_Fungus::NAME,
	Bonus_Banana::NAME,
};
const int BonusFactory::bonusLength = (sizeof(bonus)/sizeof(bonus[0]));

Bonus* BonusFactory::create(Scene* scene, double px, double py, const char* name)
{
	if(0 == strcmp(name, Bonus_Bombs::NAME))				return new Bonus_Bombs(scene, px, py);
	else if(0 == strcmp(name, Bonus_WeaponH::NAME))			return new Bonus_WeaponH(scene, px, py);
	else if(0 == strcmp(name, Bonus_WeaponR::NAME))			return new Bonus_WeaponR(scene, px, py);
	else if(0 == strcmp(name, Bonus_WeaponS::NAME))			return new Bonus_WeaponS(scene, px, py);
	else if(0 == strcmp(name, Bonus_Coin::NAME))			return new Bonus_Coin(scene, px, py);
	else if(0 == strcmp(name, Bonus_Medal::NAME))			return new Bonus_Medal(scene, px, py);
	else if(0 == strcmp(name, Bonus_Treasure::NAME))		return new Bonus_Treasure(scene, px, py);
	else if(0 == strcmp(name, Bonus_JewelRed::NAME))		return new Bonus_JewelRed(scene, px, py);
	else if(0 == strcmp(name, Bonus_JewelBlue::NAME))		return new Bonus_JewelBlue(scene, px, py);
	else if(0 == strcmp(name, Bonus_JewelYellow::NAME))		return new Bonus_JewelYellow(scene, px, py);
	else if(0 == strcmp(name, Bonus_Pig::NAME))				return new Bonus_Pig(scene, px, py);
	else if(0 == strcmp(name, Bonus_Cat::NAME))				return new Bonus_Cat(scene, px, py);
	else if(0 == strcmp(name, Bonus_Fish::NAME))			return new Bonus_Fish(scene, px, py);
	else if(0 == strcmp(name, Bonus_Monkey::NAME))			return new Bonus_Monkey(scene, px, py);
	else if(0 == strcmp(name, Bonus_Chicken::NAME))			return new Bonus_Chicken(scene, px, py);
	else if(0 == strcmp(name, Bonus_Poop::NAME))			return new Bonus_Poop(scene, px, py);
	else if(0 == strcmp(name, Bonus_Letter::NAME))			return new Bonus_Letter(scene, px, py);
	else if(0 == strcmp(name, Bonus_Doll::NAME))			return new Bonus_Doll(scene, px, py);
	else if(0 == strcmp(name, Bonus_Teddy::NAME))			return new Bonus_Teddy(scene, px, py);
	else if(0 == strcmp(name, Bonus_Fungus::NAME))			return new Bonus_Fungus(scene, px, py);
	else if(0 == strcmp(name, Bonus_Banana::NAME))			return new Bonus_Banana(scene, px, py);
	else if(0 == strcmp(name, Bonus_Frog::NAME))			return new Bonus_Frog(scene, px, py);
	return null;
}
