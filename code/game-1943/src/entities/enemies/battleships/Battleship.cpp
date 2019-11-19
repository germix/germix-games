////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Battleship
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/battleships/Battleship.h>
#include <src/Debug.h>
#include <src/Scene.h>
#include <src/ResourceManager.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/enemies/battleships/BattleshipTower.h>
#include <src/entities/enemies/battleships/BattleshipCannon.h>
#include <src/entities/enemies/battleships/BattleshipHangar.h>
#include <src/sprites/SpriteSheet.h>
#include <src/entities/enemies/weapons/EnemyWeapon_BigMissile.h>
#include <src/entities/enemies/weapons/EnemyWeapon_Simple.h>
#include <src/entities/enemies/weapons/EnemyWeapon_Missile.h>

#include <mach/Color.h>
#include <mach/String.h>
#include <mach/Texture.h>
#include <mach/Graphics.h>

#include <tmx/TmxMap.h>
#include <tmx/TmxObject.h>
#include <tmx/layers/TmxObjectLayer.h>

static char* getPath(const char* fname, char* path)
{
	char* p;
	
	p = (char*)strrchr(fname, '/');
	if(p == null)
		p = (char*)strrchr(fname, '\\');
	if(p == null)
	{
		p = path;
	}
	else
	{
		char* dst = path;
		const char* src = fname;
		while(src <= p)
		{
			*dst++ = *src++;
		}
		p = dst;
	}
	return p;
}

Battleship::Battleship(Scene* s, double x, double y, const std::string& fname) : Enemy(s, x, y)
, texture(null)
, destroyed(false)
{
	TmxMap* tmx = new TmxMap(fname.c_str());
	char  path[256];
	char* p = getPath(fname.c_str(), path);

	std::string model = tmx->getProperty("model");

	//
	// Obtener imagen
	//
	texture = res.findTexture(model.c_str());

	//
	// Comprobar sanidad de datos
	//
	{
		int mapWidth = tmx->getMapWidth()*tmx->getTileWidth();
		int mapHeight = tmx->getMapHeight()*tmx->getTileHeight();
		
		if(texture->getWidth() != mapWidth)
			printf("Barco con model=%s, tiene inconsistencia en el ancho\n", model.c_str());

		if(texture->getHeight() != mapHeight)
			printf("Barco con model=%s, tiene inconsistencia en el largo\n", model.c_str());
	}
	//
	// ...
	//
	std::vector<TmxObjectLayer*> objects = tmx->getObjectLayers();
	for(std::vector<TmxObjectLayer*>::const_iterator it = objects.begin(); it != objects.end(); it++)
	{
		TmxObjectLayer* layer = *it;
		
		//
		// Cargar torres
		//
		if(layer->getName() == "Towers")
		{
			for(std::vector<TmxObject*>::const_iterator it = layer->getObjects().begin(); it != layer->getObjects().end(); it++)
			{
				TmxObject* object = *it;
				int x = object->getX();
				int y = object->getY();
				int w = object->getWidth();
				int h = object->getHeight();
				String type = object->getType();
				Texture* texture = res.findTexture(type.c_str());
				
				towers.push_back(new BattleshipTower(scene, x + (w/2), y + (h/2), texture, this));
			}
		}
		//
		// Cargar cañones
		//
		else if(layer->getName() == "Cannons")
		{
			for(std::vector<TmxObject*>::const_iterator it = layer->getObjects().begin(); it != layer->getObjects().end(); it++)
			{
				TmxObject* object = *it;
				int x = object->getX();
				int y = object->getY();
				int w = object->getWidth();
				int h = object->getHeight();
				String type = object->getType();
				Sprite* sprite = res.findSpriteSheet("cannons")->getSprite(("cannon." + type).c_str());
				
				int health = 0;
				EnemyWeapon* weapon = null;
				
				if(type == "tank")
				{
					health = 180;
					weapon = new EnemyWeapon_BigMissile();
				}
				else if(w == 16)
				{
					health = 50;
					weapon = new EnemyWeapon_Simple();
				}
				else if(w == 32)
				{
					health = 70;
					weapon = new EnemyWeapon_Missile();
				}
				
				cannons.push_back(new BattleshipCannon(
						scene,
						x + (w/2),
						y + (h/2),
						this,
						sprite,
						health,
						weapon,
						type == "tank"));
			}
		}
	}
}
Battleship::~Battleship()
{
	for(unsigned int i = 0; i < towers.size(); i++)
		delete towers[i];
	for(unsigned int i = 0; i < cannons.size(); i++)
		delete cannons[i];
	for(unsigned int i = 0; i < hangars.size(); i++)
		delete hangars[i];
}
Rectanglef Battleship::rect() const
{
	double mw = texture->getWidth()/2;
	double mh = texture->getHeight()/2;
	return Rectanglef(pos.x-mw, pos.y-mh, mw*2, mh*2);
}
void Battleship::update(double dt)
{
	pos.y += (60*dt);
	
	updateComponents(dt);
}
void Battleship::render(Graphics* gr)
{
	//
	// Dibujar imágen del barco
	//
	int iw = texture->getWidth();
	int ih = texture->getHeight();
	int dx1 = (int)(pos.x - iw/2);
	int dy1 = (int)(pos.y - ih/2);
	int dx2 = dx1 + iw;
	int dy2 = dy1 + ih;
	int sx1 = 0;
	int sy1 = 0;
	int sx2 = iw;
	int sy2 = ih;
	
	gr->drawTexture(texture, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2);
	
	for(unsigned int i = 0; i < towers.size(); i++)
		towers[i]->render(gr);
	for(unsigned int i = 0; i < cannons.size(); i++)
		cannons[i]->render(gr);
#if 0
	for(unsigned int i = 0; i < hangars.size(); i++)
		hangars[i]->render(gr);
#endif
	if(Debug::showRectangle)
	{
		gr->drawRect(rect(), Color(255,0,0));
	}
}
bool Battleship::hurt(int damage)
{
	for(unsigned int i = 0; i < towers.size(); i++)
	{
		if(!towers[i]->isDestroyed()) towers[i]->hurt(damage);
	}
	for(unsigned int i = 0; i < cannons.size(); i++)
	{
		if(!cannons[i]->isDestroyed()) cannons[i]->hurt(damage);
	}
#if 0
	for(unsigned int i = 0; i < hangars.size(); i++)
	{
		if(!hangars[i]->isDestroyed()) hangars[i]->hurt(damage);
	}
#endif
	return false;
}
bool Battleship::isAlive() const
{
	return !destroyed;
}
bool Battleship::isDestroyed() const
{
	return destroyed;
}
int Battleship::getHealth() const
{
	int health = 0;

	for(unsigned int i = 0; i < towers.size(); i++)
	{
		health += towers[i]->getHealth();
	}
	for(unsigned int i = 0; i < cannons.size(); i++)
	{
		health += cannons[i]->getHealth();
	}
#if 0
	for(unsigned int i = 0; i < hangars.size(); i++)
	{
		health += hangars[i]->getHealth();
	}
#endif
	return health;
}
int Battleship::getDestructionScore() const
{
	return 10;
}
void Battleship::checkHit(HeroBullet* bullet)
{
	if(!cannons.empty())
	{
		destroyed = true;
		for(unsigned int i = 0; i < cannons.size(); i++)
		{
			cannons[i]->checkHit(bullet);
			if(!cannons[i]->isRemovable())
			{
				destroyed = false;
			}
		}
		if(destroyed)
		{
			for(unsigned int i = 0; i < towers.size(); i++)
			{
				towers[i]->destroy();
				delete towers[i];
			}
			for(unsigned int i = 0; i < cannons.size(); i++)
			{
				delete cannons[i];
			}
			towers.clear();
			cannons.clear();
			
			scene->getHero()->addScore(getDestructionScore());
		}
	}
}
void Battleship::updateComponents(double dt)
{
	for(unsigned int i = 0; i < towers.size(); i++)
		towers[i]->update(dt);
	for(unsigned int i = 0; i < cannons.size(); i++)
		cannons[i]->update(dt);
#if 0
	for(unsigned int i = 0; i < hangars.size(); i++)
		hangars[i]->update(dt);
#endif
}
