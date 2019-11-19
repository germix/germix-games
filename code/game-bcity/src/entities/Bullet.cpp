////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bullet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/Bullet.h>
#include <src/Config.h>
#include <src/Map.h>
#include <src/Scene.h>
#include <src/Tiles.h>
#include <src/base/Sprite.h>
#include <src/entities/Bird.h>
#include <src/entities/tanks/HeroTank.h>
#include <src/entities/tanks/EnemyTank.h>
#include <src/entities/bullets/HeroBullet.h>
#include <src/entities/bullets/EnemyBullet.h>
#include <src/entities/explosions/SmallExplosion.h>

#include <mach/Math.h>
#include <mach/Mixer.h>
#include <mach/Graphics.h>
#include <mach/Rectangle.h>

Bullet::Bullet(Map* m, Scene* s, int x, int y, Direction dir, Tank* shooter, double velocity, bool ___strong) : Entity(m, s, x-2, y-2, 4, 4)
, vx(0)
, vy(0)
, clock(velocity)
, hero(null)
, enemy(null)
, strong(___strong)
, spriteIndex(0)
{
	//
	// Calcular desplazamientos y el índice del sprite
	//
	switch(dir)
	{
		case DIRECTION_UP:
			vx = 0;
			vy = -1;
			spriteIndex = 0;
			break;
		case DIRECTION_DOWN:
			vx = 0;
			vy = +1;
			spriteIndex = 2;
			break;
		case DIRECTION_LEFT:
			vx = -1;
			vy = 0;
			spriteIndex = 1;
			break;
		case DIRECTION_RIGHT:
			vx = +1;
			vy = 0;
			spriteIndex = 3;
			break;
	}
	//
	// Almacenar referencia al disparador si es un HeroTank ó un EnemyTank
	//
	if(dynamic_cast<HeroTank*>(shooter))
		hero = (HeroTank*)shooter;
	else
		enemy = (EnemyTank*)shooter;
}
Bullet::~Bullet()
{
}
void Bullet::update(double dt)
{
	if(clock.update(dt))
	{
		Rectangle collRectWithTile(x-3, y-3, width+6, height+6);
		
		if(!moveOrHit(collRectWithTile, 0, vy))
		{
			moveOrHit(collRectWithTile, vx, 0);
		}
		if(removable)
		{
			scene->addEntity(new SmallExplosion(map, scene, x+width/2, y+height/2));
		}
	}
}
void Bullet::render(Graphics* gr)
{
	if(Debug::showBulletRectangle)
	{
		if(hero != null)
			gr->fillRect(x, y, width, height, Color(0,255,255));
		else
			gr->fillRect(x, y, width, height, Color(0,255,0));
	}
	Config::bullet->render(gr, x, y, spriteIndex);
}
void Bullet::collides(Entity* other)
{
	Bird* bird;

	//
	// Comprobar si colisionó en el símbolo de la base
	//
	if(null != (bird = dynamic_cast<Bird*>(other)))
	{
		if(bird->isAlive())
		{
			bird->kill();
			removable = true;
		}
	}
	else
	{
		//
		// Comprobar colisión de bala de héroe con tanque enemigo o con bala enemiga
		//
		if(hero != null)
		{
			EnemyTank* enemyTank;
			EnemyBullet* enemyBullet;
			if(null != (enemyTank = dynamic_cast<EnemyTank*>(other)))
			{
				enemyTank->hurt();
				if(enemyTank->isDead())
				{
					hero->addVictim(enemyTank);
				}
				removable = true;
				hero->releaseBullet();
			}
			else if(null != (enemyBullet = dynamic_cast<EnemyBullet*>(other)))
			{
				enemyBullet->removable = true;
				removable = true;
				hero->releaseBullet();
			}
		}
		//
		// Comprobar colisión de bala de enemigo con tanque héroe o con bala de héroe
		//
		else if(enemy != null)
		{
			HeroTank* heroTank;
			HeroBullet* heroBullet;
			
			if(null != (heroTank = dynamic_cast<HeroTank*>(other)))
			{
				removable = true;
				heroTank->damage();
				heroTank->releaseBullet();
			}
			else if(null != (heroBullet = dynamic_cast<HeroBullet*>(other)))
			{
				removable = true;
				heroBullet->removable = true;
				heroBullet->hero->releaseBullet();
			}
		}
	}
}
bool Bullet::moveOrHit(const Rectangle& collisionRect, int dx, int dy)
{
	if(map->tryMoveBullet(collisionRect, dx, dy))
	{
		x += dx;
		y += dy;
	}
	else
	{
		removable = true;
		
		if(hero != null)
		{
			hero->releaseBullet();
			// ...
			int b = 0;
			std::vector<int> t = map->getTiles(collisionRect, dx, dy);
			
			for(unsigned int i = 0; i < t.size(); i++)
			{
				if(t[i] == Tiles::TILE_WALL || t[i] == Tiles::TILE_METAL)// CUIDADO: Esto funciona porque TILE_WALL < TILE_METAL
				{
					b = Math::max(b, t[i]);
				}
			}
			switch(b)
			{
				case Tiles::TILE_WALL:
					Mixer::playChannel(Config::auHitBrick);
					break;
				case Tiles::TILE_METAL:
					if(strong)
						Mixer::playChannel(Config::auHitBrick);
					else
						Mixer::playChannel(Config::auHitMetal);
					break;
			}
		}
		map->breakTile(collisionRect, dx, dy, strong);
	}
	return removable;
}
