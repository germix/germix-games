////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Scene
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Scene_h___
#define ___Scene_h___
#include <src/Config.h>
#include <src/scene/EntityList.h>
#include <src/___/CollisionInfo.h>

#include <vector>

#include <mach/Rectanglef.h>

#include <gamelib/TimeClock.h>

class Graphics;
class Map;
class Hero;
class Knifeable;
class HurtableRect;

class Scene
{
	Map*						map;
	//
	// Informaci�n sobre h�roe
	//
	Hero*						hero;
	
	//
	// Informaci�n sobre entidades
	//
	
	EntityList					entityList;				// Lista de entidades
	EntityList					entityAddedList;		// Lista de entidades agregables
	EntityList					entityRemovableList;	// Lista de entidades removibles
	
	//
	// Desplazamiento del escenario
	//
	Rectanglef					sceneRect;
	Vector2f					sceneScroll;
	Vector2f					relativeScroll;
	
	int							leftLimit;
	int							rightLimit;
	
	bool						autoLeftLimit;		// Tener en cuenta que autoLeftLimit=false, es �til para testeo
	bool						autoRightLimit;		// Lo mismo que autoLeftLimit, s�lo que con el l�mite derecho
	

	bool						restoring;
	TimeClock					restoringClock;

	int							time;
	TimeClock					timeClock;
	
	bool						missionFailed;
	bool						missionCompleted;
public:
	Scene(Map* map, bool activateTime);
	~Scene();
public:
	//!
	//! Limpiar escena
	//!
	void clear();

	//!
	//! Actualizar escena
	//!
	void update(double dt);
	
	//!
	//! Renderizar escena
	//!
	void render(Graphics* gr);
	
	//!
	//! Obtener time
	//!
	int getTime() const { return time; }

	//!
	//! Obtener h�roe
	//!
	//! \return				H�roe
	//!
	Hero* getHero() const { return hero; }

	//!
	//! Obtener rect�ngulo de escena
	//!
	//! \return				Rect�ngulo de escena
	//!
	Rectanglef getSceneRect() const { return sceneRect; }
	
	//!
	//! Obtener rect�ngulo de c�mara
	//!
	//! \return				Rect�ngulo de c�mara
	//!
	Rectanglef getCameraRect() const { return Rectanglef(sceneScroll.x+relativeScroll.x, sceneScroll.y+relativeScroll.y, SCREEN_WIDTH, SCREEN_HEIGHT); }

	//!
	//! Obtener el l�mite izquierdo
	//!
	//! \return				L�mite izquierdo
	//!
	int getLeftLimit() const { return leftLimit; }

	//!
	//! Obtener l�mite derecho
	//!
	//! \return				L�mite derecho
	//!
	int getRightLimit() const { return rightLimit; }
	
	//!
	//! Establecer l�mite izquierdo
	//!
	//! \param newLimit		L�mite derecho
	//!
	void setLeftLimit(int newLimit);
	
	//!
	//! Establecer l�mite derecho
	//!
	//! \param newLimit		Establecer l�mite derecho
	//!
	void setRightLimit(int newLimit);
	
	//!
	//! Obtener el desplazamiento relativo X
	//!
	//! \return				Desplazamiento relativo X
	//!
	double getRelativeScrollX() const { return relativeScroll.x; }
	
	//!
	//! Obtener el desplazamiento relativo Y
	//!
	//! \return				Desplazamiento relativo Y
	//!
	double getRelativeScrollY() const { return relativeScroll.y; }
	
	//!
	//! Establecer el desplazamiento relativo X
	//!
	//! \param x			Desplazamiento relativo X
	//!
	void setRelativeScrollX(double x) { relativeScroll.x = x; }
	
	//!
	//! Establecer el desplazamiento relativo Y
	//!
	//! \param y			Desplazamiento relativo Y
	//!
	void setRelativeScrollY(double y) { relativeScroll.y = y; }
	
	//!
	//! Incrementar desplazamiento relativo
	//!
	//! \param dx			Desplazamiento X
	//! \param dy			Desplazamiento Y
	//!
	void addRelativeScroll(double dx, double dy)
	{
		relativeScroll.x += dx;
		relativeScroll.y += dy;
	}
	
	//!
	//! Obtener el desplazamiento actual X
	//!
	//! \return				Desplazamiento actual X
	//!
	double getCurrentScrollX() const
	{
		return (sceneScroll.x + relativeScroll.x);
	}

	//!
	//! Obtener el desplazamiento actual Y
	//!
	//! \return				Desplazamiento actual Y
	//!
	double getCurrentScrollY() const
	{
		return (sceneScroll.y + relativeScroll.y);
	}

	//!
	//! Comprobar si se est� en restauraci�n del desplazamiento
	//!
	//! \return true|false
	//!
	bool isRestoringScroll() const
	{
		return restoring;
	}
	
	//!
	//! Agregar una entidad al escenario
	//!
	//! \param entity		Entidad que se va a agregar
	//!
	void addEntity(Entity* entity);

	//!
	//! Agregar una entidad al escenario detr�s de otra entidad
	//!
	//! \param other		La otra entidad
	//! \param entity		Entidad que se va a agregar
	//!
	void addEntityBackOfOther(Entity* other, Entity* entity);
	
	//!
	//! Mover entidad
	//!
	//! \param entity		Entidad que se mueve
	//! \param dt			Delta time
	//! \param vel			Velocidad de la entidad
	//! \param accel		Acceleraci�n de la entidad
	//! \param onGround		Indica si la entidad ya est� en el suelo
	//! \param terrainTypes	Tipos de terrenos con los que puede colisionar
	//!
	//! \return				Informaci�n de colisi�n
	//!
	CollisionInfo moveEntity(Entity* entity, double dt, Vector2f& pos, Vector2f& vel, const Vector2f& accel, bool onGround, unsigned int terrainTypes);

	//!
	//! Controlar que una posici�n est� entre los l�mites de la escena
	//!
	//! \param pos			Posici�n
	//! \return				Posici�n corregida
	//!
	Vector2f boundsInScene(const Vector2f pos) const;

	//!
	//! Obtener las entidades cercanas a una posici�n que puede ser da�adas con cuchillo
	//!
	//! \param posX			Posici�n X desde donde hacer la b�squeda
	//! \param posY			Posici�n Y desde donde hacer la b�squeda
	//! \param radius		Radio de b�squeda
	//! \return				Arreglo de entidades "knifeables" encontradas
	//!
	std::vector<Knifeable*> getNearbyKnifeableEntities(double posX, double posY, int radius) const;
	
	//!
	//! Obtener rect�ngulos da�able en un �rea
	//!
	//! \param areaRect		Rect�ngulo de �rea
	//!
	//! \return				Lista de rect�ngulos da�ables
	//!
	std::vector<HurtableRect*> getHurtableRectanglesInArea(const Rectanglef& areaRect) const;
private:

	//
	// Actualizar c�mara, seg�n la posici�n de jugador
	//
	void updateCamera(double dt);
	
	//
	// Comprobar colision de balas
	//
	void checkHits();
	
	//
	// Comprobar colisi�n con colisionables
	//
	void checkCollisions();

public:
	bool isMissionFailed() const { return missionFailed; }
	bool isMissionCompleted() const { return missionCompleted; }
	void markMissionFailed() { missionFailed = true; }
	void markMissionCompleted() { missionCompleted = true; }
};

#endif
