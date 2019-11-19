////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Scene
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Scene.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/PixelMap.h>
#include <src/TexturedTileMap.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/platforms/Platform.h>
#include <src/entities/HiddenEgg.h>

#include <mach/Mixer.h>
#include <mach/String.h>
#include <mach/Graphics.h>
#include <mach/Image.h>
#include <mach/ImageLoader.h>
#include <mach/Texture.h>
#include <mach/TextureLoader.h>

#include <stdlib.h>
#include <tinyxml2/tinyxml2.h>

#include <gamelib/Font.h>

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

//const double Scene::GRAVITY = 2.0;
const double Scene::GRAVITY = 500.0;
const Vector2f Scene::GRAVITY_ACCELERATION(0, GRAVITY);

static std::list<Entity*>::const_iterator next_iter_of(std::list<Entity*>::const_iterator it)
{
	it++;
	return it;
}

Scene::Scene(HeroInfo& info, int area, int round)
: state(STATE_0)
, hero(null)
, entities()
, addedEntities()

, map(null)
, mapWidth(0)
, mapHeight(0)

, platforms()
, removables()
, background(null)
, ttmBackground(null)

, font(res.findFont("Font.1"))
, livesMark(res.findTexture("LivesMark"))
, healthMark(res.findTexture("HealthMark"))

, failed(false)
, completed(false)
, respawnPosition()
, availablesLives(-1)

, finishingClock(4)
, decreaseHealthClock(6)

, music(null)
, cameraX(0)
, cameraY(0)
, cameraOffsets(null)

, heroInfo(info)

, hideHeroInX(-1)
, musicStarted(false)
, monterCasterMusicX(-1)
, monterCasterMusicXStarted(false)

, disableHealthDecrement(false)
{
	if(area == -1)
		loadDummy();
	else
		loadScene(area, round);
}
Scene::~Scene()
{
	clear();
}
void Scene::update(double dt)
{
	if(state == STATE_FINISHED)
		return;
	if(state == STATE_FINISHING)
	{
		if(finishingClock.update(dt))
		{
			state = STATE_FINISHED;
			return;
		}
	}
	state = STATE_PLAYING;
	if(!musicStarted)
	{
		if(music)
		{
			musicStarted = true;
			Mixer::playMusic(music, -1);
		}
	}
	
	//
	// Actualizar las entidades
	//
	for(std::list<Entity*>::const_iterator it = entities.begin(); it != entities.end(); it++)
	{
		Entity* e = *it;
		e->update(dt);
		if(e->isRemovable())
		{
			removables.push_back(e);
		}
	}
	clearRemovables();
	
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
		for(std::list<Entity*>::const_iterator it2 = next_iter_of(it1); it2 != entities.end(); it2++)
		{
			Entity* e1 = *it1;
			Entity* e2 = *it2;
			
			if(e1->isRemovable())
				continue;
			if(e2->isRemovable())
				continue;
			
			if(e1->getCollisionRectangle().intersects(e2->getCollisionRectangle()))
			{
				// Notificar colisiones
				e1->collides(e2);
				e2->collides(e1);
				// Marcar como eliminables
				if(e1->isRemovable())
				{
					removables.push_back(e1);
				}
				if(e2->isRemovable())
				{
					removables.push_back(e2);
				}
			}
		}
	}
	clearRemovables();
	
	//
	// Crear nuevas entidades
	//
	entitySpawner.spawnEntities(this, heroInfo);
	
	//
	// ...
	//
	if(hero != null)
	{
		if(!Debug::disableHealthDecrement || !disableHealthDecrement)
		{
			if(decreaseHealthClock.update(dt))
			{
				if(0 == hero->decreaseHealth())
				{
					hero->dead();
				}
			}
		}
		if(hero->isDead())
		{
			failed = true;
			state = STATE_FINISHING;
		}
		else if(hero->bounds().getMinX() > mapWidth)
		{
			completed = true;
			state = STATE_FINISHING;
		}
		if(monterCasterMusicX != -1 && hero->getPosition().x > monterCasterMusicX)
		{
			if(!monterCasterMusicXStarted)
			{
				monterCasterMusicXStarted = true;
				Mixer::playMusic(res.findMusic("MonsterCastle"), -1);
				disableHealthDecrement = true;
			}
		}
	}
	
	//
	// Controlar camara
	//
	updateCamera();
}
void Scene::render(Graphics* gr)
{
	//
	// Dibujar fondo
	//
	{
		int dstX1 = 0;
		int dstY1 = 0;
		int dstX2 = SCREEN_WIDTH;
		int dstY2 = SCREEN_HEIGHT;
		
		int srcX1 = cameraX;
		int srcY1 = cameraY;
		int srcX2 = cameraX+SCREEN_WIDTH;
		int srcY2 = cameraY+SCREEN_HEIGHT;
		
		if(background != null)
		{
			gr->drawTexture(background,
					srcX1,
					srcY1,
					srcX2,
					srcY2,
					dstX1,
					dstY1,
					dstX2,
					dstY2);
		}
		else if(ttmBackground != null)
		{
			ttmBackground->render(gr, cameraX, cameraY);
		}
		
		if(Debug::showPixelMap)
		{
			map->render(gr,
					srcX1,
					srcY1,
					srcX2,
					srcY2,
					dstX1,
					dstY1,
					dstX2,
					dstY2);
		}
	}
	
	//
	// Pintar las entidades
	//
	gr->translate(-cameraX, -cameraY);
	for(std::list<Entity*>::const_iterator it = entities.begin(); it != entities.end(); it++)
	{
		Entity* e = *it;
		if(e != hero)
		{
			e->render(gr);
			if(Debug::showCollisionRect)
			{
				gr->drawRect(e->getCollisionRectangle(), Color(255,0,0));
			}
		}
	}
	if(hero != null)
	{
		if(hideHeroInX == -1 || hero->getPosition().x < hideHeroInX)
		{
			hero->render(gr);
		}
		if(Debug::showCollisionRect)
		{
			gr->drawRect(hero->getCollisionRectangle(), Color(255,0,0));
		}
	}
	gr->translate(+cameraX, +cameraY);
	
	//
	// HUD
	//
	if(hero != null && !disableHealthDecrement)
	{
		String s;
		const HeroInfo& info = hero->getInfo();
		
		//
		// Score
		//
		s = String::fromInt(info.score);
		font->render(gr, 136, 16, s.c_str());
		
		//
		// Vidas
		//
		gr->drawTexture(livesMark, 24, 24);
		if(info.lives == 0)
			s = String::fromInt(0);
		else
			s = String::fromInt(info.lives-1);
		font->render(gr, 24+16, 24, s.c_str());
		
		//
		// Health
		//
		{
			int x = 80;
			int y = 30;
			for(int i = 0; i < info.health; i++)
			{
				gr->drawTexture(healthMark, x, y);
				x += 5;
			}
		}
	}
}
void Scene::loadDummy()
{
	clear();
	background = TextureLoader::load("aisland/images/DummyBackground.png");
	Image* platformImage = ImageLoader::load("aisland/images/DummyPlatform.png");
	
	map = new PixelMap(platformImage);
	mapWidth = platformImage->getWidth();
	mapHeight = platformImage->getHeight();

	state = STATE_0;
	completed = false;
	heroInfo.reset();
}
void Scene::loadScene(int area, int round)
{
	String fname = "aisland/scenes/a" + String::fromInt(area) + "r" + String::fromInt(round) + ".xscene";
	char  path[256];
	char* semiPath = getPath(fname.c_str(), path);
	
	clear();
	
	tinyxml2::XMLError err;
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* root;
	
	err = doc.LoadFile(fname.c_str());
	if(err != tinyxml2::XML_SUCCESS)
		return;
	
	if(null != (root = doc.FirstChildElement("Scene")))
	{
		const char* s;
		
		root->QueryStringAttribute("camera", &s);
		const Rectangle cameraRect(s);
		cameraX = cameraRect.getX();
		cameraY = cameraRect.getY();
		
		readMap(path, semiPath, root->FirstChildElement("Map"));
		readMusic(path, semiPath, root->FirstChildElement("Music"));
		readEntities(path, semiPath, root->FirstChildElement("Entities"));

		tinyxml2::XMLElement* elem;
		if(null != (elem = root->FirstChildElement("Arguments")))
		{
			for(elem = elem->FirstChildElement("Argument"); elem != null; elem = elem->NextSiblingElement())
			{
				elem->QueryStringAttribute("name", &s);
				if(0 == strcmp(s, "Hide"))
				{
					elem->QueryStringAttribute("value", &s);
					hideHeroInX = atoi(s);
				}
				else if(0 == strcmp(s, "MonsterCastle"))
				{
					elem->QueryStringAttribute("value", &s);
					monterCasterMusicX = atoi(s);
				}
			}
		}
	}

	state = STATE_0;
	completed = false;
	heroInfo.reset();
}
void Scene::addEntity(Entity* entity)
{
	addedEntities.push_back(entity);
	if(dynamic_cast<Hero*>(entity))
	{
		hero = (Hero*)entity;
		availablesLives = hero->getInfo().lives-1;
		respawnPosition = hero->getPosition();
	}
	else if(dynamic_cast<Platform*>(entity))
	{
		platforms.push_back((Platform*)entity);
	}
}
unsigned int Scene::moveEntity(Entity* entity, double dt, Vector2f& pos, Vector2f& vel, const Vector2f& accel, bool onGround, unsigned int terrainTypes, unsigned int collisionFlags)
{
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
		return map->checkCollision(entity, pos, vel, oldPosition, oldVelocity, terrainTypes, collisionFlags);
	}
	return 0;
}
unsigned int Scene::checkCollision(Entity* entity, Vector2f& newPosition, Vector2f& newVelocity, const Vector2f& oldPosition, const Vector2f& oldVelocity, unsigned int terrainTypes, unsigned int collisionFlags) const
{
	return map->checkCollision(entity, newPosition, newVelocity, oldPosition, newPosition, terrainTypes, collisionFlags);
}
Rectanglef Scene::getCameraRect() const
{
	return Rectanglef(cameraX, cameraY, SCREEN_WIDTH, SCREEN_HEIGHT);
}
Hero* Scene::getHero() const
{
	return hero;
}
std::list<Platform*> Scene::getPlatforms() const
{
	return platforms;
}
bool Scene::isFinished() const
{
	return state == STATE_FINISHED;
}
bool Scene::isFailed() const
{
	return failed;
}
bool Scene::isCompleted() const
{
	return completed;
}
void Scene::setRespawnPosition(const Vector2f& vector)
{
	respawnPosition = vector;
}
void Scene::restart()
{
	state = STATE_PLAYING;
	hero->respawn(respawnPosition);
	cameraX = 0;
	updateCamera();
	finishingClock.reset();
	availablesLives = hero->getInfo().lives-1;
	entitySpawner.reset(respawnPosition.x);
	
	failed = false;
	completed = false;
	musicStarted = false;
	monterCasterMusicXStarted = false;

	platforms.clear();
	clearEntitiesNoHero(entities);
	clearEntitiesNoHero(addedEntities);
	entities.push_back(hero);
}
HiddenEgg* Scene::getHiddentEgg(const Rectanglef& r) const
{
	HiddenEgg* he;
	for(std::list<Entity*>::const_iterator it = entities.begin(); it != entities.end(); it++)
	{
		if(null != (he = dynamic_cast<HiddenEgg*>(*it)))
		{
			if(he->getCollisionRectangle().intersects(r))
			{
				return he;
			}
		}
	}
	return null;
}
void Scene::clear()
{
	for(std::list<Entity*>::const_iterator it = entities.begin(); it != entities.end(); it++)
	{
		delete *it;
	}
	for(std::list<Entity*>::const_iterator it = addedEntities.begin(); it != addedEntities.end(); it++)
	{
		delete *it;
	}
	platforms.clear();
	entities.clear();
	addedEntities.clear();
	entitySpawner.clear();
	
	delete map;
	if(background)
		delete background;
	if(ttmBackground)
		delete ttmBackground;
	if(cameraOffsets)
		delete [] cameraOffsets;
	
	Mixer::freeMusic(music);

	map = null;
	background = null;
	ttmBackground = null;
	cameraOffsets = null;
	music = null;
	musicStarted = false;

	hero = null;
	hideHeroInX = -1;
	monterCasterMusicX = -1;
	monterCasterMusicXStarted = false;

	disableHealthDecrement = false;

}
void Scene::clearEntitiesNoHero(std::list<Entity*>& ent)
{
	for(std::list<Entity*>::const_iterator it = ent.begin(); it != ent.end(); it++)
	{
		Entity* e = *it;
		if(e != hero)
			delete e;
	}
	ent.clear();
}
void Scene::readMap(const char* fullPath, char* semiPath, tinyxml2::XMLElement* elem)
{
	const char* value;
	Image* offsetsImage;
	
	//
	// Terreno
	//
	elem->QueryStringAttribute("platform", &value);
	strcpy(semiPath, value);
	map = new PixelMap(fullPath);
	mapWidth = map->getWidth();
	mapHeight = map->getHeight();
	
	//
	// Fondo
	//
	elem->QueryStringAttribute("background", &value);
	strcpy(semiPath, value);
	{
		char* p;
		std::string tmapfname;
		std::string tsetfname;
		
		p = strchr(semiPath, '.');
		strcpy(p, "-tilemap.txt");
		tmapfname = fullPath;
		strcpy(p, "-tileset.png");
		tsetfname = fullPath;
		
		ttmBackground = new TexturedTileMap(
					map->getWidth(),
					map->getHeight(),
					tmapfname.c_str(),
					tsetfname.c_str());
	}
	
	//
	// Desplazamientos verticales de la camara
	//
	elem->QueryStringAttribute("offsets", &value);
	strcpy(semiPath, value);
	if(null != (offsetsImage = ImageLoader::load(fullPath)))
	{
		int x;
		int y;
		int width = offsetsImage->getWidth();
		int height = offsetsImage->getHeight();
		
		cameraOffsets = new int[width];
		for(x = 0; x < width; x++)
		{
			for(y = height-1; y >= 0; y--)
			{
				if(offsetsImage->getColor(x, y).alpha() == 0)
				{
					break;
				}
			}
			cameraOffsets[x] = y+1;
		}
		delete offsetsImage;
	}
	else
	{
		cameraOffsets = new int[mapWidth];
		for(int x = 0; x < mapWidth; x++)
		{
			cameraOffsets[x] = map->getHeight();
		}
	}
}
void Scene::readMusic(const char* fullPath, char* semiPath, tinyxml2::XMLElement* elem)
{
	const char* value;
	
	elem->QueryStringAttribute("music", &value);
	strcpy(semiPath, value);
	music = Mixer::loadMusic(fullPath);
}
void Scene::readEntities(const char* fullPath, char* semiPath, tinyxml2::XMLElement* elem)
{
	entitySpawner.read(elem);
}
void Scene::updateCamera()
{
	if(hero != null)
	{
		int x = (int)(hero->getPosition().x - SCREEN_WIDTH/2.0);
		if(x >= cameraX)
		{
			if(x < 0)
				x = 0;
			if(cameraX+SCREEN_WIDTH >= mapWidth - 1)
				x = mapWidth - SCREEN_WIDTH;

			cameraX = x;
		}
	}
	if(cameraOffsets == null)
		cameraY = 0;
	else
		cameraY = cameraOffsets[cameraX+SCREEN_WIDTH-1] - SCREEN_HEIGHT;
	
	if(cameraY < 0)
	{
		cameraY = 0;
	}
	if(cameraY + SCREEN_HEIGHT > mapHeight)
	{
		cameraY = mapHeight - SCREEN_HEIGHT;
	}
}
void Scene::clearRemovables()
{
	for(std::list<Entity*>::const_iterator it = removables.begin(); it != removables.end(); it++)
	{
		Entity* e = *it;
		entities.remove(e);
		if(dynamic_cast<Platform*>(e))
		{
			platforms.remove((Platform*)e);
		}
		delete e;
	}
	removables.clear();
}
