////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyTank
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/tanks/EnemyTank.h>
#include <src/Config.h>
#include <src/Map.h>
#include <src/Scene.h>
#include <src/entities/bonus/BonusClock.h>
#include <src/entities/bonus/BonusGrenade.h>
#include <src/entities/bonus/BonusHelmet.h>
#include <src/entities/bonus/BonusShovel.h>
#include <src/entities/bonus/BonusStar.h>
#include <src/entities/bonus/BonusTank.h>
#include <src/entities/bullets/EnemyBullet.h>
#include <src/entities/explosions/BigExplosion.h>

#include <mach/Mixer.h>
#include <mach/Random.h>

const Direction EnemyTank::allDirections[] =
{
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
};
const double EnemyTank::MOVE_TIME_TANK_1 = 0.05;
const double EnemyTank::MOVE_TIME_TANK_2 = 0.024;
const double EnemyTank::MOVE_TIME_TANK_3 = 0.05;
const double EnemyTank::MOVE_TIME_TANK_4 = 0.08;

EnemyTank::EnemyTank(Map* m, Scene* s, int x, int y, int model, bool bonus)
: Tank(m, s, x, y, model, (model == TANK_MODEL_ENEMY_4) ? TANK_COLOR_GREEN : TANK_COLOR_GRAY)
, moveClock(0.09)
, shootClock(2)
, dead(false)
, health(1)
, deadScore(100)
, canDropBonus(false)
, blinkBonusClock(0.08)
, blinkBonusIndex(0)
, blinkTank4Clock(0.002)
, blinkTank4Index(0)
, lastTankColor(0)
{
	switch(model)
	{
		case TANK_MODEL_ENEMY_1:
			deadScore = 100;
			moveClock.reset(MOVE_TIME_TANK_1);
			break;
		case TANK_MODEL_ENEMY_2:
			deadScore = 200;
			moveClock.reset(MOVE_TIME_TANK_2);
			break;
		case TANK_MODEL_ENEMY_3:
			deadScore = 300;
			moveClock.reset(MOVE_TIME_TANK_3);
			break;
		case TANK_MODEL_ENEMY_4:
			health = 4;
			deadScore = 400;
			moveClock.reset(MOVE_TIME_TANK_4);
			break;
	}
	canDropBonus = bonus;
}
EnemyTank::~EnemyTank()
{
}
void EnemyTank::update(double dt)
{
	//
	// Parpadeo de los tanques con bonus
	//
	if(canDropBonus)
	{
		if(blinkBonusClock.update(dt))
		{
			if(tankModel == TANK_MODEL_ENEMY_4)
			{
			}
			else
			{
				blinkBonusIndex++;
				if((blinkBonusIndex&1) == 1)
				{
					lastTankColor = tankColor;
					selectTankColor(TANK_COLOR_RED);
				}
				else
				{
					selectTankColor(lastTankColor);
				}
			}
		}
	}
	//
	// Comprobar movimiento y disparos
	//
	if(!scene->isEnemiesPaused())
	{
		if(moveClock.update(dt))
		{
			if(!move(dir))
			{
				std::vector<Direction> dirs = getRandomDirections(dir);
				
				for(int i = 0; i < dirs.size(); i++)
				{
					if(move(dirs[i]))
					{
						dir = dirs[i];
						break;
					}
				}
			}
		}
		if(shootClock.update(dt))
		{
			shoot();
		}
	}
	if(tankModel == TANK_MODEL_ENEMY_4)
	{
		if(health == 3 || health == 2)
		{
			const int colors3[] = {TANK_COLOR_BROWN, TANK_COLOR_GRAY};
			const int colors2[] = {TANK_COLOR_BROWN, TANK_COLOR_GREEN};
			
			if(blinkTank4Clock.update(dt))
			{
				if((blinkBonusIndex&1) != 1)
				{
					if(health == 3)
						selectTankColor(colors3[(++blinkTank4Index&1)]);
					else
						selectTankColor(colors2[(++blinkTank4Index&1)]);
				}
			}
		}
	}
}
void EnemyTank::render(Graphics* gr)
{
	Tank::render(gr);
}
void EnemyTank::hurt()
{
	if(health > 0)
	{
		if(--health == 0)
		{
			//
			// Matar
			//
			kill();
			
			//
			// Generar bonus
			//
			if(canDropBonus)
			{
				Random r;
				int randX = r.nextInt(8, map->getPixelWidth()-16);
				int randY = r.nextInt(8, map->getPixelHeight()-16);
				
				switch(r.nextInt(0, 5))
				{
					case 0: scene->addEntity(new BonusClock(map, scene, randX, randY)); break;
					case 1: scene->addEntity(new BonusGrenade(map, scene, randX, randY)); break;
					case 2: scene->addEntity(new BonusHelmet(map, scene, randX, randY)); break;
					case 3: scene->addEntity(new BonusShovel(map, scene, randX, randY)); break;
					case 4: scene->addEntity(new BonusStar(map, scene, randX, randY)); break;
					case 5: scene->addEntity(new BonusTank(map, scene, randX, randY)); break;
				}
				Mixer::playChannel(Config::auEnemeyDeadWithBonus);
			}
			else
			{
				Mixer::playChannel(Config::auEnemeyDead);
			}
		}
		else
		{
			if(health == 1)
			{
				selectTankColor(TANK_COLOR_GRAY);
			}
			Mixer::playChannel(Config::auHitArmoredTank);
		}
	}
}
void EnemyTank::kill()
{
	//
	// Marcar como muerto y removible
	//
	dead = true;
	removable = true;
	
	//
	// Generar una explosión
	//
	scene->addEntity(new BigExplosion(map, scene, x + width/2, y + height/2));
}
void EnemyTank::shoot()
{
	if(Debug::enemiesCanShoot)
	{
		Point pos = getShootPosition(dir);
		scene->addEntity(new EnemyBullet(
				map,
				scene,
				pos.x,
				pos.y,
				dir,
				this));
	}
}
bool EnemyTank::move(Direction dir)
{
	int dx = 0;
	int dy = 0;
	switch(dir)
	{
		case DIRECTION_UP:		dy = -1; break;
		case DIRECTION_DOWN:	dy = +1; break;
		case DIRECTION_LEFT:	dx = -1; break;
		case DIRECTION_RIGHT:	dx = +1; break;
	}
	return Tank::move(dx, dy);
}
std::vector<Direction> EnemyTank::getRandomDirections(Direction thisNot) const
{
	Random rand;
	std::vector<Direction> dirs;
	std::vector<Direction> randdirs;
	
	for(int i = 0; i < 4; i++)
	{
		if(allDirections[i] != thisNot)
			dirs.push_back(allDirections[i]);
	}
	for(unsigned int i = 0; i < dirs.size(); i++)
	{
		randdirs.push_back(dirs[rand.nextInt(i, dirs.size())]);
	}
	return randdirs;
}

