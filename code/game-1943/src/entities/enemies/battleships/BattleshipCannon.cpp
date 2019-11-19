////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BattleshipCannon
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/battleships/BattleshipCannon.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/bullets/HeroBullet.h>
#include <src/entities/enemies/battleships/Battleship.h>
#include <src/entities/enemies/EnemyWeaponHandler.h>
#include <src/Utils.h>
#include <src/sprites/Sprite.h>
#include <src/entities/explosions/HitExplosion.h>
#include <src/entities/explosions/NormalExplosion.h>

#include <mach/Math.h>
#include <mach/Random.h>

BattleshipCannon::BattleshipCannon(Scene* scene, double x, double y, Battleship* ___battleship, Sprite* ___sprite, int ___health, EnemyWeapon* ___weapon, bool ___isGiantCannon) : Enemy(scene, x, y)
, sprite(___sprite)
, spriteIndex(0)
, destroyed(false)
, battleship(___battleship)
, health(___health)
, weapon(null)
, isGiantCannon(___isGiantCannon)
{
	if(___weapon)
	{
		weapon = new EnemyWeaponHandler(___weapon, Random().nextDouble(3.0, 4.5), 100);
	}
}
BattleshipCannon::~BattleshipCannon()
{
	delete weapon;
}
Vector2f BattleshipCannon::position() const
{
	Rectanglef rc = battleship->rect();
	return Vector2f(rc.getX() + pos.x, rc.getY() + pos.y);
}
Rectanglef BattleshipCannon::rect() const
{
	if(destroyed)
		return Rectanglef();
	return sprite->rect(position());
}
void BattleshipCannon::update(double dt)
{
	if(destroyed)
		return;
	Hero* hero = scene->getHero();
	Vector2f heroPos = hero->position();
	Vector2f cannonPos = position();
	if(isGiantCannon)
	{
		double dx = (heroPos.x - cannonPos.x);
		double dy = (heroPos.y - cannonPos.y);
		double radians = Math::atan2(dy, dx);
		double degrees = Math::toDegrees(radians);
		
		if(degrees >= 30 && degrees <= 150)
		{
			if(degrees >= 60 && degrees < 120)
				spriteIndex = 1;
			else if(degrees > 120 && degrees < 150)
				spriteIndex = 0;
			else if(degrees > 30 && degrees < 60)
				spriteIndex = 2;
			
			if(weapon != null)
			{
				weapon->update(scene, position().x, position().y, dt);
			}
		}
	}
	else
	{
		double dx = (heroPos.x - cannonPos.x);
		double dy = (heroPos.y - cannonPos.y);
		double radians = Math::atan2(dy, dx);
		
		spriteIndex = Utils::spriteFromAngle(radians, sprite->count);
		if(weapon != null)
		{
			weapon->update(scene, position().x, position().y, dt);
		}
	}
}
void BattleshipCannon::render(Graphics* gr)
{
	if(destroyed)
		return;
	sprite->render(gr, position().x, position().y, spriteIndex);
}
bool BattleshipCannon::hurt(int damage)
{
	health -= damage;
	if(health <= 0)
	{
		health = 0;
		destroyed = true;
		removable = true;
		scene->getHero()->addScore(getDestructionScore());
		scene->addEntity(new NormalExplosion(scene, pos.x, pos.y, battleship, "explosions.small", "explosions.16x16.v1"));
		return false;
	}
	return true;
}
bool BattleshipCannon::isAlive() const
{
	return !destroyed;
}
bool BattleshipCannon::isDestroyed() const
{
	return destroyed;
}
int BattleshipCannon::getHealth() const
{
	return health;
}
int BattleshipCannon::getDestructionScore() const
{
	return 1;
}
void BattleshipCannon::checkHit(HeroBullet* bullet)
{
	if(rect().intersects(bullet->rect()))
	{
		hurt(bullet->getDamageToEnemy());
		if(isAlive())
		{
			scene->addEntity(new HitExplosion(scene, pos.x, pos.y, battleship));
		}
		bullet->destroy();
	}
}
