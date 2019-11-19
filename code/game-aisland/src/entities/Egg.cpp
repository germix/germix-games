////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Egg
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/Egg.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/EntityParameters.h>
#include <src/entities/hero/HeroBullet.h>
#include <src/entities/bonus/Bonus_Ax.h>
#include <src/entities/bonus/Bonus_Milk.h>
#include <src/entities/bonus/Bonus_Skate.h>
#include <src/entities/bonus/Bonus_Flower.h>
#include <src/entities/bonus/Bonus_Fireball.h>
#include <src/entities/followers/Eggplant.h>
#include <src/entities/followers/Honeygirl.h>

#include <gamelib/TimeClock.h>
#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Egg::BONUS_AX = "Ax";
const char* Egg::BONUS_MILK = "Milk";
const char* Egg::BONUS_SKATE = "Skate";
const char* Egg::BONUS_FLOWER = "Flower";
const char* Egg::BONUS_FIREBALL = "Fireball";
const char* Egg::BONUS_EGGPLANT = "Eggplant";
const char* Egg::BONUS_HONEYGIRL = "Honeygirl";

Egg::Egg(Scene* s, double x, double y, const String& ___bonus) : Entity(s, x, y)
, sheet(res.findSpriteSheet("Egg"))
, sprite(sheet->getSprite("None"))
, state(0)
, bonus(___bonus)
, kicked(false)
, velocity()
, acceleration()
, ready(false)
, readyClock(0.2)
{
}
Egg::~Egg()
{
}
void Egg::update(double dt)
{
	if(kicked)
	{
		unsigned int collisionFlags = scene->moveEntity(this, dt, pos, velocity, acceleration, false, MAP_TERRAIN_SOLID, COLLISION_FLAG_BOTTOM);

		if(0 != (collisionFlags & COLLISION_FLAG_BOTTOM))
		{
			dropBonus();
		}
	}
	if(!ready)
	{
		if(readyClock.update(dt))
		{
			ready = true;
		}
	}
	if(scene->getCameraRect().getMinX() > bounds().getMaxX())
	{
		removable = true;
	}
}
void Egg::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, state, 0);
}
Rectanglef Egg::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef Egg::bounds(double px, double py) const
{
	return sprite->rectangle(px, py, state, 0);
}
void Egg::collides(Entity* e)
{
	if(dynamic_cast<HeroBullet*>(e))
	{
		if(++state == 2)
		{
			dropBonus();
		}
		((HeroBullet*)e)->remove();
	}
}
Rectanglef Egg::getCollisionRectangle() const
{
	if(!ready)
		return Rectanglef();
	if(!kicked)
		return bounds();
	return Rectanglef();
}
void Egg::kick(double x)
{
	if(!kicked)
	{
		kicked = true;
		velocity = Vector2f(x, -150);
		acceleration = Scene::GRAVITY_ACCELERATION;
	}
}
void Egg::dropBonus()
{
	removable = true;
	if(bonus == BONUS_AX)				scene->addEntity(new Bonus_Ax(scene, pos.x, pos.y));
	else if(bonus == BONUS_FIREBALL)	scene->addEntity(new Bonus_Fireball(scene, pos.x, pos.y));
	else if(bonus == BONUS_MILK)		scene->addEntity(new Bonus_Milk(scene, pos.x, pos.y));
	else if(bonus == BONUS_SKATE)		scene->addEntity(new Bonus_Skate(scene, pos.x, pos.y));
	else if(bonus == BONUS_FLOWER)		scene->addEntity(new Bonus_Flower(scene, pos.x, pos.y));
	else if(bonus == BONUS_EGGPLANT)	scene->addEntity(new Eggplant(scene, pos.x, pos.y));
	else if(bonus == BONUS_HONEYGIRL)	scene->addEntity(new Honeygirl(scene, pos.x, pos.y));
}


