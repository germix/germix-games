////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Aircraft
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/aircrafts/Aircraft.h>
#include <src/Debug.h>
#include <src/sprites/Sprite.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/bullets/HeroBullet.h>
#include <src/entities/explosions/HitExplosion.h>
#include <src/entities/explosions/NormalExplosion.h>
#include <src/entities/enemies/EnemyWeaponHandler.h>
#include <src/entities/enemies/aircrafts/AircraftTroop.h>
#include <src/entities/enemies/aircrafts/behaviors/AircraftBehavior.h>

#include <mach/Color.h>
#include <mach/Graphics.h>

#define COLLISION_DAMAGE	10

Aircraft::Aircraft(Scene* s, double x, double y, int ___health, Sprite* ___sprite, AircraftTroop* ___troop, AircraftBehavior* ___behavior, EnemyWeaponHandler* ___weapon) : Enemy(s, x, y)
, sprite(___sprite)
, spriteIndex(0)
, alive(true)
, health(___health)

, interactive(false)

, troop(___troop)
, behavior(___behavior)

, weapon(___weapon)

, canHurt(true)
, hurtTime(0.4)
{
}
Aircraft::~Aircraft()
{
	if(troop)
		troop->unref();
	if(behavior)
		delete behavior;
	if(weapon)
		delete weapon;
}
Rectanglef Aircraft::rect() const
{
	if(alive)
		return sprite->rect(pos);
	return Rectanglef();
}
void Aircraft::update(double dt)
{
	//
	// Analizar tiempo de daño
	//
	if(hurtTime.update(dt))
	{
		canHurt = true;
	}
	
	//
	// Comprobar disparo
	//
	if(weapon != null)
	{
		weapon->update(scene, pos.x, pos.y, dt);
	}
	
	//
	// Comprobar comportamiento
	//
	if(behavior != null)
		behavior->update(pos, dt, sprite, spriteIndex);
		
	//
	// Comprobar interactividad
	//
	checkInteractivity();
}
void Aircraft::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteIndex, int((1.0f + (behavior->getLevel()*0.1f)) * 255));
	
	if(Debug::showRectangle)
	{
		gr->drawRect(rect(), Color(255,0,0));
	}
}
bool Aircraft::hurt(int damage)
{
	if(canHurt)
	{
		canHurt = false;
		hurtTime.reset();
		// ...
		health -= damage;
		if(health <= 0)
		{
			alive = false;
			health = 0;
			removeMe(true);
			return false;
		}
		return true;
	}
	return false;
}
bool Aircraft::isAlive() const
{
	return alive;
}
bool Aircraft::isDestroyed() const
{
	return !alive;
}
int Aircraft::getHealth() const
{
	return health;
}
int Aircraft::getDestructionScore() const
{
	return 1;
}
void Aircraft::checkHit(HeroBullet* bullet)
{
	if(behavior == null)
	{
		//
		// Para el caso en que haya un avión sin comportamiento, ESTO NO DEBERÍA SUCEDER
		//
		removeMe(false);
	}
	else
	{
		if(interactive && behavior->getLevel() == 0)
		{
			if(rect().intersects(bullet->rect()))
			{
				hurt(bullet->getDamageToEnemy());
				if(isAlive())
				{
					scene->addEntity(new HitExplosion(scene,
						bullet->position().x,
						bullet->position().y,
						null));
				}
				bullet->destroy();
			}
		}
	}
}
void Aircraft::checkCollision(Entity* other)
{
	if(behavior == null)
	{
	}
	else if(interactive && behavior->getLevel() == 0)
	{
		if(dynamic_cast<Hero*>(other))
		{
			if(rect().intersects(other->rect()))
			{
				Hero* hero = (Hero*)other;
				
				hero->hurt(COLLISION_DAMAGE);
				if(hurt(hero->getCollisionDamage()))
				{
					scene->addEntity(
						new NormalExplosion(scene,
							pos.x,
							pos.y,
							null,
							"explosions.small",
							"explosions.16x16.v2"));
				}
			}
		}
	}
}
void Aircraft::removeMe(bool destroyed)
{
	removable = true;
	if(troop != null)
	{
		troop->remove(this, scene, destroyed);
	}
	if(destroyed)
	{
//		ExplosionFactory::destroyed(scene, pos);
		scene->getHero()->addScore(getDestructionScore());
		int w = sprite->width;
		const char* e = 0;
		if(w == 16)
			e = "explosions.16x16.v1";
		else if(w == 32)
			e = "explosions.32x32.v1";
		else if(w == 64)
			e = "explosions.64x64.v1";
		
		if(e)
		{
			scene->addEntity(
				new NormalExplosion(scene,
					pos.x,
					pos.y,
					null,
					"explosions.small",
					e));
		}
	}
}
void Aircraft::checkInteractivity()
{
	if(!interactive)
	{
		if(scene->getSceneRect().intersects(sprite->rect(pos)))
		{
			interactive = true;
		}
	}
	else if(behavior->isRemovable())
	{
		if(!scene->getSceneRect().intersects(sprite->rect(pos)))
		{
			removeMe(false);
		}
	}
}
