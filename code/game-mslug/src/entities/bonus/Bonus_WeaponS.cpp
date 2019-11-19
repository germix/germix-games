////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_WeaponS | Bonus que entrega una arma Shotgun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_WeaponS.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/Weapon.h>
#include <src/entities/effects/BonusEffect.h>

#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Bonus_WeaponS::NAME = "Weapon(S)";

Bonus_WeaponS::Bonus_WeaponS(Scene* scene, double x, double y) : Bonus(scene, x, y)
{
	sprite = res.findSpriteSheet("Bonus.Weapon")->getSprite();
	spriteFrame = 1;
}
Bonus_WeaponS::~Bonus_WeaponS()
{
}
void Bonus_WeaponS::activate(Hero* hero)
{
	hero->setWeapon(WEAPON_SHOT_GUN);
	Mixer::playChannel(res.findSound("Bonus.Weapon.S"));
	Rectanglef r = bounds();
	scene->addEntity(new BonusEffect(scene, r.getCenterX(), r.getCenterY()));
}

