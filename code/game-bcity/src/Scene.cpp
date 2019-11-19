////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Scene
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Scene.h>
#include <src/Map.h>
#include <src/Tiles.h>
#include <src/entities/Bonus.h>
#include <src/entities/Entity.h>
#include <src/entities/Bird.h>
#include <src/entities/tanks/EnemyTank.h>

#include <src/entities/bullets/HeroBullet.h>

#include <tmx/TmxMap.h>

#define ENEMIES_PAUSED_TIME		10		// 10 SEGUNDOS
#define FORTIFIED_BASE_TIME		20		// 20 SEGUNDOS

const Point Scene::spawnPoints[] = 
{
	Point(0,0),
	Point(96,0),
	Point(192,0),
};
const Point Scene::borderBasePoints[] =
{
	Point(11, 25),
	Point(11, 24),
	Point(11, 23),
	Point(12, 23),
	Point(13, 23),
	Point(14, 23),
	Point(14, 24),
	Point(14, 25),
};

#define MAX_SPAWN_POINTS			(sizeof(spawnPoints)/sizeof(spawnPoints[0]))
#define MAX_BORDER_BASE_POINTS		(sizeof(borderBasePoints)/sizeof(borderBasePoints[0]))

Scene::Scene()
: map(null)

, gameOver(false)
, levelCompleted(false)

, entities()
, addedEntities()

, enemiesPaused(false)
, enemiesPausedClock(ENEMIES_PAUSED_TIME)

, fortifiedBase(false)
, fortifiedBaseClock(FORTIFIED_BASE_TIME)

, enemySet()
, spawnState(SPAWN_STATE_NONE)
, spawnClock(1.8)
, spawnBlink()
, spawnPointIndex(1)

, enemyTanksInScene(0)
{
}
Scene::~Scene()
{
	clear();
}
Map* Scene::load(const TmxMap* tmx)
{
	clear();
	
	//
	// Resetear atributos
	//
	gameOver = false;
	levelCompleted = false;
	entities.clear();
	addedEntities.clear();
	enemiesPaused = false;
	enemiesPausedClock.reset();
	fortifiedBase = false;
	fortifiedBaseClock.reset();
	spawnState = SPAWN_STATE_NONE;
	spawnClock.reset();
	spawnBlink.reset();
	spawnPointIndex = 1;
	enemyTanksInScene = 0;

	//
	// Crear mapa
	//
	map = new Map(tmx);
	
	//
	// Cargar lista de enemigos
	//
	enemySet.load(tmx);
	
	//
	// Retornar mapa
	//
	return map;
}
void Scene::update(double dt)
{
	std::list<Entity*> removables;
	
	//
	// Primero actualizar el mapa
	//
	map->update(dt);
	
	if(enemiesPaused)
	{
		if(enemiesPausedClock.update(dt))
		{
			enemiesPaused = false;
		}
	}
	if(fortifiedBase)
	{
		if(fortifiedBaseClock.update(dt))
		{
			fortifiedBase = false;
			for(int i = 0; i < MAX_BORDER_BASE_POINTS; i++)
			{
				map->replaceTile(borderBasePoints[i].x, borderBasePoints[i].y, Tiles::TILE_METAL, Tiles::TILE_WALL);
			}
		}
	}
	//
	// Actualizar las entidades
	//
	for(std::list<Entity*>::const_iterator it = entities.begin(); it != entities.end(); it++)
	{
		(*it)->update(dt);
		if((*it)->isRemovable())
		{
			removables.push_back(*it);
		}
	}
	clearEntities(removables);
	
	//
	// Agregar las entidades pendientes
	//
	for(std::list<Entity*>::const_iterator it = addedEntities.begin(); it != addedEntities.end(); it++)
	{
		entities.push_back(*it);
	}
	addedEntities.clear();
	
	//
	// Comprobar colisiones
	//
	for(std::list<Entity*>::const_iterator it1 = entities.begin(); it1 != entities.end(); it1++)
	{
		for(std::list<Entity*>::const_iterator it2 = entities.begin(); it2 != entities.end(); it2++)
		{
			Entity* e1 = *it1;
			Entity* e2 = *it2;
			
			if(e1 != e2
				&& !e1->isRemovable()
				&& !e2->isRemovable()
				&& e1->getCollisionRectangle().intersects(e2->getCollisionRectangle()))
			{
				if(dynamic_cast<HeroBullet*>(e1) || dynamic_cast<HeroBullet*>(e2))
				{
					if(dynamic_cast<EnemyTank*>(e1) || dynamic_cast<EnemyTank*>(e2))
					{
					}
				}
				// Notificar colisiones
				e1->collides(e2);
				if(!(e2->isRemovable() || e2->isRemovable()))
					e2->collides(e1);
				// Marcar como eliminables
				if(e1->isRemovable()) removables.push_back(e1);
				if(e2->isRemovable()) removables.push_back(e2);
			}
		}
	}
	clearEntities(removables);

	//
	// Comprobar generador de enemigos
	//
	switch(spawnState)
	{
		case SPAWN_STATE_NONE:
			if(enemyTanksInScene < 4 && !enemySet.isEmpty())
			{
				if(spawnClock.update(dt))
				{
					spawnBlink.reset();
					spawnState = SPAWN_STATE_BLINK;
				}
			}
			break;
		case SPAWN_STATE_BLINK:
			if(spawnBlink.update(dt))
			{
				addedEntities.push_back(
					enemySet.getEnemyTank(
						map, this,
						spawnPoints[spawnPointIndex].x, spawnPoints[spawnPointIndex].y));
				enemyTanksInScene++;
				if(++spawnPointIndex >= MAX_SPAWN_POINTS)
				{
					spawnPointIndex = 0;
				}
				spawnState = SPAWN_STATE_NONE;
			}
			break;
	}
	if(enemyTanksInScene == 0 && enemySet.isEmpty())
	{
		levelCompleted = true;
	}
}
void Scene::render(Graphics* gr)
{
	std::vector<Bonus*> bonus;
	
	//
	// Pintar el mapa
	//
	map->render(gr);
	
	//
	// Pintar las entidades
	//
	for(std::list<Entity*>::const_iterator it = entities.begin(); it != entities.end(); it++)
	{
		Entity* e = *it;
		if(dynamic_cast<Bonus*>(e))
			bonus.push_back((Bonus*)e);
		else
			e->render(gr);
	}
	//
	// Pintar las partes del mapa que están sobre otros objetos
	//
	map->renderTopmost(gr);
	
	//
	// Pintar los bonus
	//
	for(std::vector<Bonus*>::const_iterator it = bonus.begin(); it != bonus.end(); it++)
	{
		(*it)->render(gr);
	}
	//
	// Pintar efecto de parpadeo del generador de enemigos
	//
	if(spawnState == SPAWN_STATE_BLINK)
	{
		spawnBlink.render(gr, spawnPoints[spawnPointIndex].x, spawnPoints[spawnPointIndex].y);
	}
}
bool Scene::tryMove(Tank* tank, int dx, int dy) const
{
	Entity* e;
	Rectangle rcOld = tank->getCollisionRectangle();
	Rectangle rcNew(rcOld.getX()+dx, rcOld.getY()+dy, rcOld.getWidth(), rcOld.getHeight());
	
	for(std::list<Entity*>::const_iterator it = entities.begin(); it != entities.end(); it++)
	{
		e = *it;
		if(null != dynamic_cast<Tank*>(e) || null != dynamic_cast<Bird*>(e))
		{
			Rectangle rc = e->getCollisionRectangle();
			
			if(!rc.intersects(rcOld) && rc.intersects(rcNew))
				return false;
		}
	}
	return true;
}
void Scene::killEnemies()
{
	EnemyTank* et;
	std::list<Entity*> removables;
	
	for(std::list<Entity*>::const_iterator it = entities.begin(); it != entities.end(); it++)
	{
		if(null != (et = dynamic_cast<EnemyTank*>(*it)))
		{
			et->kill();
			removables.push_back(et);
		}
	}
	clearEntities(removables);
}
void Scene::pauseEnemies()
{
	enemiesPaused = true;
	enemiesPausedClock.reset(ENEMIES_PAUSED_TIME);
}
void Scene::fortifyBase()
{
	fortifiedBase = true;
	fortifiedBaseClock.reset(FORTIFIED_BASE_TIME);
	
	for(int i = 0; i < MAX_BORDER_BASE_POINTS; i++)
	{
		map->replaceTile(borderBasePoints[i].x, borderBasePoints[i].y, Tiles::TILE_METAL);
	}
}
int Scene::getEnemyCount() const
{
	return enemySet.getRemanent();
}
void Scene::clear()
{
	for(std::list<Entity*>::const_iterator it = entities.begin(); it != entities.end(); it++)
	{
		delete *it;
	}
	entities.clear();
	for(std::list<Entity*>::const_iterator it = addedEntities.begin(); it != addedEntities.end(); it++)
	{
		delete *it;
	}
	addedEntities.clear();
}
void Scene::clearEntities(std::list<Entity*>& removables)
{
	for(std::list<Entity*>::const_iterator it = removables.begin(); it != removables.end(); it++)
	{
		entities.remove(*it);
		if(dynamic_cast<EnemyTank*>(*it))
		{
			enemyTanksInScene--;
		}
		delete *it;
	}
	removables.clear();
	
}
