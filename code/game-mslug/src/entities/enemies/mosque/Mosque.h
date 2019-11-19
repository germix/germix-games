////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Mosque | Mezquita con torres lanza cohetes
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Mosque_h___
#define ___Mosque_h___
#include <src/entities/enemies/Enemy.h>
#include <src/___/Hurtable.h>

#include <vector>

#include <mach/Point.h>

#include <gamelib/TimeClock.h>

class Sprite;
class Texture;
class MosqueTower;

class Mosque : public Enemy, public Hurtable
{
	enum STATE
	{
		STATE_NOTHING,					// Nada
		STATE_LIFTING,					// Elevación de torres
		STATE_OPENING1,					// Abriendo las torres (abriendo las puertas)
		STATE_OPENING2,					// Abriendo las torres (asomarse el operador)
		STATE_ATTACKING,				// Atacando al judador
		STATE_EXPLOITING_1,				// Explorar todo
		STATE_EXPLOITING_SHAKE,			// Explotar todo y sacudir
		STATE_RESTORING,				// Restauración del desplazamiento del escenario
		STATE_DESTROYED,				// Mosquita destruida
	};
	enum
	{
		MAX_TOWERS = 3,
		
		MAX_OPENING_FRAMES					= 19,
		BASE_INDEX_TOWER_OPENING_FRAMES		= 1,
		BASE_INDEX_TOWER_ATTACKING_FRAMES	= (BASE_INDEX_TOWER_OPENING_FRAMES+MAX_OPENING_FRAMES-1),
		BASE_INDEX_TOWER_DESTROYED_FRAMES	= (BASE_INDEX_TOWER_ATTACKING_FRAMES+1),
	};
	STATE					state;
	int						mosqueWidth;
	int						mosqueHeight;
	
	int						activationX;
	
	Texture*				textureBaseNormal;
	Texture*				textureBaseDestroyed;
	
	TimeClock				clock;						// Clock de proposito general
	unsigned int			animationIndex;				// Sirve para controlar animaciones, en LIFTING, OPENING1, OPENING2
	
	//
	// Datos de torres
	//
	MosqueTower*			towers[MAX_TOWERS];
	
	//
	// Datos de puertas de torre
	//
	unsigned int			doorFrame;
	Sprite*					doorSprite;
	
	//
	// Datos de operario de torre
	//
	Sprite*					operatorSprite;


	int						lastExplosionIndex;
	
	//
	// Datos acerca de la sacudida de la escena en las explosión
	//
	int						shakeValue;
	int						shakeDirection;
	
	friend class MosqueTower;
public:
	Mosque(Scene* scene, double x, double y);
	~Mosque();
public:
	void update(double dt);
	void render(Graphics* gr);
	
	void getHurtableRects(const Rectanglef& area, std::vector<HurtableRect*>& rects) const;
private:
	void explode();
	void explode(struct ExplosionDescriptor* ed);
};

#endif
