////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Pistol
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/weapons/Pistol.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/weapons/PistolBullet.h>

#include <mach/Math.h>
#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define VELOCITY			270
#define ANIMATION_TIME		0.078

Pistol::Pistol()
: animIndex(0)
, shootSound(null)
, spritePistol0(null)
, spritePistol90(null)
, spritePistolDown(null)
, spritePistolCrouched(null)
{
	shootSound = res.findSound("Shoot.Weapon.P");
}
int         Pistol::type() const
{
	return 0;
}
const char* Pistol::name() const
{
	return "Pistol";
}
int         Pistol::getAmmo(bool firstTime) const
{
	return -1;
}
bool        Pistol::canChangeAngleWhileShooting() const
{
	return true;// (animIndex >= 5);
}
void        Pistol::reset(SpriteSheet* sheet)
{
	spritePistol0 = sheet->getSprite("thorax(P)-shoot(0)");
	spritePistol90 = sheet->getSprite("thorax(P)-shoot(90)");
	spritePistolDown = sheet->getSprite("thorax(P)-shoot(down)");
	spritePistolCrouched = sheet->getSprite("crouched(P)-shoot");
}
int         Pistol::update(Scene* scene, Hero* hero, double dt, double posX, double posY, int lookX, int shotAngle, int ammo)
{
	if(shooting)
	{
		if(shootingClock.update(dt))
		{
			if(++animIndex >= sprite->count())
			{
				shooting = false;
				animIndex = 0;
			}
		}
		spriteFrame = animIndex;
	}
	return ammo;

}
int         Pistol::trigger(Scene* scene, Hero* hero, double posX, double posY, int lookX, int shotAngle, int ammo)
{
	if(checkAngle(shotAngle) && checkSprite(hero, shotAngle))
	{
		//
		// Disparar
		//
		Point shotPoint = sprite->point("shoot", posX, posY, spriteFrame, (lookX ==-1) ? Sprite::FLIP_X : 0);
		double rad = Math::toRadians((double)shotAngle);
		double dirX = Math::cos(rad)*lookX;
		double dirY = Math::sin(rad);
		double bulletAngle = Math::atan2(dirY, dirX);
		scene->addEntity(new PistolBullet(
				scene,
				shotPoint.x,
				shotPoint.y,
				Math::cos(bulletAngle)*VELOCITY,
				-Math::sin(bulletAngle)*VELOCITY));
		if(shootSound != null)
		{
			Mixer::playChannel(shootSound);
		}
		shooting = true;
		// ....
		animIndex = 0;
		spriteFrame = 0;
		shootingClock.reset(ANIMATION_TIME);
	}
	return ammo;
}
bool                Pistol::checkAngle(int shotAngle)
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
bool                Pistol::checkSprite(Hero* hero, int shotAngle)
{
	if(hero->isCrouching())
	{
		sprite = spritePistolCrouched;
	}
	else if(shotAngle == 0)
	{
		sprite = spritePistol0;
	}
	else if(shotAngle == 90)
	{
		sprite = spritePistol90;
	}
	else if(shotAngle == -90)
	{
		sprite = spritePistolDown;
	}
	else
	{
		printf("Ángulo no válido=%d\n", shotAngle);
		return false;
	}
	return true;
}