////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BradleyRocket
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/bradley/BradleyRocket.h>
#include <src/Debug.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/NormalExplosionM.h>

#include <mach/Math.h>
#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define VELOCITY 200.0

BradleyRocket::BradleyRocket(Scene* scene, double x, double y) : EnemyProjectile(scene, x, y)
, accel(0, GRAVITY_CONSTANT*GRAVITY_DOWN)
, oldPos(pos)
{
	//
	// Calcular vector velocidad
	//
	double rad = Math::toRadians(-45.0);
	vel.x = -Math::cos(rad)*VELOCITY;
	vel.y = Math::sin(rad)*VELOCITY;
	
	// ..
	sprite = res.findSpriteSheet("Bradley.Rocket")->getSprite();
}
BradleyRocket::~BradleyRocket()
{
}
void BradleyRocket::update(double dt)
{
	//
	// Guardar vieja posición
	//
	oldPos = pos;
	
	//
	// Mover
	//
	CollisionInfo ci = scene->moveEntity(this, dt, pos, vel, accel, false, MAP_TERRAIN_SOLID);
	
	// ...
	if(ci.flags & COLLISION_FLAG_BOTTOM)
	{
		removable = true;
		scene->addEntity(new NormalExplosionM(scene, pos.x, pos.y));
	}
}
void BradleyRocket::render(Graphics* gr)
{
	double angle = Math::atan2(pos.x - oldPos.x, pos.y - oldPos.y);
	double degrees = Math::toDegrees(angle);
	if(degrees < 0.0)
		degrees = 360.0 + degrees;
	
	int frame = Math::min(18, (int)Math::round(((degrees-200)/(360-200))*19.0));
	if(frame >= 0)
	{
		sprite->render(gr, pos.x, pos.y, frame, 0);

		if(Debug::showBulletRects)
		{
			gr->drawRect(bounds(), Debug::colorBulletRects);
		}
	}
}
Rectanglef BradleyRocket::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef BradleyRocket::bounds(double px, double py) const
{
	return Rectanglef(px - 8, py - 8, 16, 16);
}
void BradleyRocket::collide(Entity* other)
{
	if(dynamic_cast<Hero*>(other))
	{
		removable = true;
		((Hero*)other)->hurt();
		scene->addEntity(new NormalExplosionM(scene, pos.x, pos.y));
	}
}
Rectanglef BradleyRocket::collisionRect() const
{
	return bounds();
}
