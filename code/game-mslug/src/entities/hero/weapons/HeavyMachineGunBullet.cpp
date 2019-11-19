////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeavyMachineGunBullet | Bala de HeavyMachineGun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/weapons/HeavyMachineGunBullet.h>
#include <src/Debug.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/effects/BulletHit1.h>
#include <src/entities/effects/BulletHit2.h>
#include <src/___/HurtableRect.h>

#include <mach/Math.h>
#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

HeavyMachineGunBullet::HeavyMachineGunBullet(Scene* scene, double px, double py, double vx, double vy, double shootAngle) : HeroBullet(scene, px, py)
, vel(vx, vy)
, sprite(null)
, spriteFrame(0)
, spriteHints(0)
{
	sprite = res.findSpriteSheet("Bullet.H")->getSprite();

	//
	// Seleccionar hints y frame según el ángulo
	//
	int index = -1;
	int count = 16;
	
	index = (int)(Math::round(shootAngle/90.0*(double)count));
	
	if(vx < 0)
		spriteHints |= Sprite::FLIP_X;
	if(index < 0)
		index *= -1;
	else
		spriteHints |= Sprite::FLIP_Y;
	spriteFrame = index;
}
HeavyMachineGunBullet::~HeavyMachineGunBullet()
{
}
void HeavyMachineGunBullet::update(double dt)
{
	CollisionInfo ci =  scene->moveEntity(this, dt, pos, vel, accel, false, MAP_TERRAIN_SOLID);

	if(ci.flags != 0)
	{
		scene->addEntity(new BulletHit2(scene, pos.x, pos.y));
		
		removable = true;
	}
	else if(scene->getCameraRect().excluded(bounds()))
	{
		removable = true;
	}
}
void HeavyMachineGunBullet::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteFrame, spriteHints);
	if(Debug::showBulletRects)
	{
		gr->drawRect(bounds(), Debug::colorBulletRects);
	}
}
Rectanglef HeavyMachineGunBullet::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef HeavyMachineGunBullet::bounds(double px, double py) const
{
	return Rectanglef(px-4, py-4, 8, 8);
}
void HeavyMachineGunBullet::hurt(HurtableRect* hr)
{
	removable = true;
	hr->hurt(2);
	scene->addEntity(new BulletHit1(scene, pos.x, pos.y));
}
