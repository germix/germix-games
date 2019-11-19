////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Scene
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Scene_h___
#define ___Scene_h___
#include <list>
#include <mach/Rectanglef.h>

#include <src/FadingHandler.h>
#include <src/TypingMessage.h>

class Graphics;

class Hud;
class Hero;
class Entity;
class SpecialAttack;
class Campaign;
class CampaignMap;
class CampaignRound;
class Presentation;
class HeroBullet;

class Scene
{
public:
	enum PLAYER_STATE
	{
		PLAYER_STATE_UNDEFINED,
		PLAYER_STATE_LOSER,
		PLAYER_STATE_WINNER,
		PLAYER_STATE_PLAYING,
	};
private:
	enum CAMPAIGN_STATE
	{
		CAMPAIGN_STATE_NONE,								// Inicialmente, nada
		CAMPAIGN_STATE_NEXT_ROUND,							// Seleccionar siguiente ronda
		CAMPAIGN_STATE_STAGE_A_INIT,
		CAMPAIGN_STATE_STAGE_A_INFO,						// Mostrar info inicial
		CAMPAIGN_STATE_STAGE_A_COMBAT,
		CAMPAIGN_STATE_STAGE_A_DESCEND,						// Descender
		CAMPAIGN_STATE_STAGE_A_FADING,
		CAMPAIGN_STATE_STAGE_A_SURFACE_FORCES_CONFIRMED,
		CAMPAIGN_STATE_STAGE_B_INIT,
		CAMPAIGN_STATE_STAGE_B_COMBAT,
		CAMPAIGN_STATE_STAGE_B_LEAVING,						// Saliendo del mapa (hacia adelante)
		CAMPAIGN_STATE_STAGE_B_FADING,
		// ..
		CAMPAIGN_STATE_MISSION_ABORTED,
		CAMPAIGN_STATE_MISSION_COMPLETED,
		CAMPAIGN_STATE_HERO_DEAD,
		CAMPAIGN_STATE_CAMPAIGN_FAILED,
		CAMPAIGN_STATE_CAMPAIGN_COMPLETED,
		// ...
		CAMPAIGN_STATE_ERROR_STAGE,
		CAMPAIGN_STATE_UNDEFINED_STAGE,
	};
	
	//
	// Jugador
	//
	PLAYER_STATE				playerState;
	
	//
	// Camaña
	//
	Campaign*					campaign;
	CampaignMap*				campaignMap;
	CampaignRound*				campaignRound;
	CAMPAIGN_STATE				campaignState;
	
	int							attempts;
	
	//
	// Objetos
	//
	Hero*						hero;
	
	std::list<Entity*>			bonus;
	std::list<Entity*>			bonusAdded;
	
	std::list<Entity*>			aircrafts;
	std::list<Entity*>			aircraftsAdded;
	
	std::list<Entity*>			battleships;
	std::list<Entity*>			battleshipsAdded;
	
	std::list<Entity*>			explosions;
	std::list<Entity*>			explosionsAdded;
	
	std::list<Entity*>			heroBullets;
	std::list<Entity*>			heroBulletsAdded;
	
	std::list<Entity*>			enemyBullets;
	std::list<Entity*>			enemyBulletsAdded;
	
	//
	// Ataques especiales
	//
	SpecialAttack*				specialAttack;
	
	//
	// ...
	//
	Hud*						hud;

	FadingHandler				fading;
	
	Presentation*				presentation;
public:
	Scene();
	~Scene();
public:
	void init();
	void update(double dt);
	void render(Graphics* gr);
public:
	Hero* getHero() const;
	Rectanglef getSceneRect() const;
	void addEntity(Entity* entity);
	void callSpecialAttack();
	
	int getPlayerState() const
	{
		return playerState;
	}
private:
	bool initRound();
	bool updateMap(double dt);
	void updateHero(double dt);
	void updateEntities(double dt);
	bool updateLeaving(double dt);
	bool updateDescend(double dt);
	bool updateFading(double dt);
	bool updateCombat(double dt);
	void renderCombat(Graphics* gr);
	void checkHits();
	void checkHits(std::list<Entity*>& list);
	bool checkHits(std::list<Entity*>& list, HeroBullet* bullet);
	void checkCollisions();
	void checkCollisions(std::list<Entity*>& list);
	void solvePendings();
	CAMPAIGN_STATE loadMap(char stage);
	void initCombat(char stage);

	void addAddedEntities(std::list<Entity*>& dst, std::list<Entity*>& src);
	void callUpdateEntitiesFor(std::list<Entity*>& entities, double dt);
	void callRenderEntitiesFor(const std::list<Entity*>& entities, Graphics* gr);
	
	std::list<Entity*> removables;
	void clearEntities();
	void clearEntities(std::list<Entity*>& list);
	void clearRemovables();
};

#endif
