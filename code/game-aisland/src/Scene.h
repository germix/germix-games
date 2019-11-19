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

#include <mach/Vector2f.h>
#include <mach/Rectangle.h>
#include <mach/Rectanglef.h>

#include <gamelib/TimeClock.h>

#include <src/EntitySpawner.h>

class Music;
class Font;
class Texture;

class Hero;
class Entity;
class Graphics;
class Platform;
class PixelMap;
class EntitySpawner;
class HiddenEgg;
class TexturedTileMap;
class HeroInfo;

namespace tinyxml2
{
	class XMLElement;
};

#ifndef MAP_TERRAIN_SOLID
#define MAP_TERRAIN_SOLID		0x01
#define MAP_TERRAIN_TOPDOWN		0x02
#endif

#ifndef COLLISION_FLAG_LEFT
#define COLLISION_FLAG_LEFT		0x01
#define COLLISION_FLAG_RIGHT	0x02
#define COLLISION_FLAG_TOP		0x04
#define COLLISION_FLAG_BOTTOM	0x08

#define COLLISION_FLAG_ALL		(COLLISION_FLAG_LEFT|COLLISION_FLAG_RIGHT|COLLISION_FLAG_TOP|COLLISION_FLAG_BOTTOM)
#endif

class Scene
{
public:
	static const double GRAVITY;
	static const Vector2f GRAVITY_ACCELERATION;
private:
	enum STATE
	{
		STATE_0,
		STATE_PLAYING,
		STATE_FINISHING,
		STATE_FINISHED,
	};
	STATE							state;

	Hero*							hero;
	
	std::list<Entity*>				entities;
	std::list<Entity*>				addedEntities;
	
	PixelMap*						map;
	int								mapWidth;
	int								mapHeight;
	
	std::list<Platform*>			platforms;
	std::list<Entity*>				removables;
	Texture*						background;
	TexturedTileMap*				ttmBackground;
	
	//
	// HUD
	//
	Font*							font;
	Texture*						livesMark;
	Texture*						healthMark;
	
	bool							failed;
	bool							completed;
	Vector2f						respawnPosition;
	int								availablesLives;// TODO: Remover?

	TimeClock						finishingClock;
	TimeClock						decreaseHealthClock;

	Music*							music;
	int								cameraX;
	int								cameraY;
	int*							cameraOffsets;
	
	HeroInfo&						heroInfo;
	EntitySpawner					entitySpawner;

	int								hideHeroInX;

	bool							musicStarted;

	int								monterCasterMusicX;
	bool							monterCasterMusicXStarted;

	bool							disableHealthDecrement;
public:
	Scene(HeroInfo& info, int area = -1, int round = -1);
	~Scene();
public:
	void update(double dt);
	void render(Graphics* gr);

	//!
	//! Cargar escena de prueba
	//!
	void loadDummy();
	
	//!
	//! Carcar escena del juego
	//!
	//! \param area				Área
	//! \param round			Ronda
	//!
	void loadScene(int area, int round);
	
	//!
	//! Agregar entidad a la escena
	//!
	//! \param entity			Entidad
	//!
	void addEntity(Entity* entity);

	//!
	//! Mover entidad
	//!
	//! \param entity			Entidad que se mueve
	//! \param dt				Delta time
	//! \param vel				Velocidad de la entidad
	//! \param accel			Acceleración de la entidad
	//! \param onGround			Indica si la entidad ya está en el suelo
	//! \param terrainTypes		Tipos de terrenos con los que puede colisionar
	//! \param collisionFlags	Tipos de collisiones para detectar
	//!
	//! \return					Información de colisión
	//!
	unsigned int moveEntity(Entity* entity, double dt, Vector2f& pos, Vector2f& vel, const Vector2f& accel, bool onGround, unsigned int terrainTypes, unsigned int collisionFlags = COLLISION_FLAG_ALL);
	
	//!
	//! Comprobar si hay colisión
	//!
	//! \param entity			Entidad
	//! \param newPosition		Nueva posición
	//! \param newVelocity		Nueva velocidad
	//! \param oldPosition		Vieja posición
	//! \param oldVelocity		Vieja velocidad
	//! \param terrainTypes		Tipos de terrenos con los que puede colisionar
	//! \param collisionFlags	Tipos de collisiones para detectar
	//!
	//! \return					Información de colisión
	//!
	unsigned int checkCollision(Entity* entity, Vector2f& newPosition, Vector2f& newVelocity, const Vector2f& oldPosition, const Vector2f& oldVelocity, unsigned int terrainTypes, unsigned int collisionFlags = COLLISION_FLAG_ALL) const;
	
	//!
	//! Obtener rectángulo de cámara
	//!
	//! \return					Rectángulo de cámara
	//!
	Rectanglef getCameraRect() const;
	
	//!
	//! Obtener héroe
	//!
	//! \return					Héroe
	//!
	Hero* getHero() const;

	//!
	//! Obtener las plataformas en la escena
	//!
	//! \return					Lista de plataformas
	//!
	std::list<Platform*> getPlatforms() const;
	
	//!
	//! Comprobar si se falló
	//!
	//! \return					true|false
	//!
	bool isFailed() const;
	
	//!
	//! Comprobar si se finalizó la escena (falló o se completó)
	//!
	//! \return					true|false
	//!
	bool isFinished() const;
	
	//!
	//! Comprobar si se completó la escena
	//!
	//! \return					true|false
	//!
	bool isCompleted() const;
	
	//!
	//! Estaplecer nuevo punto de respawn del héroe
	//!
	//! \param pos				Punto de respawn
	//!
	void setRespawnPosition(const Vector2f& pos);
	
	//!
	//! Resetear la escena
	//!
	void restart();

	//!
	//! Obtener bonus oculto en rectángulo
	//!
	//! \param r				Rectángulo
	//!
	//! \return					Huevo oculto
	//!
	HiddenEgg* getHiddentEgg(const Rectanglef& r) const;

	bool isPlaying() const { return state == STATE_PLAYING; }
	Music* getSceneMusic() const { return music; }
private:
	void clear();
	void clearEntitiesNoHero(std::list<Entity*>& ent);
	void readMap(const char* fullPath, char* semiPath, tinyxml2::XMLElement* elem);
	void readMusic(const char* fullPath, char* semiPath, tinyxml2::XMLElement* elem);
	void readEntities(const char* fullPath, char* semiPath, tinyxml2::XMLElement* elem);
	void updateCamera();
	void clearRemovables();
};

#endif
