////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugHiddenBonusScreen
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___DebugHiddenBonusScreen_h___
#define ___DebugHiddenBonusScreen_h___
#include <src/screens/debug/DebugPlayingScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/bonus/HiddenBonus.h>
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

#include <mach/Graphics.h>
#include <mach/Keyboard.h>

#include <gamelib/Font.h>

class DebugHiddenBonusScreen : public DebugPlayingScreen
{
public:
	DebugHiddenBonusScreen()
	{
	}
	~DebugHiddenBonusScreen() {}
public:
	void show(Machine* mach)
	{
		DebugPlayingScreen::show(mach);
		scene->setRightLimit(SCREEN_WIDTH+30);

		scene->addEntity(new HiddenBonus(scene, 100, 90, 5, Bonus_Pig::NAME));
		scene->addEntity(new HiddenBonus(scene, 150, 10, 3, Bonus_Monkey::NAME));
		scene->addEntity(new HiddenBonus(scene, 190, 165, 1, Bonus_Bombs::NAME));
		scene->addEntity(new HiddenBonus(scene, 200, 100, 7, Bonus_WeaponH::NAME));
		scene->addEntity(new HiddenBonus(scene, 50, 165, 3, Bonus_Banana::NAME));
		scene->addEntity(new HiddenBonus(scene, 230, 165, 3, Bonus_Treasure::NAME));
	}
};

#endif
