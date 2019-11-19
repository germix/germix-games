////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RocketLauncher
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/weapons/RocketLauncher.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/weapons/RocketLauncherBullet.h>

#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define ANIMATION_TIME		0.060

static const int indexedFramesRocketLauncherCrouched[] = {0,1,2,3,4,3,2,1};
#define indexedFramesRocketLauncherCrouched_length (sizeof(indexedFramesRocketLauncherCrouched)/sizeof(indexedFramesRocketLauncherCrouched[0]))

RocketLauncher::RocketLauncher()
: ready(true)
, animIndex(0)
, shootSound(null)
, spriteRocketLauncher0(null)
, spriteRocketLauncher90(null)
, spriteRocketLauncherDown(null)
, spriteRocketLauncherCrouched(null)
{
	shootSound = res.findSound("Shoot.Weapon.R");
}
int         RocketLauncher::type() const
{
	return 2;
}
const char* RocketLauncher::name() const
{
	return "Rocket Launcher";
}
int         RocketLauncher::getAmmo(bool firstTime) const
{
	return (firstTime ? 30 : 15);
}
bool        RocketLauncher::canChangeAngleWhileShooting() const
{
	return false;
}
void        RocketLauncher::reset(SpriteSheet* sheet)
{
	spriteRocketLauncher0 = sheet->getSprite("thorax(R)-shoot(0)");
	spriteRocketLauncher90 = sheet->getSprite("thorax(R)-shoot(90)");
	spriteRocketLauncherDown = sheet->getSprite("thorax(R)-shoot(down)");
	spriteRocketLauncherCrouched = sheet->getSprite("crouched(R)-shoot");
}
int         RocketLauncher::update(Scene* scene, Hero* hero, double dt, double posX, double posY, int lookX, int shotAngle, int ammo)
{
	if(shooting && shootingClock.update(dt))
	{
		if(animIndex == 2)
			ready = true;
		if(hero->isCrouching())
		{
			if(++animIndex >= indexedFramesRocketLauncherCrouched_length)
			{
				ready = true;
				shooting = false;
				animIndex = 0;
			}
			spriteFrame = indexedFramesRocketLauncherCrouched[animIndex];
		}
		else
		{
			if(++animIndex >= sprite->count())
			{
				ready = true;
				shooting = false;
				animIndex = 0;
			}
			spriteFrame = animIndex;
		}
	}
	return ammo;
}
int         RocketLauncher::trigger(Scene* scene, Hero* hero, double posX, double posY, int lookX, int shotAngle, int ammo)
{
	if(ammo > 0 && ready && checkAngle(shotAngle) && checkSprite(hero, shotAngle))
	{
		//
		// Disparar
		//
		ammo--;
		Point shotPoint = sprite->point("shoot", posX, posY, spriteFrame, (lookX == -1) ? Sprite::FLIP_X : 0);
		scene->addEntity(new RocketLauncherBullet(
				scene,
				shotPoint.x,
				shotPoint.y,
				shotAngle,
				lookX));
		if(shootSound != null)
		{
			Mixer::playChannel(shootSound);
		}
		//
		// ...
		//
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
bool                RocketLauncher::checkAngle(int shotAngle)
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
bool                RocketLauncher::checkSprite(Hero* hero, int shotAngle)
{
	if(hero->isCrouching())
	{
		sprite = spriteRocketLauncherCrouched;
	}
	else if(shotAngle == 0)
	{
		sprite = spriteRocketLauncher0;
	}
	else if(shotAngle == 90)
	{
		sprite = spriteRocketLauncher90;
	}
	else if(shotAngle == -90)
	{
		sprite = spriteRocketLauncherDown;
	}
	else
	{
		return false;
	}
	return true;
}

