////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_WeaponH | Bonus que entrega una arma HeavyMachineGun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_WeaponH.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/Weapon.h>
#include <src/entities/effects/BonusEffect.h>

#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Bonus_WeaponH::NAME = "Weapon(H)";

Bonus_WeaponH::Bonus_WeaponH(Scene* scene, double x, double y) : Bonus(scene, x, y)
{
	sprite = res.findSpriteSheet("Bonus.Weapon")->getSprite();
	spriteFrame = 0;
}
Bonus_WeaponH::~Bonus_WeaponH()
{
}
void Bonus_WeaponH::activate(Hero* hero)
{
	hero->setWeapon(WEAPON_HEAVY_MACHINE_GUN);
	Mixer::playChannel(res.findSound("Bonus.Weapon.H"));
	Rectanglef r = bounds();
	scene->addEntity(new BonusEffect(scene, r.getCenterX(), r.getCenterY()));
}


