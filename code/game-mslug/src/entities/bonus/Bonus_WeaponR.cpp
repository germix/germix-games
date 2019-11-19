////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_WeaponR | Bonus que entrega una arma RocketLauncher
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_WeaponR.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/Weapon.h>
#include <src/entities/effects/BonusEffect.h>

#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Bonus_WeaponR::NAME = "Weapon(R)";

Bonus_WeaponR::Bonus_WeaponR(Scene* scene, double x, double y) : Bonus(scene, x, y)
{
	sprite = res.findSpriteSheet("Bonus.Weapon")->getSprite();
	spriteFrame = 2;
}
Bonus_WeaponR::~Bonus_WeaponR()
{
}
void Bonus_WeaponR::activate(Hero* hero)
{
	hero->setWeapon(WEAPON_ROCKET_LAUNCHER);
	Mixer::playChannel(res.findSound("Bonus.Weapon.R"));
	Rectanglef r = bounds();
	scene->addEntity(new BonusEffect(scene, r.getCenterX(), r.getCenterY()));
}

