////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IronNokanaCannonBullet | Bala lanzada por el cañón de IronNokana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/nokana/IronNokanaCannonBullet.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/NormalExplosionS.h>

#include <mach/Random.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

IronNokanaCannonBullet::IronNokanaCannonBullet(Scene* scene, double x, double y) : EnemyProjectile(scene, x, y)
, vel(-Random().nextInt(80,140), 0)
, accel(0, 60*GRAVITY_DOWN)
, sprite(null)
, colorIndex(0)
, colorClock(0.06)
, positionClock(0.05)
{
	sprite = res.findSpriteSheet("IronNokanaCannonBullet")->getSprite();
	oldPositions[0] = pos;
	oldPositions[1] = pos;
	oldPositions[2] = pos;
}
IronNokanaCannonBullet::~IronNokanaCannonBullet()
{
}
void IronNokanaCannonBullet::update(double dt)
{
	//
	// Actualizar cambio de color
	//
	if(colorClock.update(dt))
	{
		colorIndex++;
		if(colorIndex >= MAX_COLORS)
			colorIndex = 0;
	}
	//
	// Actualizar las viejas posiciones
	//
	if(positionClock.update(dt))
	{
		for(int i = MAX_OLD_POSITIONS-1; i > 0; i--)
		{
			oldPositions[i] = oldPositions[i-1];
		}
		oldPositions[0] = pos;
	}
	//
	//
	// Actualizar movimiento
	//
	CollisionInfo ci = scene->moveEntity(this, dt, pos, vel, accel, false, MAP_TERRAIN_SOLID);
	
	if(ci.flags & COLLISION_FLAG_BOTTOM)
	{
		removable = true;
		scene->addEntity(new NormalExplosionS(scene, pos.x, pos.y));
	}
}
void IronNokanaCannonBullet::render(Graphics* gr)
{
	for(int i = MAX_OLD_POSITIONS-1; i > 0; i--)
	{
		sprite->render(gr, oldPositions[i].x, oldPositions[i].y, (colorIndex*5)+(1+i), 0);
	}
	sprite->render(gr, pos.x, pos.y, (colorIndex*5)+0, 0);
}
void IronNokanaCannonBullet::collide(Entity* other)
{
	if(dynamic_cast<Hero*>(other))
	{
		removable = true;
		((Hero*)other)->hurt();
		scene->addEntity(new NormalExplosionS(scene, pos.x, pos.y));
	}
}
Rectanglef IronNokanaCannonBullet::collisionRect() const
{
	return sprite->rectangle(pos.x, pos.y, (colorIndex*5)+0, 0);
}
