////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusPack
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/BonusPack.h>
#include <src/Debug.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/bullets/HeroBullet.h>
#include <src/Bonus.h>
#include <src/BonusManager.h>
#include <src/sprites/Sprite.h>

#include <mach/Mixer.h>
#include <mach/Color.h>
#include <mach/Graphics.h>

#define FRAME_PER_SECONDS		50
//#define FRAME_PER_SECONDS		62

BonusPack::BonusPack(Scene* scene, double x, double y, const String& bonusDescriptor) : Entity(scene, x, y)
, sprite(null)
, spriteTime()
, spriteIndex()

, bonusList()
, currentBonus(0)

, hitCount(0)
, interactive(true)
{
	Bonus* bonus;
	std::vector<String> bonusNames = bonusDescriptor.split(",");
	
	for(unsigned int i = 0; i < bonusNames.size(); i++)
	{
		printf("bonusNames[%d]: %s\n", i, bonusNames[i].c_str());
		if(null != (bonus = BonusManager::findBonus(bonusNames[i])))
		{
			bonusList.push_back(bonus);
		}
	}
	currentBonus = -1;
	if(!bonusList.empty())
	{
		currentBonus = 0;
		setupSprite();
	}
}
BonusPack::~BonusPack()
{
}
Rectanglef BonusPack::rect() const
{
	return sprite->rect(pos);
}
void BonusPack::update(double dt)
{
	pos.y += (FRAME_PER_SECONDS * dt);
	if(sprite != null)
	{
		spriteTime += dt;
		if(spriteTime > 0.2)
		{
			spriteTime -= 0.2;
			if(++spriteIndex == sprite->count)
			{
				spriteIndex = 0;
			}
		}
		if(!scene->getSceneRect().intersects(sprite->rect(pos)))
		{
			removable = true;
			interactive = false;
		}
	}
}
void BonusPack::render(Graphics* gr)
{
	if(sprite != null)
	{
		sprite->render(gr, pos.x, pos.y, spriteIndex);
	}
	if(Debug::showRectangle)
	{
		gr->drawRect(rect(), Color(255,0,0));
	}
}
void BonusPack::checkHit(HeroBullet* bullet)
{
	if(interactive && currentBonus != -1)
	{
		if(bonusList.size() > 1)		// Sólo si hay más de un bonus
		{
			if(rect().intersects(bullet->rect()))
			{
				pos.y -= 5;
				hitCount++;
				if(0 == (hitCount%2))
				{
					currentBonus++;
					if(currentBonus >= bonusList.size())
						currentBonus = 0;
					
					setupSprite();
				}
				bullet->destroy();
			}
		}
	}
}
void BonusPack::checkCollision(Entity* other)
{
	if(interactive && currentBonus != -1)
	{
		if(dynamic_cast<Hero*>(other))
		{
			Hero* hero = (Hero*)other;
			if(rect().intersects(hero->rect()))
			{
				bonusList[currentBonus]->action(scene, hero);
				removable = true;
				interactive = false;
				Mixer::playChannel(res.findSound("bonus"));
			}
		}
	}
}
void BonusPack::setupSprite()
{
	sprite = bonusList[currentBonus]->sprite();
	spriteTime = 0;
}
