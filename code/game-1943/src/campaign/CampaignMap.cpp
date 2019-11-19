////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CampaignMap
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/campaign/CampaignMap.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <tmx/TmxMap.h>
#include <tmx/TmxObject.h>
#include <tmx/layers/TmxImageLayer.h>
#include <tmx/layers/TmxObjectLayer.h>

#include <mach/Math.h>
#include <mach/String.h>
#include <mach/Graphics.h>
#include <mach/Texture.h>
#include <mach/TextureLoader.h>

#include <src/sprites/Sprite.h>
#include <src/sprites/SpriteSheet.h>
#include <src/Scene.h>
#include <src/ResourceManager.h>
#include <src/entities/enemies/aircrafts/Aircraft.h>
#include <src/entities/enemies/aircrafts/AircraftPath.h>
#include <src/entities/enemies/aircrafts/AircraftTroop.h>
#include <src/entities/enemies/aircrafts/behaviors/AircraftBehavior_Immelman.h>
#include <src/entities/enemies/aircrafts/behaviors/AircraftBehavior_Kamikaze.h>
#include <src/entities/enemies/aircrafts/behaviors/AircraftBehavior_BigBombardier.h>
#include <src/entities/enemies/aircrafts/behaviors/AircraftBehavior_VerticalS.h>
#include <src/entities/enemies/aircrafts/behaviors/AircraftBehavior_Patrol.h>
#include <src/entities/enemies/battleships/Battleship.h>
#include <src/entities/enemies/battleships/BossBattleship.h>

#include <gamelib/TimeClock.h>

#include <src/entities/BonusPack.h>
#include <src/entities/enemies/EnemyWeaponHandler.h>
#include <src/entities/enemies/weapons/EnemyWeapon_BigMissile.h>
#include <src/entities/enemies/weapons/EnemyWeapon_Missile.h>
#include <src/entities/enemies/weapons/EnemyWeapon_Multi.h>
#include <src/entities/enemies/weapons/EnemyWeapon_Simple.h>

//
// Los aviones rojos (en tropa) no tienen armas
// Si hasAircraftTroop es true, no se crea armas
//
static EnemyWeaponHandler* getAircraftWeapon(const String& weaponType, bool hasAircraftTroop)
{
	if(weaponType == "multi")
	{
		return new EnemyWeaponHandler(new EnemyWeapon_Multi(), 2.0, 70);
	}
	else if(weaponType == "simple")
	{
		if(!hasAircraftTroop)
			return new EnemyWeaponHandler(new EnemyWeapon_Simple(), 3.0, 100);
		return null;
	}
	else if(weaponType == "none")
	{
		return null;
	}
	return new EnemyWeaponHandler(new EnemyWeapon_Multi(), 1.7, 60);
}

CampaignMap::CampaignMap(Scene* s, const std::string& fname)
: state(STATE_INIT)
, width(0)
, height(0)
, offset(0)
, scene(s)
, entities()
, oceanTexture(null)
, cloudsTexture(null)
{
	TmxMap* tmx = new TmxMap(("1943/campaign/" + fname).c_str());

	width = tmx->getMapWidth()*tmx->getTileWidth();
	height = tmx->getMapHeight()*tmx->getTileHeight();
	
	entities.resize(height);

	initImageLayers(tmx->getImageLayers());
	initObjectLayers(tmx->getObjectLayers());
	
	delete tmx;
}
CampaignMap::~CampaignMap()
{
	for(unsigned int i = 0; i < entities.size(); i++)
	{
		for(unsigned int j = 0; j < entities[i].size(); j++)
		{
			delete entities[i].at(j);
		}
		entities[i].clear();
	}
	entities.clear();
}
void CampaignMap::init()
{
	offset = SCENE_HEIGHT;
	insertEntitiesInScene(0, 0, offset);
}
void CampaignMap::update(double dt)
{
	switch(state)
	{
		case STATE_INIT:
			state = STATE_COMBAT;
			break;
		case STATE_COMBAT:
			{
				double fps = 62;		// 62 marcos por segundo
				double oldOffset = offset;
				double newOffset = offset + (fps*dt);
				double maxOffset = Math::min(newOffset, (double)height);

				//
				// ...
				//
				if(newOffset > maxOffset)
				{
					state = STATE_ENDED;
					newOffset = maxOffset;
				}
				offset = newOffset;
				insertEntitiesInScene(dt, oldOffset, newOffset);
			}
			break;
		case STATE_ENDED:
			break;
	}
}
void CampaignMap::render(Graphics* gr)
{
	if(oceanTexture != null)
	{
		int dy = (int)offset;
		
		gr->drawTexture(
			oceanTexture,
			0,
			oceanTexture->getHeight() - int(offset),
			width,
			SCENE_HEIGHT + (oceanTexture->getHeight() - int(offset)),
			
			0,
			0,
			SCENE_WIDTH,
			SCENE_HEIGHT);

		if(cloudsTexture)
		{
			gr->drawTexture(
				cloudsTexture,
				0,
				cloudsTexture->getHeight() - int(offset),
				width,
				SCENE_HEIGHT + (cloudsTexture->getHeight() - int(offset)),
				
				0,
				0,
				SCENE_WIDTH,
				SCENE_HEIGHT,
				
				170);
		}
	}
}
bool CampaignMap::isEnded() const
{
	return (state == STATE_ENDED);
}
const BossStatistics* CampaignMap::getBossStatistics() const
{
	return bossStatistics;
}
void CampaignMap::initImageLayers(const std::vector<TmxImageLayer*>& layers)
{
	oceanTexture = null;
	cloudsTexture = null;
	
	//
	// Cargar imágenes
	//
	for(unsigned int i = 0; i < layers.size(); i++)
	{
		TmxImageLayer* layer = layers[i];
		
		if(layer->getName() == "Ocean")
		{
			if(layer->getImage() == "stageA-ocean.png")
				oceanTexture = res.findTexture("ocean_a");
			else
				oceanTexture = res.findTexture("ocean_b");
		}
		else if(layer->getName() == "Clouds")
		{
			cloudsTexture = res.findTexture("clouds");
		}
	}
}
void CampaignMap::readObjectLayer(const TmxObjectLayer* layer)
{
	AircraftTroop* aircraftTroop = null;
	{
		std::string bonusDescriptor = layer->getProperty("bonus");
		
		if(!bonusDescriptor.empty())
		{
			aircraftTroop = new AircraftTroop(bonusDescriptor);
		}
	}
	int startY = 0;
	std::vector<Entity*> entityList;

	//
	// Calcular startY, o sea del primer objeto del grupo en coordenadas y
	//
	for(std::vector<TmxObject*>::const_iterator it = layer->getObjects().begin(); it != layer->getObjects().end(); it++)
	{
		TmxObject* object = *it;
		startY = Math::max(startY, object->getY()+object->getHeight());
	}
	//
	// Crear objetos
	//
	for(std::vector<TmxObject*>::const_iterator it = layer->getObjects().begin(); it != layer->getObjects().end(); it++)
	{
		TmxObject* object = *it;
		int x = object->getX();
		int y = object->getY();
		
		if(object->getType() == "Aircraft" || object->getType() == "AircraftTroop")
		{
			int w = object->getWidth();
			int h = object->getHeight();
			int dy = 0;
			String   sDY = object->getProperty("dy");
			String   model = object->getProperty("model");
			String   behavior = object->getProperty("behavior");
			String   health = object->getProperty("health");
			String   velocity = object->getProperty("velocity");
			String   weapon = object->getProperty("weapon");
			// ...
			Aircraft*			aircraft = null;
			Vector2f			aircraftPos;
			Sprite*				aircraftSprite = null;
			AircraftBehavior*	aircraftBehavior = null;
			EnemyWeaponHandler*	aircraftWeapon = null;
			
			if(!sDY.empty())
			{
				dy = sDY.toInt();
			}
			if(aircraftTroop != null)
			{
				dy += (startY-y);
			}
			if(model.empty())
			{
				behavior = "kamikaze";
				printf("Existe un avión sin \"behavior\", se selecciona por defecto behavior=kamikaze\n");
			}
			if(velocity.empty())
			{
				velocity = "150";
				printf("Existe un avión sin \"velocity\", se selecciona por defecto velocity=150\n");
			}
			//
			// Crear posición, sprite y comportamiento
			//
			if(behavior == "kamikaze")
			{
				if(null != (aircraftSprite = res.findSpriteSheet("aircrafts")->getSprite(("aircraft." + model + ".360").c_str())))
				{
					aircraftPos = Vector2f(x+(w/2), -dy - (h/2));
					aircraftBehavior = new AircraftBehavior_Kamikaze(scene, velocity.toInt());
				}
			}
			else if(behavior == "immelman")
			{
				if(null != (aircraftSprite = res.findSpriteSheet("aircrafts")->getSprite(("aircraft." + model + ".immelman").c_str())))
				{
					aircraftPos = Vector2f(x+(w/2), -dy - (h/2));
					aircraftBehavior = new AircraftBehavior_Immelman(scene, velocity.toInt());
				}
			}
			else if(behavior == "bombardier")
			{
				if(null != (aircraftSprite = res.findSpriteSheet("aircrafts")->getSprite("aircraft.big.1")))
				{
					int sceneWidth = SCENE_WIDTH;
					int sceneHeight = SCENE_HEIGHT;
					int enteringLimit = sceneHeight - (sceneHeight / 4);
					int horizontalMovementLength = sceneWidth - x - w;
					
					aircraftPos = Vector2f(x+(w/2), sceneHeight-h);
					aircraftBehavior = new AircraftBehavior_BigBombardier(
						scene,
						velocity.toInt(),
						enteringLimit,
						horizontalMovementLength);
					
					//
					// Usar valores predefinidos para este tipo de avión
					//
					health = "200";
					weapon = "multi";
				}
			}
			else if(behavior == "support.u")
			{
				AircraftPath* path;
				
				if(null != (aircraftSprite = res.findSpriteSheet("aircrafts")->getSprite(("aircraft." + model).c_str())))
				{
					path = AircraftPath::createU(
							Vector2f(width/4, dy - (h/2)),
							false,
							150,
							width - (width/2));
					
					aircraftPos = path->firstPoint();
					aircraftBehavior = new AircraftBehavior_Patrol(path, 0, velocity.toInt());
				}
			}
			else if(behavior == "vertical.s")
			{
				if(null != (aircraftSprite = res.findSpriteSheet("aircrafts")->getSprite(("aircraft." + model + ".straight-s").c_str())))
				{
					aircraftPos = Vector2f(x+(w/2), dy - (h/2));
					aircraftBehavior = new AircraftBehavior_VerticalS(velocity.toInt());
				}
			}
			if(health.empty())
			{
				health = "10";
				printf("Existe un avión sin \"health\", se selecciona por defecto health=10\n");
			}
			if(weapon.empty())
			{
				weapon = "simple";
			}
			//
			// Crear arma
			//
			aircraftWeapon = getAircraftWeapon(weapon, aircraftTroop != null);

			//
			// Crear avión
			//
			if(aircraftSprite != null && aircraftBehavior != null)
			{
				aircraft = new Aircraft(
						scene,
						aircraftPos.x,
						aircraftPos.y,
						health.toInt(),
						aircraftSprite,
						aircraftTroop,
						aircraftBehavior,
						aircraftWeapon);
			}

			//
			// Si se creó el avión, agregarlo a la lista, sino, notificarlo
			//
			if(aircraft != null)
			{
				if(aircraftTroop != null)
				{
					aircraftTroop->add(aircraft);
					addObjectToDataList(startY, aircraft);
				}
				else
				{
					addObjectToDataList(y, aircraft);
				}
			}
			else
			{
				printf("No se puede crear un avión. Modelo: %s, Comportamiento: %s\n", model.c_str(), behavior.c_str());
			}
		}
		else if(object->getType() == "AircraftPath")
		{
			String dy = object->getProperty("dy");
			String polyLine = object->getPolyline();
			String unitCount = object->getProperty("count");
			
			if(dy.empty())
			{
				dy = "45";
			}
			if(unitCount.empty())
			{
				unitCount = "5";
				printf("Existe una tropa sin \"counts\", se selecciona por defecto counts=5\n");
			}
			Aircraft*     aircraft;
			AircraftPath* aircraftPath = AircraftPath::createFromDescriptor(polyLine, dy.toInt());
			String        aircraftModel = object->getProperty("model");
			String        aircraftHealth = "10";
			String        aircraftVelocity = object->getProperty("velocity");
			int DISTANCE_BETWEEN_AIRCRAFTS = 16+16;
			
			if(aircraftModel.empty())
			{
				aircraftModel = "red2";
			}
			if(aircraftVelocity.empty())
			{
				aircraftVelocity = "110";
			}
			
			for(int i = 0; i < unitCount.toInt(); i++)
			{
				Vector2f          aircraftPos = aircraftPath->firstPoint();
				Sprite*           aircraftSprite = res.findSpriteSheet("aircrafts")->getSprite(("aircraft." + aircraftModel + ".360").c_str());
				AircraftBehavior* aircraftBehavior = new AircraftBehavior_Patrol(
						aircraftPath,
						(i * DISTANCE_BETWEEN_AIRCRAFTS)*-1,
						aircraftVelocity.toInt());
				
				// ...
				aircraft = new Aircraft(
						scene,
						aircraftPos.x,
						aircraftPos.y,
						aircraftHealth.toInt(),
						aircraftSprite,
						aircraftTroop,
						aircraftBehavior,
						null);
				
				aircraftTroop->add(aircraft);
				addObjectToDataList(y, aircraft);
			}
		}
		else if(object->getType() == "Battleship")
		{
			int w = object->getWidth();
			int h = object->getHeight();
		
			Battleship* battleship = new Battleship(
					scene,
					x+(w/2),
					-h,
					"1943/campaign/battleships/" + object->getProperty("file") + ".tmx");
			
			addObjectToDataList(y+h, battleship);
		}
		else if(object->getType() == "BossBattleship")
		{
			int w = object->getWidth();
			int h = object->getHeight();
			
			BossBattleship* battleship = new BossBattleship(
				scene,
				x+(w/2),
				-h,
				"1943/campaign/battleships/" + object->getProperty("file") + ".tmx");
			
			bossStatistics = dynamic_cast<BossStatistics*>(battleship);
			
			addObjectToDataList(y+h, battleship);
		}
	}
}
void CampaignMap::initObjectLayers(const std::vector<TmxObjectLayer*>& layers)
{
	//
	// Cargar objetos
	//
	for(unsigned int i = 0; i < layers.size(); i++)
	{
		readObjectLayer(layers[i]);
	}
}
void CampaignMap::insertEntitiesInScene(double dt, double oldOffset, double newOffset)
{
#if 1
	for(int i = (int)oldOffset; i < (int)newOffset; i++)
	{
		if(!entities[i].empty())
		{
			for(unsigned int j = 0; j < entities[i].size(); j++)
			{
				scene->addEntity(entities[i][j]);
			}
			entities[i].clear();
		}
	}
#else
	static bool firstTime = true;
	if(firstTime)
	{
		firstTime = false;
		scene->addEntity(new BonusPack(scene, SCENE_WIDTH/2, 0, "side_fighter"));

#if 0
		Battleship* battleship = new Battleship(
				scene,
				SCENE_WIDTH/2,
				-80,
				"1943/campaign/battleships/Battleship-01.tmx");
#endif

#if 0
		Battleship* battleship = new BossBattleship(
				scene,
				SCENE_WIDTH/2,
				-260,
				"1943/campaign/battleships/BossBattleship-Yamato.tmx");
		scene->addEntity(battleship);
#endif
	}
#endif
}
void CampaignMap::addObjectToDataList(int startY, Entity* e)
{
	entities[height - startY].push_back(e);
}
