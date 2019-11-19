////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MasknellLeader | Helicóptero Masknell líder de la flota
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/masknell/MasknellLeader.h>
#include <src/ResourceManager.h>
#include <src/routes/Route.h>
#include <src/routes/RouteCoordinate.h>
#include <src/scene/Scene.h>
#include <src/entities/enemies/masknell/MasknellBullet.h>
#include <src/entities/enemies/masknell/MasknellShotEffect.h>
#include <src/entities/enemies/masknell/MasknellBulletCartridge.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

MasknellLeader::MasknellLeader(Scene* scene, double x, double y, Route* r) : Masknell(scene, x, y, r)
, state(STATE_STARTING)
, clock(0.04)
, distanceToRotation(0)
{
	sprite = res.findSpriteSheet("Masknell")->getSprite("Leader");

	RouteCoordinate rc;
	route->getCoordinate(2, &rc);
	distanceToRotation = rc.distance;
	spriteFrame = 3;
	spriteHints = 0;
}
MasknellLeader::~MasknellLeader()
{
}
void MasknellLeader::update(double dt)
{
	RouteCoordinate rc;
	Vector2f        oldPos = pos;
	Masknell::update(dt, &rc);
	// ...
	switch(state)
	{
		case STATE_STARTING:
			if(traveled > distanceToRotation)
			{
				state = STATE_ROTATING;
			}
			break;
		case STATE_SHOOTING:
			if(clock.update(dt))
			{
				Point p = sprite->point("Shoot", pos.x, pos.y, spriteFrame, spriteHints);
				scene->addEntity(new MasknellBullet(scene, p.x, p.y));
				scene->addEntity(new MasknellShotEffect(scene, p.x, p.y));
				if(pos.x < oldPos.x)
					scene->addEntity(new MasknellBulletCartridge(scene, p.x, p.y, +1));
				else
					scene->addEntity(new MasknellBulletCartridge(scene, p.x, p.y, -1));
			}
			break;
		case STATE_ROTATING:
			if(clock.update(dt))
			{
				spriteFrame++;
				if(spriteFrame >= sprite->count())
				{
					state = STATE_SHOOTING;
					clock.reset(0.9);
					spriteFrame = sprite->count()-1;
				}
			}
			break;
	}
}
