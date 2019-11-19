////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Scene
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/scene/Scene.h>
#include <src/Config.h>
#include <src/___/Knifeable.h>
#include <src/___/Hurtable.h>
#include <src/___/HurtableRect.h>
#include <src/scene/Map.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/projectiles/HeroBomb.h>
#include <src/entities/projectiles/HeroBullet.h>

#include <mach/Math.h>
#include <mach/Graphics.h>

Scene::Scene(Map* ___map, bool activateTime)
: map(___map)
, hero(null)
, entityList()
, entityAddedList()
, entityRemovableList()

, sceneRect()
, sceneScroll()
, relativeScroll()
, leftLimit(0)
, rightLimit(-1)
, autoLeftLimit(true)
, autoRightLimit(true)

, restoring(false)
, restoringClock(0.02)

, time(activateTime ? 60 : 0)
, timeClock(5)

, missionFailed(false)
, missionCompleted(false)
{
	if(map)
		sceneRect = Rectanglef(0, 0, map->getWidth(), map->getHeight());

	updateCamera(0);
}
Scene::~Scene()
{
	clear();
}
void Scene::clear()
{
	if(map)
	{
		delete map;
		map = null;
	}
	entityList.clear();
	entityAddedList.clear();
	entityRemovableList.clear();
}
void Scene::update(double dt)
{
	EntityNode* next;
	EntityNode* node;

	if(!map)
		return;
	
	map->update(this, dt);

	//
	// Actualizar tiempo
	//
	if(time && hero && !(hero->isLoser() || hero->isWinner()))
	{
		if(timeClock.update(dt))
		{
			if(--time < 0)
			{
				time = 0;
				hero->dead();
			}
		}
	}

	//
	// Agregar entidades
	//
	for(node = entityAddedList.head; node != null; node = next)
	{
		if(dynamic_cast<Hero*>(node->entity))
			hero = (Hero*)node->entity;
		
		next = entityList.append(entityAddedList, node);
	}
	//
	// Actualizar entidades
	//
	for(node = entityList.head; node != null; node = next)
	{
		node->entity->update(dt);
		if(!node->entity->isRemovable())
			next = node->next;
		else
			next = entityRemovableList.append(entityList, node);
	}
	//
	// Comprobar colisiones
	//
	if(hero)
	{
		checkHits();
		checkCollisions();
	}
	//
	// Eliminar entidades
	//
	if(!entityRemovableList.empty())
	{
		entityRemovableList.clear();
	}
	//
	// Actualizar cámara
	//
	updateCamera(dt);
}
void Scene::render(Graphics* gr)
{
	if(!map)
		return;
	int sx = (int)(sceneScroll.x+relativeScroll.x) - map->getX();
	int sy = (int)(sceneScroll.y+relativeScroll.y) - map->getY();
	
	gr->clip(map->getX(), map->getY(), Math::min(map->getWidth(),SCREEN_WIDTH), Math::min(map->getHeight(),SCREEN_HEIGHT));
	// ...
	map->renderBackground(gr, sx, sy);
	// ...
	gr->translate(-sx, -sy);

	//
	// Dibujar entidades
	//
	EntityNode* node;
	for(node = entityList.head; node != null; node = node->next)
	{
		if(node->entity != hero)
			node->entity->render(gr);
	}
	if(hero)
		hero->render(gr);
	
	gr->translate(+sx, +sy);

	map->renderForeground(gr, sx, sy);
	
	gr->clip(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}
void Scene::setLeftLimit(int newLimit)
{
	leftLimit = newLimit;
	if(leftLimit < 0) leftLimit = 0;
}
void Scene::setRightLimit(int newLimit)
{
	if(newLimit == -1)
	{
		restoring = true;
		restoringClock.reset();
	}
	else
	{
		rightLimit = newLimit;
		if(rightLimit > map->getWidth()) rightLimit = map->getWidth()-1;
		else if(rightLimit < SCREEN_WIDTH) rightLimit = SCREEN_WIDTH;
	}
}
void Scene::addEntity(Entity* entity)
{
	entityAddedList.append(entity);
}
void Scene::addEntityBackOfOther(Entity* other, Entity* entity)
{
	entityAddedList.append(entity, other);
}
CollisionInfo Scene::moveEntity(Entity* entity, double dt, Vector2f& pos, Vector2f& vel, const Vector2f& accel, bool onGround, unsigned int terrainTypes)
{
	CollisionInfo info;
	Vector2f oldPosition = pos;
	Vector2f oldVelocity = vel;
	
	//
	// Ecuación cinemática de posición
	//
	// y' = y + v*dt + (a*dt^2)/2
	//
	pos.x = oldPosition.x + oldVelocity.x*dt + (accel.x*dt*dt)/2;
	pos.y = oldPosition.y + oldVelocity.y*dt + (accel.y*dt*dt)/2;
	
	//
	// Ecuación cinemática de velocidad
	//
	// v' = v + a*dt
	//
	vel.x = oldVelocity.x + accel.x*dt;
	vel.y = oldVelocity.y + accel.y*dt;
	
	if(terrainTypes)
	{
		info.flags = map->checkCollision(entity, pos, vel, oldPosition, oldVelocity, terrainTypes);
	}
	
	return info;
}
Vector2f Scene::boundsInScene(const Vector2f pos) const
{
	double x = pos.x;
	if(x < 0)
		x = 0;
	if(x < leftLimit)
		x = leftLimit;
	
	if(x >= map->getWidth())
	{
		x = map->getWidth()-1;
	}
	if(rightLimit != -1)
	{
		if(x > rightLimit)
		{
			x = rightLimit;
		}
	}
	return Vector2f(x, pos.y);
}
std::vector<Knifeable*> Scene::getNearbyKnifeableEntities(double posX, double posY, int radius) const
{
	Rectanglef rect(posX-radius, posY-radius, radius*2, radius*2);
	std::vector<Knifeable*> knifeables;
	
	for(EntityNode* node = entityList.head; node != null; node = node->next)
	{
		if(node->entity != hero)
		{
			Knifeable* k = dynamic_cast<Knifeable*>(node->entity);
			if(k != null && k->isKnifeHurtable() && rect.intersects(node->entity->bounds()))
			{
				knifeables.push_back(k);
			}
		}
	}
	return knifeables;
}
std::vector<HurtableRect*> Scene::getHurtableRectanglesInArea(const Rectanglef& areaRect) const
{
	Hurtable* h;
	HurtableRect* hr;
	std::vector<HurtableRect*> rects;
	
	for(EntityNode* node = entityList.head; node != null; node = node->next)
	{
		if(node->entity != hero)
		{
			if(null != (h = dynamic_cast<Hurtable*>(node->entity)))
			{
				h->getHurtableRects(areaRect, rects);
			}
			else if(null != (hr = dynamic_cast<HurtableRect*>(node->entity)))
			{
				if(hr->isHurtable() &&  hr->hurtableRect().intersects(areaRect))
				{
					rects.push_back(hr);
				}
			}
		}
	}
	return rects;
}
void Scene::updateCamera(double dt)
{
//	if(hero != null)
	{
		sceneScroll = map->getSuggestedSceneScroll(hero);
	}
	//
	// Ajustar límites horizontales
	//
	if(restoring)
	{
		if(restoringClock.update(dt))
		{
			Vector2f scroll = map->getSuggestedSceneScroll(hero);
			bool changes = false;
			
			scroll.x += SCREEN_WIDTH;
			
			if(rightLimit < scroll.x)
			{
				changes = true;
				rightLimit += 2;
			}
			if(relativeScroll.y < 0)
			{
				changes = true;
				relativeScroll.y += 1;
				if(relativeScroll.y > 0)
					relativeScroll.y = 0;
			}
			if(!changes)
			{
				restoring = false;
				rightLimit = -1;
			}
		}
	}
	if(autoRightLimit && rightLimit != -1)
	{
		if((sceneScroll.x+SCREEN_WIDTH) > rightLimit)
		{
			sceneScroll.x -= (sceneScroll.x+SCREEN_WIDTH) - rightLimit;
		}
	}
	if(autoLeftLimit)
	{
		int m = map->getWidth() - SCREEN_WIDTH - 100;
		
		leftLimit = (int)Math::max((double)leftLimit, sceneScroll.x);
		sceneScroll.x = leftLimit;
		leftLimit = Math::min(leftLimit, m);
	}
	
	//
	// Actualizar rectángulo de escena
	//
	{
		int sceneWidth;
		int sceneHeight;
		
		if(rightLimit == -1)
			sceneWidth = map->getWidth();
		else
			sceneWidth = Math::max(rightLimit-leftLimit, SCREEN_WIDTH);
		
		sceneHeight = map->getHeight();
		sceneRect = Rectanglef(leftLimit, sceneScroll.y, sceneWidth, sceneHeight);
	}
}
void Scene::checkHits()
{
	Rectanglef r;
	Hurtable* h;
	HeroProjectile* p;
	HurtableRect* hr;
	std::vector<HurtableRect*> rects;
	
	for(EntityNode* node1 = entityList.head; node1 != null; node1 = node1->next)
	{
		if(null != (p = dynamic_cast<HeroProjectile*>(node1->entity)))
		{
			r = node1->entity->bounds();
			for(EntityNode* node2 = entityList.head; node2 != null; node2 = node2->next)
			{
				if(null != (h = dynamic_cast<Hurtable*>(node2->entity)))
				{
					rects.clear();
					h->getHurtableRects(r, rects);
					for(unsigned int i = 0; i < rects.size(); i++)
					{
						HeroBomb* bomb;
						HeroBullet* bullet;
						
						if(null != (bomb = dynamic_cast<HeroBomb*>(p))) bomb->explode();
						else if(null != (bullet = dynamic_cast<HeroBullet*>(p))) bullet->hurt(rects[0]);
						
						break;
					}
				}
				else if(null != (hr = dynamic_cast<HurtableRect*>(node2->entity)))
				{
					if(hr->isHurtable() && hr->hurtableRect().intersects(r))
					{
						HeroBomb* bomb;
						HeroBullet* bullet;
						
						if(null != (bomb = dynamic_cast<HeroBomb*>(p))) bomb->explode();
						else if(null != (bullet = dynamic_cast<HeroBullet*>(p))) bullet->hurt(hr);
					}
				}
			}
		}
	}
}
void Scene::checkCollisions()
{
	EntityNode* node;
	EntityNode* next;
	Rectanglef rect = hero->collisionRect();
	Collisionable* otherCollisionable;
	for(node = entityList.head; node != null; node = next)
	{
		if(!hero->isRemovable()
			&& (hero != node->entity)
			&& (null != (otherCollisionable = dynamic_cast<Collisionable*>(node->entity))))
		{
			if(otherCollisionable->collisionRect().intersects(rect))
			{
				otherCollisionable->collide(hero);
			}
		}
		if(!node->entity->isRemovable())
		{
			next = node->next;
		}
		else
		{
			next = entityRemovableList.append(entityList, node);
		}
	}
}
