////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugBonusScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___DebugBonusScreen_h___
#define ___DebugBonusScreen_h___
#include <src/screens/debug/DebugPlayingScreen.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/friendly/Hostage.h>
#include <src/entities/bonus/BonusBox.h>
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

#include <mach/Graphics.h>
#include <mach/Keyboard.h>

#include <gamelib/Font.h>

class DebugBonusScreen : public DebugPlayingScreen
{
	Font*			font;
	int				currentBonus;
public:
	DebugBonusScreen()
		: font(null)
		, currentBonus(0)
	{
	}
	~DebugBonusScreen() {}
public:
	void show(Machine* mach)
	{
		DebugPlayingScreen::show(mach);
		scene->setRightLimit(SCREEN_WIDTH+30);

		font = res.findFont("Font.8x8.1");
	}
	void update(Machine* mach, double dt)
	{
		DebugPlayingScreen::update(mach, dt);
		if(Keyboard::isPressed(Key::KP_PLUS))
		{
			if(++currentBonus >= BonusFactory::bonusLength)
			{
				currentBonus = 0;
			}
		}
		else if(Keyboard::isPressed(Key::KP_MINUS))
		{
			if(--currentBonus < 0)
			{
				currentBonus = BonusFactory::bonusLength-1;
			}
		}
		else if(Keyboard::isPressed(Key::LETTER_B))
		{
			scene->addEntity(new BonusBox(scene, getDropPos(), 0, getDropBonus()));
		}
		else if(Keyboard::isPressed(Key::LETTER_H))
		{
			scene->addEntity(new Hostage(scene, getDropPos(), 0, getDropBonus()));
		}
		else if(Keyboard::isPressed(Key::SPACE))
		{
			scene->addEntity(BonusFactory::create(scene, getDropPos(), 0, getDropBonus()));
		}
	}
	void render(Machine* mach, Graphics* gr)
	{
		DebugPlayingScreen::render(mach, gr);
		gr->fillRect(0, 0, SCREEN_WIDTH, 8+(2*2), Color(18, 28, 20));
		font->render(gr, 0+2, 0+2, "Bonus: ");
		font->render(gr, 0+2 + 7*8, 0+2, getDropBonus());
	}
private:
	double getDropPos() const
	{
		double scrollX = scene->getCurrentScrollX();
		double heroX = scene->getHero()->getPosition().x - scrollX;
		double dropX = 0;
		
		if(heroX < SCREEN_WIDTH/2)
			dropX = heroX + 50;
		else
			dropX = heroX - 50;
		
		return scrollX+dropX;
	}
	const char* getDropBonus() const
	{
		return BonusFactory::bonus[currentBonus];
	}
};

#endif
