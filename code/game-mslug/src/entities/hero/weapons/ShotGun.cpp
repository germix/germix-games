////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ShotGun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/weapons/ShotGun.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/weapons/ShotGunExplosion.h>

#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define ANIMATION_TIME		0.03

ShotGun::ShotGun()
: ready(true)
, animIndex(0)
, shootSound(null)
, spriteShotGun0(null)
, spriteShotGun90(null)
, spriteShotGunDown(null)
, spriteShotGunCrouched(null)
{
	shootSound = res.findSound("Shoot.Weapon.S");
}
int         ShotGun::type() const
{
	return 2;
}
const char* ShotGun::name() const
{
	return "Shot Gun";
}
int         ShotGun::getAmmo(bool firstTime) const
{
	return (firstTime ? 30 : 10);
}
bool        ShotGun::canChangeAngleWhileShooting() const
{
	return false;
}
void        ShotGun::reset(SpriteSheet* sheet)
{
	spriteShotGun0 = sheet->getSprite("thorax(S)-shoot(0)");
	spriteShotGun90 = sheet->getSprite("thorax(S)-shoot(90)");
	spriteShotGunDown = sheet->getSprite("thorax(S)-shoot(down)");
	spriteShotGunCrouched = sheet->getSprite("crouched(S)-shoot");
}
int         ShotGun::update(Scene* scene, Hero* hero, double dt, double posX, double posY, int lookX, int shotAngle, int ammo)
{
	if(shooting && shootingClock.update(dt))
	{
		if(++animIndex >= sprite->count())
		{
			ready = true;
			
			shooting = false;
			animIndex = 0;
		}
	}
	spriteFrame = animIndex;
	
	return ammo;
}
int         ShotGun::trigger(Scene* scene, Hero* hero, double posX, double posY, int lookX, int shotAngle, int ammo)
{
	if(ammo > 0 && ready && checkAngle(shotAngle) && checkSprite(hero, shotAngle))
	{
		//
		// Disparar
		//
		ammo--;
		Point shotPoint = sprite->point("shoot", posX, posY, spriteFrame, (lookX ==-1) ? Sprite::FLIP_X : 0);
		scene->addEntity(new ShotGunExplosion(
				scene,
				shotPoint.x,
				shotPoint.y,
				shotAngle,
				lookX));
		if(shootSound != null)
		{
			Mixer::playChannel(shootSound);
		}
		ready = false;
		shooting = true;
		// ...
		shootingClock.reset(ANIMATION_TIME);
		//
		// Seleccionar frame
		//
		animIndex = 0;
		spriteFrame = 0;
	}
	return ammo;
}
bool                ShotGun::checkAngle(int shotAngle)
{
	switch(shotAngle)
	{
		case 0:
		case 90:
		case -90:
			return true;
	}
	return false;
}
bool                ShotGun::checkSprite(Hero* hero, int shotAngle)
{
	if(hero->isCrouching())
	{
		sprite = spriteShotGunCrouched;
	}
	else if(shotAngle == 0)
	{
		sprite = spriteShotGun0;
	}
	else if(shotAngle == 90)
	{
		sprite = spriteShotGun90;
	}
	else if(shotAngle == -90)
	{
		sprite = spriteShotGunDown;
	}
	else
	{
		return false;
	}
	return true;
}
