////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EntitySpawner
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/EntitySpawner.h>
#include <src/EntityParameters.h>
#include <src/Scene.h>
#include <src/Scene.h>

#include <tinyxml2/tinyxml2.h>

class EntityCreationNode
{
public:
	int					x;
	int					y;
	std::string			name;
	EntityParameters	params;
	int					spawnx;
	bool				spawned;
	int					spawningCount;
public:
	EntityCreationNode()
	{
	}
	~EntityCreationNode()
	{
	}
};

EntitySpawner::EntitySpawner()
{
}
EntitySpawner::~EntitySpawner()
{
	clear();
}
void EntitySpawner::read(tinyxml2::XMLElement* elem)
{
	const char* s;
	const tinyxml2::XMLAttribute* attr;
	tinyxml2::XMLElement*         attrElem;
	
	clear();
	for(elem = elem->FirstChildElement("Entity"); elem != null; elem = elem->NextSiblingElement())
	{
		EntityCreationNode* node = new EntityCreationNode();
		elem->QueryStringAttribute("x", &s);
		node->x = atoi(s);
		elem->QueryStringAttribute("y", &s);
		node->y = atoi(s);
		elem->QueryStringAttribute("class", &s);
		node->name = s;
		elem->QueryStringAttribute("spawnx", &s);
		node->spawnx = atoi(s);
		node->spawned = false;
		node->spawningCount = 0;
		
		if(null != (attrElem = elem->FirstChildElement("Arguments")))
		{
			for(attr = attrElem->FirstAttribute(); attr != null; attr = attr->Next())
			{
				node->params.insert(attr->Name(), attr->Value());
			}
		}
		creationList.push_back(node);
	}
}
void EntitySpawner::clear()
{
	for(std::list<EntityCreationNode*>::const_iterator it = creationList.begin(); it != creationList.end(); it++)
	{
		delete *it;
	}
	creationList.clear();
}
void EntitySpawner::reset(int x)
{
	for(std::list<EntityCreationNode*>::const_iterator it = creationList.begin(); it != creationList.end(); it++)
	{
		if((*it)->x >= x+60)
		{
			if((*it)->name == "Hero")
				continue;
			if((*it)->name == "Bonus_Pot")
				continue;
			if((*it)->name == "HiddenEgg" && (*it)->params.get("RespawnEntity", "").empty())
				continue;

			(*it)->spawned = false;
		}
	}
}
void EntitySpawner::spawnEntities(Scene* scene, HeroInfo& info)
{
	Hero* h = 0;
	for(std::list<EntityCreationNode*>::const_iterator it = creationList.begin(); it != creationList.end(); it++)
	{
		EntityCreationNode* node = (*it);
		int minX = scene->getCameraRect().getMinX();
		int maxX = scene->getCameraRect().getMaxX();
		if(node->x < minX)
		{
		}
		else if(node->spawnx > minX && node->spawnx <= maxX)
		{
			if(!node->spawned)
			{
				Entity* entity;
				if(null != (entity = createEntity(scene, node, info)))
				{
					node->spawned = true;
					node->spawningCount++;
					scene->addEntity(entity);

					//printf("entity: %s | x: %d | spawnx: %d | maxX: %d\n", node->name.c_str(), node->x, node->spawnx, maxX);
				}
			}
		}
	}
}
#include <src/entities/bonus/Bonus_Apple.h>
#include <src/entities/bonus/Bonus_Ax.h>
#include <src/entities/bonus/Bonus_Banana.h>
#include <src/entities/bonus/Bonus_Carrot.h>
#include <src/entities/bonus/Bonus_ExtraLife.h>
#include <src/entities/bonus/Bonus_Fireball.h>
#include <src/entities/bonus/Bonus_Flower.h>
#include <src/entities/bonus/Bonus_Gamepad.h>
#include <src/entities/bonus/Bonus_Milk.h>
#include <src/entities/bonus/Bonus_Pineapple.h>
#include <src/entities/bonus/Bonus_Pot.h>
#include <src/entities/bonus/Bonus_Skate.h>
#include <src/entities/bonus/Bonus_Tomato.h>

#include <src/entities/enemies/Bat.h>
#include <src/entities/enemies/Bird.h>
#include <src/entities/enemies/Cobra.h>
#include <src/entities/enemies/Coyote.h>
#include <src/entities/enemies/Frog.h>
#include <src/entities/enemies/Icicle.h>
#include <src/entities/enemies/Monster.h>
#include <src/entities/enemies/Pooter.h>
#include <src/entities/enemies/Pulposus.h>
#include <src/entities/enemies/Rock.h>
#include <src/entities/enemies/RockBall.h>
#include <src/entities/enemies/Skull.h>
#include <src/entities/enemies/Snail.h>
#include <src/entities/enemies/Spider.h>
#include <src/entities/enemies/Swordfish.h>
#include <src/entities/enemies/WoodFire.h>

#include <src/entities/hero/Hero.h>

#include <src/entities/platforms/PlatformFallDown.h>
#include <src/entities/platforms/PlatformFallUp.h>
#include <src/entities/platforms/PlatformFixed.h>
#include <src/entities/platforms/PlatformMoveTo.h>
#include <src/entities/platforms/PlatformScrollDown.h>
#include <src/entities/platforms/PlatformScrollUp.h>
#include <src/entities/platforms/PlatformZigZagHorz.h>
#include <src/entities/platforms/PlatformZigZagVert.h>

#include <src/entities/Egg.h>
#include <src/entities/HiddenEgg.h>
#include <src/entities/JumpSpring.h>
#include <src/entities/Label.h>

Entity* EntitySpawner::createEntity(Scene* scene, EntityCreationNode* node, HeroInfo& info)
{
	if(node->name == "AxAux")
	{
		/*
		if(node->spawningCount == 0)
		{
			node->spawned = true;
			node->spawningCount++;
			return null;
		}
		*/
		if(info.weapon == 0)
			return new Bonus_Ax(scene, node->x, node->y);
	}
	else if(node->name == "Bonus_Apple")		return new Bonus_Apple(scene, node->x, node->y);
	else if(node->name == "Bonus_Ax")			return new Bonus_Ax(scene, node->x, node->y);
	else if(node->name == "Bonus_Banana")		return new Bonus_Banana(scene, node->x, node->y);
	else if(node->name == "Bonus_Carrot")		return new Bonus_Carrot(scene, node->x, node->y);
	else if(node->name == "Bonus_ExtraLife")	return new Bonus_ExtraLife(scene, node->x, node->y);
	else if(node->name == "Bonus_Flower")		return new Bonus_Flower(scene, node->x, node->y);
	else if(node->name == "Bonus_Gamepad")		return new Bonus_Gamepad(scene, node->x, node->y);
	else if(node->name == "Bonus_Milk")			return new Bonus_Milk(scene, node->x, node->y);
	else if(node->name == "Bonus_Pineapple")	return new Bonus_Pineapple(scene, node->x, node->y);
	else if(node->name == "Bonus_Pot")			return new Bonus_Pot(scene, node->x, node->y);
	else if(node->name == "Bonus_Skate")		return new Bonus_Skate(scene, node->x, node->y);
	else if(node->name == "Bonus_Tomato")		return new Bonus_Tomato(scene, node->x, node->y);

	else if(node->name == "Bat")				return new Bat(scene, node->x, node->y, node->params.get("BaseY", "0").toInt());
	else if(node->name == "Bird")				return new Bird(scene, node->x, node->y, node->params.get("Egg", ""));
	else if(node->name == "Cobra")				return new Cobra(scene, node->x, node->y);
	else if(node->name == "Coyote")				return new Coyote(scene, node->x, node->y);
	else if(node->name == "Frog")				return new Frog(scene, node->x, node->y, node->params.get("Health", "1").toInt(), node->params.get("CanJump", "false").toBool());
	else if(node->name == "Icicle")				return new Icicle(scene, node->x, node->y);
	else if(node->name == "Monster")			return new Monster(scene, node->x, node->y, node->params.get("Type", "1").toInt());
	else if(node->name == "Pooter")				return new Pooter(scene, node->x, node->y);
	else if(node->name == "Pulposus")			return new Pulposus(scene, node->x, node->y, node->params.get("Health", "1").toInt());
	else if(node->name == "Rock")				return new Rock(scene, node->x, node->y);
	else if(node->name == "RockBall")			return new RockBall(scene, node->x, node->y);
	else if(node->name == "Skull")				return new Skull(scene, node->x, node->y);
	else if(node->name == "Snail")				return new Snail(scene, node->x, node->y);
	else if(node->name == "Spider")				return new Spider(scene, node->x, node->y, node->params.get("Min", "0").toInt(), node->params.get("Max", "0").toInt());
	else if(node->name == "Swordfish")			return new Swordfish(scene, node->x, node->y);
	else if(node->name == "WoodFire")			return new WoodFire(scene, node->x, node->y);

	else if(node->name == "Hero")				return new Hero(scene, node->x, node->y, info);
	
	else if(node->name == "PlatformFallDown")	return new PlatformFallDown(scene, node->x, node->y, node->params);
	else if(node->name == "PlatformFallUp")		return new PlatformFallUp(scene, node->x, node->y, node->params);
	else if(node->name == "PlatformFixed")		return new PlatformFixed(scene, node->x, node->y, node->params);
	else if(node->name == "PlatformMoveTo")		return new PlatformMoveTo(scene, node->x, node->y, node->params);
	else if(node->name == "PlatformScrollDown")	return new PlatformScrollDown(scene, node->x, node->y, node->params);
	else if(node->name == "PlatformScrollUp")	return new PlatformScrollUp(scene, node->x, node->y, node->params);
	else if(node->name == "PlatformZigZagHorz")	return new PlatformZigZagHorz(scene, node->x, node->y, node->params);
	else if(node->name == "PlatformZigZagVert")	return new PlatformZigZagVert(scene, node->x, node->y, node->params);

	else if(node->name == "Egg")
	{
		String entityName;
	
		/*
		if(node->spawningCount)
		{
			entityName = node->params.get("EntityAux", "");
		}
		*/
		if(info.weapon == 0)
		{
			entityName = node->params.get("EntityAux", "");
		}
		if(entityName.empty())
		{
			entityName = node->params.get("Entity", "");
		}
		return new Egg(scene, node->x, node->y, entityName);
	}
	else if(node->name == "HiddenEgg")
	{
		if(node->spawningCount > 0)
		{
			return new HiddenEgg(scene, node->x, node->y, node->params.get("RespawnEntity", ""));
		}
		return new HiddenEgg(scene, node->x, node->y, node->params.get("Entity", ""));
	}
	else if(node->name == "JumpSpring")			return new JumpSpring(scene, node->x, node->y, node->params.get("InitialState", "Down") == "Up" ? JumpSpring::STATE_UP : JumpSpring::STATE_DOWN);
	else if(node->name == "Label")				return new Label(scene, node->x, node->y, node->params.get("Type", "")[0]);

	return null;
}
