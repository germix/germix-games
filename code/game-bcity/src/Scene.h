////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Scene
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Scene_h___
#define ___Scene_h___
#include <src/base/EnemySet.h>
#include <src/base/SpawnerBlink.h>

#include <list>

#include <mach/Point.h>

#include <gamelib/TimeClock.h>

class Map;
class Tank;
class Entity;

class Graphics;

class Scene
{
	enum SPAWN_STATE
	{
		SPAWN_STATE_NONE,
		SPAWN_STATE_BLINK,
	};
	
	Map*						map;
	
	bool						gameOver;
	bool						levelCompleted;
	
	std::list<Entity*>			entities;
	std::list<Entity*>			addedEntities;
	
	bool						enemiesPaused;
	TimeClock					enemiesPausedClock;
	
	bool						fortifiedBase;
	TimeClock					fortifiedBaseClock;
	
	EnemySet					enemySet;
	SPAWN_STATE					spawnState;
	TimeClock					spawnClock;
	SpawnerBlink				spawnBlink;
	int							spawnPointIndex;
	
	static const Point spawnPoints[];
	static const Point borderBasePoints[];

	int							enemyTanksInScene;
public:
	Scene();
	~Scene();
public:
	//!
	//! Cargar nivel
	//!
	//! \param tmx Archivo del nivel
	//!
	//! \return Mapa del nivel
	//!
	Map* load(const TmxMap* tmx);
	
	//!
	//! Actualizar entidades. Tambien comprueba colisiones.
	//! Agregar las entidades pendientes y eliminas las entidades removibles
	//!
	//! \param dt Delta del tiempo
	//!
	void update(double dt);
	
	//!
	//! Dibujar entidades
	//!
	//! \param gr Un objeto Graphics2D
	//!
	void render(Graphics* gr);
	
	//!
	//! Agregar una entidad
	//!
	//! \param e Entidad
	//!
	void addEntity(Entity* e)
	{
		addedEntities.push_back(e);
	}
	
	//!
	//! Marcar que se ha perdido el juego
	//!
	void setGameOver()
	{
		gameOver = true;
	}

	//!
	//! Comprobar si se ha perdido el juego
	//!
	//! \return true si se ha perdido, false en caso contrario
	//!
	bool isGameOver() const
	{
		return gameOver;
	}

	//!
	//! Comprobar que el nivel ha sido completado, cuando se eliminan todos los enemigos
	//!
	//! \return true si el nivel ha sido completado, false en caso contrario
	//!
	bool isLevelCompleted() const
	{
		return levelCompleted;
	}

	//!
	//! Comprobar si es posible caminar sin que haya una colisión con tanques.
	//! Los tanques son las únicas entidades que no se pueden traspasar (tanques enemigos o héroes).
	//! Si el tanque ya está en colisión antes del movimiento, sí se permite el movimiento,
	//! esto es para que los tanques se puedan mover en caso de una superposición y no queden bloqueados.
	//!
	//! \param tank Tanque que intenta moverse
	//! \param dx Desplazamiento horizontal que intenta hacer el objeto
	//! \param dy Desplazamiento vertical que intenta hacer el objeto
	//!
	//! \return true si el movimiento es posible, false en caso contrario
	//!
	bool tryMove(Tank* tank, int dx, int dy) const;
	
	//!
	//! Destruir todos los tanques enemigos
	//!
	void killEnemies();
	
	//!
	//! Pone en pausa a todos los enemigos
	//!
	void pauseEnemies();
	
	//!
	//! Comprobar si los enemigos están pausados
	//!
	//! \return true si están pausados, false en caso contrario
	//!
	bool isEnemiesPaused() const
	{
		return enemiesPaused;
	}

	//!
	//! Fortificar con metal la base
	//!
	void fortifyBase();
	
	//!
	//! Obtener la cantidad de enemigos
	//!
	//! \return Cantidad de enemigos
	//!
	int getEnemyCount() const;
private:
	void clear();
	
	void clearEntities(std::list<Entity*>& removables);
};

#endif
