////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MissionMap
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/scene/MissionMap.h>
#include <src/Config.h>
#include <src/scene/Scene.h>
#include <src/scene/MissionMapRenderable.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/enemies/Enemy.h>
#include <src/___/CollisionInfo.h>

#include <mach/Math.h>
#include <mach/Mixer.h>
#include <mach/Image.h>
#include <mach/Graphics.h>

static const Color COLOR_COLLISION_FULL(0,0,0);
static const Color COLOR_COLLISION_TOPDOWN(255,0,0);

static bool checkIntersection(Image* image, const Rectanglef& testRectangle, const Rectanglef& spriteRectangle, Rectanglef& pixelIntersection, const Color& testColor)
{
	int dx1 = 0;
	int dy1 = 0;
	/*
	int dx2 = 0;
	int dy2 = 0;
	*/
	Rectanglef r1 = testRectangle;
	Rectanglef r2 = spriteRectangle;
	Rectanglef ri = r1.intersected(r2);

	if(!ri.isEmpty())
	{
		int minX = (int)ri.getWidth();
		int minY = (int)ri.getHeight();
		int maxX = 0;
		int maxY = 0;
		
		if(r2.getMinY() > r1.getMinY())
			dy1 = (int)(r2.getMinY() - r1.getMinY());
		if(r2.getMinX() > r1.getMinX())
			dx1 = (int)(r2.getMinX() - r1.getMinX());

		/*
		if(r1.getMinY() > r2.getMinY())
			dy2 = (int)(r1.getMinY() - r2.getMinY());
		if(r1.getMinX() > r2.getMinX())
			dx2 = (int)(r1.getMinX() - r2.getMinX());
		*/
		for(int y = 0; y < ri.getHeight(); y++)
		{
			for(int x = 0; x < ri.getWidth(); x++)
			{
				if(image->getColor(dx1 + x, dy1 + y) == testColor)
				{
					minX = Math::min(minX, x);
					minY = Math::min(minY, y);
					maxX = Math::max(maxX, x);
					maxY = Math::max(maxY, y);
				}
			}
		}
		pixelIntersection = Rectanglef((int)ri.getMinX() + minX, (int)ri.getMinY() + minY, maxX-minX+1, maxY-minY+1);
		
		return !pixelIntersection.isEmpty();
	}
	return false;
}
static bool checkIntersectionFromBottom(Image* image, const Rectanglef& testRectangle, const Rectanglef& spriteRectangle, Rectanglef& pixelIntersection, const Color& testColor)
{
	int dx1 = 0;
	int dy1 = 0;
	/*
	int dx2 = 0;
	int dy2 = 0;
	*/
	Rectanglef r1 = testRectangle;
	Rectanglef r2 = spriteRectangle;
	Rectanglef ri = r1.intersected(r2);

	if(!ri.isEmpty())
	{
		int minX = (int)ri.getWidth();
		int minY = (int)ri.getHeight();
		int maxX = 0;
		int maxY = 0;
		
		if(r2.getMinY() > r1.getMinY())
			dy1 = (int)(r2.getMinY() - r1.getMinY());
		if(r2.getMinX() > r1.getMinX())
			dx1 = (int)(r2.getMinX() - r1.getMinX());
		
		for(int y = (int)(ri.getHeight()-1); y >= 0; y--)
		{
			bool colorMatch = false;
			for(int x = 0; x < ri.getWidth(); x++)
			{
				if(testColor == image->getColor(dx1 + x, dy1 + y))
				{
					minX = Math::min(minX, x);
					minY = Math::min(minY, y);
					maxX = Math::max(maxX, x);
					maxY = Math::max(maxY, y);
					colorMatch = true;
				}
			}
			if(!colorMatch)
				break;
		}
		pixelIntersection = Rectanglef((int)ri.getMinX() + minX, (int)ri.getMinY() + minY, maxX-minX+1, maxY-minY+1);
		
		return !pixelIntersection.isEmpty();
	}
	return false;
}
MissionMap::EntitySpawnNode::EntitySpawnNode(const char* _type)
{
	next = null;
	prev = null;
	type = strdup(_type);
}
MissionMap::EntitySpawnNode::~EntitySpawnNode()
{
	free((void*)type);
}
MissionMap::~MissionMap()
{
	if(slopes)
		delete [] slopes;
	if(terrain)
		delete terrain;
	if(missionMusic)
	{
		Mixer::halt();
		Mixer::freeMusic(missionMusic);
	}
}
Vector2f MissionMap::getSuggestedSceneScroll(Entity* entity) const
{
	Vector2f pos = entity ? entity->getPosition() : Vector2f();
	int      posX = (int)pos.x;
	int      posY = (int)pos.y;
	int      minX = 0;
	int      maxX = width;
	int      minY = 0;
	int      maxY = height;
	int      scrollX;
	int      scrollY;
	
	//
	// Calcular desplazamiento en X
	//
	scrollX = posX - SCREEN_WIDTH/2;
	if(scrollX < minX)
		scrollX = minX;
	else if(scrollX >= maxX-SCREEN_WIDTH)
		scrollX = maxX-SCREEN_WIDTH;
	
	//
	// Calcular desplazamiento en Y
	//
	if(slopes == null)
	{
		scrollY = posY - SCREEN_HEIGHT/2;
	}
	else
	{
		int ohi;
		
		ohi = scrollX+SCREEN_WIDTH;
		ohi = (ohi >= width) ? width-1 : ohi;
		scrollY = slopes[ohi]-SCREEN_HEIGHT;
	}
	if(scrollY < minY)
		scrollY = minY;
	else if(scrollY > maxY-SCREEN_HEIGHT)
		scrollY = maxY-SCREEN_HEIGHT;
	
	return Vector2f(scrollX, scrollY);
}
void MissionMap::update(Scene* scene, double dt)
{
	if(!isPlayingMusic)
	{
		isPlayingMusic = true;
		Mixer::playMusic(missionMusic);
	}
	Hero* hero = scene->getHero();
	for(std::vector<MissionMapRenderable*>::const_iterator it = backgrounds.begin(); it != backgrounds.end(); it++)
	{
		(*it)->update(dt);
	}
	for(std::vector<MissionMapRenderable*>::const_iterator it = foregrounds.begin(); it != foregrounds.end(); it++)
	{
		(*it)->update(dt);
	}
	if(hero != null && hero->isLoser())
	{
		Mixer::halt(2000);
		scene->markMissionFailed();
	}
	else if(finalBoss != null && finalBoss->isDestroyed())
	{
		Mixer::halt(2000);
		scene->markMissionCompleted();
	}
	else
	{
		//
		// Agregar nuevas entidades
		//
		Entity* entity;
		int off = (int)scene->getCameraRect().getMaxX()+40;
		EntitySpawnNode* next;
		EntitySpawnNode* node = entitySpawner.head;
		
		while(node != null)
		{
			next = node->next;
			if(node->x < off)
			{
				if(null != (entity = newEntity(scene, node)))
				{
					scene->addEntity(entity);
					if(node->boss)
						finalBoss = (Enemy*)entity;
				}

				//
				// Desenlazar de la lista y eliminar
				//
				if(node->prev)
					node->prev->next = node->next;
				if(node->next)
					node->next->prev = node->prev;
				if(entitySpawner.head == node)
					entitySpawner.head = entitySpawner.head->next;
				if(entitySpawner.tail == node)
					entitySpawner.tail = entitySpawner.tail->prev;
				
				delete node;
			}
			node = next;
		}
	}
}
void MissionMap::renderBackground(Graphics* gr, int sx, int sy) const
{
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, backgroundColor);

	for(std::vector<MissionMapRenderable*>::const_iterator it = backgrounds.begin(); it != backgrounds.end(); it++)
	{
		(*it)->render(gr, sx, sy);
	}
}
void MissionMap::renderForeground(Graphics* gr, int sx, int sy) const
{
	for(std::vector<MissionMapRenderable*>::const_iterator it = foregrounds.begin(); it != foregrounds.end(); it++)
	{
		(*it)->render(gr, sx, sy);
	}
}
unsigned int MissionMap::checkCollision(
						Entity* entity,
						Vector2f& newPosition,
						Vector2f& newVelocity,
						const Vector2f& oldPosition,
						const Vector2f& oldVelocity,
						unsigned int terrainType) const
{
	unsigned int flags = 0;
	Rectanglef rc;
	Rectanglef testRectangle(0,0,terrain->getWidth(), terrain->getHeight());
	Rectanglef pixelIntersection;
	
	if(terrainType & MAP_TERRAIN_SOLID)
	{
		//
		// Colisión en X
		//
		if(newVelocity.x > 0 || newVelocity.x < 0)
		{
			if(newVelocity.x > 0)
				rc = entity->bounds(Math::ceil(newPosition.x), oldPosition.y);
			else
				rc = entity->bounds(Math::floor(newPosition.x), oldPosition.y);
			if(checkIntersection(terrain, testRectangle, rc, pixelIntersection, COLOR_COLLISION_FULL))
			{
				if(((int)pixelIntersection.getHeight() == 1 || (int)pixelIntersection.getHeight() == 2)
						&& (rc.getMaxY() == pixelIntersection.getMaxY()))
				{
					//if(newVelocity.y > 0)
					{
						newPosition.y = pixelIntersection.getMinY();
						newVelocity.y = 0;
						flags |= COLLISION_FLAG_BOTTOM;
					}
				}
				else
				{
					if(newVelocity.x < 0)
						flags |= COLLISION_FLAG_LEFT;
					if(newVelocity.x > 0)
						flags |= COLLISION_FLAG_RIGHT;
					newVelocity.x = 0;
					newPosition.x = oldPosition.x;
				}
			}
		}
		//
		// Colisión en Y
		//
		if(newVelocity.y > 0 || newVelocity.y < 0)
		{
			if(newVelocity.y > 0)
				rc = entity->bounds(newPosition.x, Math::ceil(newPosition.y));
			else
				rc = entity->bounds(newPosition.x, Math::floor(newPosition.y));
			
			if(checkIntersection(terrain, testRectangle, rc, pixelIntersection, COLOR_COLLISION_FULL))
			{
				if(newVelocity.y > 0)
				{
					flags |= COLLISION_FLAG_BOTTOM;
					newPosition.y = pixelIntersection.getMinY();
					newVelocity.y = 0;
				}
				else if(newVelocity.y < 0)
				{
					//if(pixelIntersection.getMinY() == rc.getMinY())
					{
						flags |= COLLISION_FLAG_TOP;
						newPosition.y = (int)(pixelIntersection.getMaxY()+rc.getHeight());
						newVelocity.x = 0;
						newVelocity.y /= 2;
					}
				}
			}
		}
	}
	if(terrainType & MAP_TERRAIN_TOPDOWN)
	{
		//
		// Colisión en Y
		//
		if(newVelocity.y > 0)
		{
			rc = entity->bounds(newPosition.x, Math::ceil(newPosition.y));
			if(checkIntersectionFromBottom(terrain, testRectangle, rc, pixelIntersection, COLOR_COLLISION_TOPDOWN))
			{
			//	if((int)rc.getMaxY() == (int)pixelIntersection.getMaxY())
				{
					flags |= COLLISION_FLAG_BOTTOM;
					newPosition.y = pixelIntersection.getMinY();
					newVelocity.y = 0;
				}
			}
		}
	}
	return flags;
}
#include <src/entities/enemies/soldier/Soldier.h>
#include <src/entities/enemies/rshobu/RShobu.h>
#include <src/entities/enemies/sarubia/Sarubia.h>
#include <src/entities/enemies/mosque/Mosque.h>
#include <src/entities/enemies/mosque/Mosque.h>
#include <src/entities/enemies/bradley/Bradley.h>
#include <src/entities/enemies/masknell/MasknellFleet.h>
#include <src/entities/enemies/nokana/IronNokana.h>
#include <src/entities/friendly/Hostage.h>
#include <src/entities/bonus/HiddenBonus.h>
#include <src/entities/bonus/Bonus_Monkey.h>
Entity* MissionMap::newEntity(Scene* scene, EntitySpawnNode* node)
{
	if(0 == strcmp(node->type, "Soldier"))				return new Soldier(scene, node->x, node->y);
	else if(0 == strcmp(node->type, "RShobu"))			return new RShobu(scene, node->x, node->y);
	else if(0 == strcmp(node->type, "Sarubia"))			return new Sarubia(scene, node->x, node->y);
	else if(0 == strcmp(node->type, "Mosque"))			return new Mosque(scene, node->x, node->y);
	else if(0 == strcmp(node->type, "Bradley"))			return new Bradley(scene, node->x, node->y);
	else if(0 == strcmp(node->type, "MasknellFleet"))	return new MasknellFleet(scene, node->x, node->y);
	else if(0 == strcmp(node->type, "IronNokana"))		return new IronNokana(scene, node->x, node->y);

	else if(0 == strcmp(node->type, "Hostage"))			return new Hostage(scene, node->x, node->y, node->params.get("bonus", "Coin"));
	else if(0 == strcmp(node->type, "HiddenBonus"))		return new HiddenBonus(scene, node->x, node->y, atoi(node->params.get("health", "1")), node->params.get("bonus", "Coin"));
	
	else if(0 == strcmp(node->type, "Bonus_Monkey"))	return new Bonus_Monkey(scene, node->x, node->y);
	
	printf("Entity \'%s\' no created\n", node->type);
	return null;
}


