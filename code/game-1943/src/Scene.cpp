////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Scene
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Scene.h>
#include <src/Hud.h>
#include <src/Debug.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/campaign/Campaign.h>
#include <src/campaign/CampaignMap.h>
#include <src/campaign/CampaignRound.h>

#include <src/entities/BonusPack.h>
#include <src/entities/explosions/Explosion.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/bullets/HeroBullet.h>
#include <src/entities/enemies/bullets/EnemyBullet.h>
#include <src/entities/enemies/aircrafts/Aircraft.h>
#include <src/entities/enemies/battleships/Battleship.h>

#include <src/attacks/SpecialAttack_Storm.h>
#include <src/attacks/SpecialAttack_Tsunami.h>

#include <src/presentations/ErrorPresentation.h>
#include <src/presentations/RoundInfoPresentation.h>
#include <src/presentations/MissionAbortedPresentation.h>
#include <src/presentations/MissionCompletedPresentation.h>
#include <src/presentations/SurfaceForcesConfirmedPresentation.h>

#include <src/BossStatistics.h>

#include <mach/Mixer.h>
#include <mach/Color.h>
#include <mach/Graphics.h>

Scene::Scene()
: playerState(PLAYER_STATE_PLAYING)
, campaign(null)
, campaignMap(null)
, campaignRound(null)
, campaignState(CAMPAIGN_STATE_NONE)
, attempts(0)
, hero(null)
, specialAttack(null)
, hud(null)

, fading(0.7, 255)

, presentation(null)
{
	hud = new Hud(this);
	hero = new Hero(this, 0, 0);
	campaign = new Campaign();
}
Scene::~Scene()
{
	if(hud) delete hud;
	if(hero) delete hero;
	if(campaign) delete campaign;

	if(campaignMap) delete campaignMap;
	if(campaignRound) delete campaignRound;
	if(presentation) delete presentation;
	if(specialAttack) delete specialAttack;

	clearEntities();
}
void Scene::init()
{
	if(!initRound())
	{
	}
}
void Scene::update(double dt)
{
	switch(campaignState)
	{
		case CAMPAIGN_STATE_NONE:
			break;
		case CAMPAIGN_STATE_NEXT_ROUND:
			if(!initRound())
			{
				playerState = PLAYER_STATE_WINNER;
				campaignState = CAMPAIGN_STATE_CAMPAIGN_COMPLETED;
			}
			break;
		case CAMPAIGN_STATE_STAGE_A_INIT:
			initCombat('A');
			break;
		case CAMPAIGN_STATE_STAGE_A_INFO:
			if(presentation->update(dt))
			{
				delete presentation;
				presentation = null;
				campaignState = CAMPAIGN_STATE_STAGE_A_COMBAT;
			}
			break;
		case CAMPAIGN_STATE_STAGE_A_COMBAT:
			if(!updateCombat(dt))
			{
				hero->descend();
				Mixer::halt(1000);
				campaignState = CAMPAIGN_STATE_STAGE_A_DESCEND;
			}
			break;
		case CAMPAIGN_STATE_STAGE_A_DESCEND:
			if(!updateDescend(dt))
			{
				campaignState = CAMPAIGN_STATE_STAGE_A_FADING;
				fading.reset();
			}
			break;
		case CAMPAIGN_STATE_STAGE_A_FADING:
			if(!updateFading(dt))
			{
				campaignState = CAMPAIGN_STATE_STAGE_A_SURFACE_FORCES_CONFIRMED;
				presentation = new SurfaceForcesConfirmedPresentation();
			}
			break;
		case CAMPAIGN_STATE_STAGE_A_SURFACE_FORCES_CONFIRMED:
			if(presentation->update(dt))
			{
				delete presentation;
				presentation = null;
				campaignState = CAMPAIGN_STATE_STAGE_B_INIT;
			}
			break;
		case CAMPAIGN_STATE_STAGE_B_INIT:
			initCombat('B');
			break;
		case CAMPAIGN_STATE_STAGE_B_COMBAT:
			if(!updateCombat(dt))
			{
				hero->leave();
				Mixer::halt(1000);
				campaignState = CAMPAIGN_STATE_STAGE_B_LEAVING;
			}
			break;
		case CAMPAIGN_STATE_STAGE_B_LEAVING:
			if(!updateLeaving(dt))
			{
				fading.reset();
				campaignState = CAMPAIGN_STATE_STAGE_B_FADING;
			}
			break;
		case CAMPAIGN_STATE_STAGE_B_FADING:
			if(!updateFading(dt))
			{
				const BossStatistics* statistics = campaignMap->getBossStatistics();
				
				if(statistics == null)
				{
					campaignState = CAMPAIGN_STATE_ERROR_STAGE;
					presentation = new ErrorPresentation("NO EXISTE ESTADISTICAS DE JEFE ENEMIGO");
				}
				else
				{
					if(statistics->getDestroyedPercent() < 70)
					{
						campaignState = CAMPAIGN_STATE_MISSION_ABORTED;
						
						presentation = new MissionAbortedPresentation(statistics->getDestroyedPercent());
					}
					else
					{
						campaignState = CAMPAIGN_STATE_MISSION_COMPLETED;
						
						presentation = new MissionCompletedPresentation(statistics->getDestroyedPercent());
					}
				}
			}
			break;
		case CAMPAIGN_STATE_MISSION_ABORTED:
			if(presentation->update(dt))
			{
				if(++attempts == 1)
				{
					hero->resetTempScore();
					initCombat('B');
				}
				else
				{
					campaignState = CAMPAIGN_STATE_NEXT_ROUND;
					delete presentation;
					presentation = null;
				}
			}
			break;
		case CAMPAIGN_STATE_MISSION_COMPLETED:
			if(presentation->update(dt))
			{
				campaignState = CAMPAIGN_STATE_NEXT_ROUND;
				delete presentation;
				presentation = null;
			}
			break;
		case CAMPAIGN_STATE_HERO_DEAD:
			if(!updateFading(dt))
			{
				playerState = PLAYER_STATE_LOSER;
				campaignState = CAMPAIGN_STATE_CAMPAIGN_FAILED;
			}
			break;
		case CAMPAIGN_STATE_CAMPAIGN_FAILED:
			// Nada
			break;
		case CAMPAIGN_STATE_CAMPAIGN_COMPLETED:
			// Nada
			break;
		case CAMPAIGN_STATE_ERROR_STAGE:
			if(presentation->update(dt))
			{
				playerState = PLAYER_STATE_UNDEFINED;
				campaignState = CAMPAIGN_STATE_UNDEFINED_STAGE;
				delete presentation;
				presentation = null;
			}
			break;
		case CAMPAIGN_STATE_UNDEFINED_STAGE:
			// Nada
			break;
	}
}
void Scene::render(Graphics* gr)
{
	gr->translate(SCENE_X, SCENE_Y);
	switch(campaignState)
	{
		case CAMPAIGN_STATE_NONE:
		case CAMPAIGN_STATE_NEXT_ROUND:
		case CAMPAIGN_STATE_STAGE_A_INIT:
		case CAMPAIGN_STATE_STAGE_B_INIT:
			// Nada
			break;
		case CAMPAIGN_STATE_STAGE_A_COMBAT:
		case CAMPAIGN_STATE_STAGE_A_DESCEND:
		case CAMPAIGN_STATE_STAGE_B_COMBAT:
		case CAMPAIGN_STATE_STAGE_B_LEAVING:
			renderCombat(gr);
			break;
		case CAMPAIGN_STATE_HERO_DEAD:
		case CAMPAIGN_STATE_STAGE_A_FADING:
		case CAMPAIGN_STATE_STAGE_B_FADING:
			if(fading.value() < 255)
			{
				renderCombat(gr);
			}
			gr->fillRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT, Color(0,0,0,fading.value()));
			break;
		case CAMPAIGN_STATE_STAGE_A_INFO:
		case CAMPAIGN_STATE_MISSION_ABORTED:
		case CAMPAIGN_STATE_MISSION_COMPLETED:
		case CAMPAIGN_STATE_STAGE_A_SURFACE_FORCES_CONFIRMED:
			if(campaignState == CAMPAIGN_STATE_STAGE_A_INFO)
			{
				campaignMap->render(gr);
			}
			presentation->render(gr);
			break;
		case CAMPAIGN_STATE_CAMPAIGN_FAILED:
		case CAMPAIGN_STATE_CAMPAIGN_COMPLETED:
			break;
		case CAMPAIGN_STATE_ERROR_STAGE:
			presentation->render(gr);
			break;
		case CAMPAIGN_STATE_UNDEFINED_STAGE:
			// TODO: Eliminar esto
			break;
	}
	gr->translate(-SCENE_X, -SCENE_Y);
}
Hero* Scene::getHero() const
{
	return hero;
}
Rectanglef Scene::getSceneRect() const
{
	return Rectanglef(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
}
void Scene::addEntity(Entity* entity)
{
	if(dynamic_cast<Aircraft*>(entity))			{ aircraftsAdded.push_back(entity);			}
	else if(dynamic_cast<Battleship*>(entity))	{ battleshipsAdded.push_back(entity);		}
	else if(dynamic_cast<HeroBullet*>(entity))	{ heroBulletsAdded.push_back(entity);		}
	else if(dynamic_cast<EnemyBullet*>(entity))	{ enemyBulletsAdded.push_back(entity);		}
	else if(dynamic_cast<BonusPack*>(entity))	{ bonusAdded.push_back(entity);				}
	else if(dynamic_cast<Explosion*>(entity))	{ explosionsAdded.push_back(entity);		}
}
void Scene::callSpecialAttack()
{
	if(specialAttack == null)
	{
		switch(campaignState)
		{
			case CAMPAIGN_STATE_STAGE_A_COMBAT:
				specialAttack = new SpecialAttack_Storm(this);
				break;
			case CAMPAIGN_STATE_STAGE_B_COMBAT:
				specialAttack = new SpecialAttack_Tsunami(this);
				break;
			default:
				// TODO: Tratar error aquí
				break;
		}
		if(specialAttack->damageForHero() >= hero->getHealth())
		{
			//
			// Si la capasidad de daño que tiene el ataque especial
			// supera la salud del heroe, entonces cancelar el ataque
			//
			delete specialAttack;
			specialAttack = null;
		}
		else
		{
			hero->hurt(specialAttack->damageForHero());
			for(std::list<Entity*>::const_iterator it = aircrafts.begin(); it != aircrafts.end(); it++)
			{
				((Aircraft*)(*it))->hurt(specialAttack->damageForAircrafts());
			}
			for(std::list<Entity*>::const_iterator it = battleships.begin(); it != battleships.end(); it++)
			{
				((Battleship*)(*it))->hurt(specialAttack->damageForBattleships());
			}
			
			//
			// Romper las balas enemigas
			//
			for(std::list<Entity*>::const_iterator it = enemyBullets.begin(); it != enemyBullets.end(); it++)
			{
				((EnemyBullet*)(*it))->collisioned();
			}
		}
	}
}
bool Scene::initRound()
{
	if(campaignMap)
	{
		delete campaignMap;
		campaignMap = null;
	}
	if(campaignRound)
	{
		delete campaignRound;
		campaignRound = null;
	}
	if(presentation)
	{
		delete presentation;
		presentation = null;
	}
	if(specialAttack)
	{
		delete specialAttack;
		specialAttack = null;
	}
	clearEntities();
	
	if(null != (campaignRound = campaign->nextRound()))
	{
		attempts = 0;
		campaignState = CAMPAIGN_STATE_STAGE_A_INIT;
		return true;
	}
	return false;
}
bool Scene::updateMap(double dt)
{
	campaignMap->update(dt);
	return !campaignMap->isEnded();
}
void Scene::updateHero(double dt)
{
	hero->update(dt);
	if(hero->isLoser())
	{
		Mixer::halt(1000);
		fading.reset();
		campaignState = CAMPAIGN_STATE_HERO_DEAD;
	}
}
void Scene::updateEntities(double dt)
{
	callUpdateEntitiesFor(aircrafts, dt);
	if(specialAttack == null)
	{
		callUpdateEntitiesFor(battleships, dt);
	}
	if(specialAttack == null)
	{
		callUpdateEntitiesFor(bonus, dt);
	}
	callUpdateEntitiesFor(explosions, dt);
	callUpdateEntitiesFor(heroBullets, dt);
	callUpdateEntitiesFor(enemyBullets, dt);
}
bool Scene::updateLeaving(double dt)
{
	updateHero(dt);
	updateEntities(dt);
	return !hero->isReady();
}
bool Scene::updateDescend(double dt)
{
	updateHero(dt);
	updateEntities(dt);
	return !hero->isReady();
}
bool Scene::updateFading(double dt)
{
	if(fading.update(dt))
	{
		updateEntities(dt);
		return true;
	}
	return false;
}
bool Scene::updateCombat(double dt)
{
	if(specialAttack != null)
	{
		if(!hero->isLoser())
		{
			updateHero(dt);
		}
		updateEntities(dt);
		specialAttack->update(dt);
		if(specialAttack->isFinished())
		{
			delete specialAttack;
			specialAttack = null;
		}
		checkHits();
		
		checkCollisions();
		
		solvePendings();
		
		hud->update(dt);
		
		return true;
	}

	if(updateMap(dt))
	{
		if(!hero->isLoser())
		{
			updateHero(dt);
		}
		updateEntities(dt);
		
		checkHits();
		
		checkCollisions();
		
		solvePendings();
		
		hud->update(dt);
		
		return true;
	}
	return false;
}
void Scene::renderCombat(Graphics* gr)
{
	campaignMap->render(gr);
	
	callRenderEntitiesFor(battleships, gr);
	
	callRenderEntitiesFor(bonus, gr);
	callRenderEntitiesFor(aircrafts, gr);
	callRenderEntitiesFor(explosions, gr);
	callRenderEntitiesFor(heroBullets, gr);
	callRenderEntitiesFor(enemyBullets, gr);
	
	if(specialAttack != null)
	{
		specialAttack->render(gr);
	}
	
	hero->render(gr);
	hud->render(gr);
}
void Scene::checkHits()
{
	//
	// Balas de heroe contra los otros objetos
	//
	checkHits(bonus);
	checkHits(aircrafts);
	checkHits(battleships);
	
	//
	// Balas enemigas contra el heroe
	//
	if(hero->isAlive())
	{
		for(std::list<Entity*>::const_iterator it = enemyBullets.begin(); it != enemyBullets.end() && hero->isAlive(); it++)
		{
			Entity* ent = *it;
			EnemyBullet* bullet = (EnemyBullet*)(ent);
			
			hero->checkHit(bullet);
			if(bullet->isRemovable())
			{
				removables.push_back(ent);
			}
		}
		clearRemovables();
	}
}
void Scene::checkHits(std::list<Entity*>& list)
{
	HeroBullet* bullet;
	
	for(std::list<Entity*>::const_iterator it = heroBullets.begin(); it != heroBullets.end(); it++)
	{
		if(checkHits(list, bullet = (HeroBullet*)*it))
		{
			return;
			//removables.push_back(bullet);
		}
	}
	//clearRemovables();
}
bool Scene::checkHits(std::list<Entity*>& list, HeroBullet* bullet)
{
	for(std::list<Entity*>::const_iterator it = list.begin(); it != list.end() && !bullet->isRemovable(); it++)
	{
		Entity* entity = (Entity*)*it;
		Shootable* shootable = dynamic_cast<Shootable*>(entity);

		if(shootable)
		{
			shootable->checkHit(bullet);
			if(entity->isRemovable())
				removables.push_back(entity);
			if(bullet->isRemovable())
				removables.push_back(bullet);
		}
	}
	bool rem = bullet->isRemovable();
	clearRemovables();
	return rem;
}
void Scene::checkCollisions()
{
	checkCollisions(bonus);
	checkCollisions(aircrafts);
}
void Scene::checkCollisions(std::list<Entity*>& list)
{
	for(std::list<Entity*>::const_iterator it = list.begin(); it != list.end() && hero->isAlive(); it++)
	{
		Entity* ent = *it;
		Collisionable* collisionable = dynamic_cast<Collisionable*>(ent);

		collisionable->checkCollision(hero);
		if(ent->isRemovable())
			removables.push_back(ent);
	}
	clearRemovables();
}
void Scene::solvePendings()
{
	//
	// Agregar objectos pendientes
	//
	addAddedEntities(aircrafts, aircraftsAdded);
	addAddedEntities(battleships, battleshipsAdded);
	addAddedEntities(bonus, bonusAdded);
	addAddedEntities(heroBullets, heroBulletsAdded);
	addAddedEntities(enemyBullets, enemyBulletsAdded);
	addAddedEntities(explosions, explosionsAdded);
}
Scene::CAMPAIGN_STATE Scene::loadMap(char stage)
{
	CAMPAIGN_STATE s = CAMPAIGN_STATE_ERROR_STAGE;
	
	if(campaignMap)
	{
		delete campaignMap;
	}
	campaignMap = campaignRound->getMap(this, stage);
	
	if(campaignMap != null)
	{
		switch(stage)
		{
			case 'A':
				s = CAMPAIGN_STATE_STAGE_A_INFO;
				presentation = new RoundInfoPresentation(campaignRound->getBossName());
				break;
			case 'B':
				s = CAMPAIGN_STATE_STAGE_B_COMBAT;
				break;
		}
	}
	if(s == CAMPAIGN_STATE_ERROR_STAGE)
	{
		if(presentation)
			delete presentation;
		presentation = new ErrorPresentation("Error de mapa");
	}
	return s;
}
void Scene::initCombat(char stage)
{
	if(stage == 'A' || stage == 'B')
	{
		if(campaignMap)
		{
			delete campaignMap;
			campaignMap = null;
		}
		if(presentation)
		{
			delete presentation;
			presentation = null;
		}
		if(specialAttack)
		{
			delete specialAttack;
			specialAttack = null;
		}
		clearEntities();
		
		//
		// Cargar mapa, luego iniciar
		//
		if((campaignState = loadMap(stage)) != CAMPAIGN_STATE_ERROR_STAGE)
		{
			//
			// Obtener música y reproducir
			//
			if(Debug::playMusic)
			{
				if(stage == 'A')
					Mixer::playMusic(res.findMusic("stage1"));
				else
					Mixer::playMusic(res.findMusic("stage2"));
			}
			
			//
			// Iniciar mapa de campaña
			//
			campaignMap->init();
			
			//
			// Colocar heroe
			//
			if(stage == 'B')
				hero->enter(SCENE_WIDTH/2, SCENE_HEIGHT);
			else
				hero->ascend(SCENE_WIDTH/2, SCENE_HEIGHT/2);
		}
	}
	else
	{
		char sz[256];
		
		sprintf(sz, "Etapa desconocida \"c\"", stage);
		campaignState = CAMPAIGN_STATE_ERROR_STAGE;
		presentation = new ErrorPresentation(sz);
	}
}
void Scene::addAddedEntities(std::list<Entity*>& dst, std::list<Entity*>& src)
{
	for(std::list<Entity*>::const_iterator it = src.begin(); it != src.end(); it++)
	{
		dst.push_back(*it);
	}
	src.clear();
}
void Scene::callUpdateEntitiesFor(std::list<Entity*>& entities, double dt)
{
	// Actualizar entidades
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
}
void Scene::callRenderEntitiesFor(const std::list<Entity*>& entities, Graphics* gr)
{
	for(std::list<Entity*>::const_iterator it = entities.begin(); it != entities.end(); it++)
	{
		(*it)->render(gr);
	}
}
void Scene::clearEntities()
{
	clearEntities(bonus);
	clearEntities(bonusAdded);
	
	clearEntities(aircrafts);
	clearEntities(aircraftsAdded);

	clearEntities(battleships);
	clearEntities(battleshipsAdded);
	
	clearEntities(explosions);
	clearEntities(explosionsAdded);

	clearEntities(heroBullets);
	clearEntities(heroBulletsAdded);

	clearEntities(enemyBullets);
	clearEntities(enemyBulletsAdded);
}
void Scene::clearEntities(std::list<Entity*>& list)
{
	for(std::list<Entity*>::const_iterator it = list.begin(); it != list.end(); it++)
		delete *it;
	list.clear();
}
void Scene::clearRemovables()
{
	// Remover las entidades removibles
	for(std::list<Entity*>::const_iterator it = removables.begin(); it != removables.end(); it++)
	{
		Entity* e = *it;

		if(dynamic_cast<BonusPack*>(e))			bonus.remove(e);
		else if(dynamic_cast<Aircraft*>(e))		aircrafts.remove(e);
		else if(dynamic_cast<Battleship*>(e))	battleships.remove(e);
		else if(dynamic_cast<Explosion*>(e))	explosions.remove(e);
		else if(dynamic_cast<HeroBullet*>(e))	heroBullets.remove(e);
		else if(dynamic_cast<EnemyBullet*>(e))	enemyBullets.remove(e);

		delete e;
	}
	removables.clear();
}

