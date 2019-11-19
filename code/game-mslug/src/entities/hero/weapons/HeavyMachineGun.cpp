////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeavyMachineGun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/weapons/HeavyMachineGun.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/weapons/HeavyMachineGunBullet.h>

#include <mach/Math.h>
#include <mach/Random.h>
#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define VELOCITY			300.0
#define ANIMATION_TIME		0.056

static const int indexedFramesHeavyMachineGun[] = {0,1,0,1,2,3,2,3};
#define indexedFramesHeavyMachineGun_length (sizeof(indexedFramesHeavyMachineGun)/sizeof(indexedFramesHeavyMachineGun[0]))

HeavyMachineGun::HeavyMachineGun()
: shootSound(null)
, shootSoundChannel(-1)
, spriteHeavyMachineGun0(null)
, spriteHeavyMachineGun30(null)
, spriteHeavyMachineGun60(null)
, spriteHeavyMachineGun90(null)
, spriteHeavyMachineGunDown(null)
, spriteHeavyMachineGunCrouched(null)
, animIndex(0)
, prevAngle(0)
, currentAngle(0)
{
	shootSound = res.findSound("Shoot.Weapon.H");
}
int         HeavyMachineGun::type() const
{
		return 1;
}
const char* HeavyMachineGun::name() const
{
	return "Heavy Machine Gun";
}
int         HeavyMachineGun::getAmmo(bool firstTime) const
{
	return (firstTime ? 200 : 150);
}
bool        HeavyMachineGun::canChangeAngleWhileShooting() const
{
	return true;
}
void        HeavyMachineGun::reset(SpriteSheet* sheet)
{
	shooting = false;
	spriteHeavyMachineGun0 = sheet->getSprite("thorax(H)-shoot(0)");
	spriteHeavyMachineGun30 = sheet->getSprite("thorax(H)-shoot(30)");
	spriteHeavyMachineGun60 = sheet->getSprite("thorax(H)-shoot(60)");
	spriteHeavyMachineGun90 = sheet->getSprite("thorax(H)-shoot(90)");
	spriteHeavyMachineGunDown = sheet->getSprite("thorax(H)-shoot(down)");
	spriteHeavyMachineGunCrouched = sheet->getSprite("crouched(H)-shoot");
}
int         HeavyMachineGun::update(Scene* scene, Hero* hero, double dt, double posX, double posY, int lookX, int shotAngle, int ammo)
{
	if(shooting)
	{
		bool shootNow = false;
		
		if(checkSprite(hero, shotAngle))
		{
			prevAngle = currentAngle;
			currentAngle = shotAngle;
			// ...
			switch(currentAngle)
			{
				case 0:
				case 90:
				case -90:
					if(shootingClock.update(dt))
					{
						if(++animIndex >= indexedFramesHeavyMachineGun_length)
						{
							shooting = false;
							animIndex = 0;
						}
						if((animIndex%2 == 0))
							shootNow = true;
					}
					spriteFrame = indexedFramesHeavyMachineGun[animIndex];
					break;
				default:
					if(prevAngle <= currentAngle)
						spriteFrame = 0;
					else
						spriteFrame = 1;
					
					if(((prevAngle/22)*22) != ((currentAngle/22)*22))
					{
						shootNow = true;
					}
					break;
			}
			//
			// Disparar
			//
			if(shootNow && ammo > 0)
			{
				ammo--;
				shoot(scene, posX, posY + Random().nextInt(16) - 8, lookX, shotAngle);
			}
		}
	}
	return ammo;
}
int         HeavyMachineGun::trigger(Scene* scene, Hero* hero, double posX, double posY, int lookX, int shotAngle, int ammo)
{
	if(ammo > 0 && checkSprite(hero, shotAngle))
	{
		prevAngle = shotAngle;
		currentAngle = shotAngle;
		
		//
		// Disparar
		//
		ammo--;
		shoot(scene, posX, posY, lookX, shotAngle);
		if(shootSound)
		{
			Mixer::haltChannel(shootSoundChannel);
			shootSoundChannel = Mixer::playChannel(shootSound);
		}
		//
		// ...
		//
		shooting = true;
		// ....
		animIndex = 0;
		spriteFrame = 0;
		shootingClock.reset(ANIMATION_TIME);
	}
	return ammo;
}
bool                HeavyMachineGun::checkSprite(Hero* hero, int shotAngle)
{
	if(hero->isCrouching())
	{
		sprite = spriteHeavyMachineGunCrouched;
	}
	else
	{
		if(shotAngle == 0)
		{
			sprite = spriteHeavyMachineGun0;
		}
		else if(shotAngle > 0 && shotAngle < 30)
		{
			sprite = spriteHeavyMachineGun30;
		}
		else if(shotAngle >= 30 && shotAngle < 90)
		{
			sprite = spriteHeavyMachineGun60;
		}
		else if(shotAngle == 90)
		{
			sprite = spriteHeavyMachineGun90;
		}
		else if(shotAngle == -90)
		{
			sprite = spriteHeavyMachineGunDown;
		}
		else
		{
			printf("Ángulo no válido=%d", shotAngle);
		}
	}
	return (sprite != null);
}
void                HeavyMachineGun::shoot(Scene* scene, double posX, double posY, int lookX, int shotAngle)
{
	Point shotPoint = sprite->point("shoot", posX, posY, spriteFrame, (lookX ==-1) ? Sprite::FLIP_X : 0);
	double rad = Math::toRadians((double)shotAngle);
	double dirX = Math::cos(rad)*lookX;
	double dirY = Math::sin(rad);
	double bulletAngle = Math::atan2(dirY, dirX);
	scene->addEntity(new HeavyMachineGunBullet(
			scene,
			shotPoint.x,
			shotPoint.y,
			Math::cos(bulletAngle)*VELOCITY,
			-Math::sin(bulletAngle)*VELOCITY,
			shotAngle));
}
