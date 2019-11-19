////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Masknell | Helicóptero Masknell
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/masknell/Masknell.h>
#include <src/Debug.h>
#include <src/ResourceManager.h>
#include <src/routes/Route.h>
#include <src/routes/RouteCoordinate.h>
#include <src/scene/Scene.h>
#include <src/entities/effects/NormalExplosionM.h>

#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

Masknell::Masknell(Scene* scene, double x, double y, Route* r) : Enemy(scene, x, y)
, route(r)
, basePos(pos)
, health(50)
, traveled(0)
, sprite(null)
, spriteFrame(0)
, spriteHints(0)
, bladesIndex(0)
, bladesClock(0.05)
{
	SpriteSheet* sheet = res.findSpriteSheet("MasknellBlades");
	blades[0] = sheet->getSprite("Blades1");
	blades[1] = sheet->getSprite("Blades2");
	blades[2] = sheet->getSprite("Blades3");
	blades[3] = sheet->getSprite("Blades4");
	blades[4] = sheet->getSprite("Blades5");
	blades[5] = sheet->getSprite("Blades6");
}
Masknell::~Masknell()
{
}
void Masknell::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteFrame, spriteHints);
	blades[bladesIndex]->render(gr, pos.x, pos.y, spriteFrame, spriteHints);

	if(Debug::showEnemyRects)
	{
		gr->drawRect(hurtableRect(), Debug::colorEnemyRects);
	}
}
void Masknell::hurt(int damage)
{
	if(health > 0)
	{
		health -= damage;
		if(health <= 0)
		{
			destroy();
		}
	}
}
bool Masknell::isHurtable() const
{
	return true;
}
Rectanglef Masknell::hurtableRect() const
{
	return Rectanglef(pos.x-20, pos.y, 40, 40);
}
void Masknell::destroy()
{
	health = 0;
	removable = true;
	destroyed = true;
	scene->addEntity(new NormalExplosionM(scene, pos.x, pos.y+20));
}
void Masknell::update(double dt, RouteCoordinate* rc)
{
	traveled += 120*dt;
	route->getCoordinateFromTraveled(traveled, rc);
	if(rc->finished)
	{
		route->getCoordinate(1, rc);
		traveled = rc->distance;
	}
	pos.x = basePos.x+rc->x;
	pos.y = basePos.y+rc->y;

	if(bladesClock.update(dt))
	{
		if(++bladesIndex >= 6)
		{
			bladesIndex = 0;
		}
	}
}

