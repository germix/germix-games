////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AircraftBehavior_BigBombardier
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___AircraftBehavior_BigBombardier_h___
#define ___AircraftBehavior_BigBombardier_h___
#include <src/entities/enemies/aircrafts/behaviors/AircraftBehavior.h>

#include <gamelib/TimeClock.h>

class Scene;

class AircraftBehavior_BigBombardier : public AircraftBehavior
{
	enum STATE
	{
		STATE_NONE,
		STATE_ENTERING,							// Entrando en la escena (APPROACHING)
		STATE_RISE,								// Subir
		STATE_OUTSIDE,							// Fuera de la escena
		STATE_MOVEMENT_VERT,					// Movimiento vertical
		STATE_MOVEMENT_HORZ,					// Movimiento horizontal
	};
	STATE		state;
	double		velocity;

	double		enteringLimit;

	double		referenceY;						// Posición y de referencia en el movimiento horizontal

	double		verticalMovementLength;
	
	double		horizontalMovementLength;
	double		horizontalMovementOffset;
	double		horizontalMovementDirection;	// Factor multiplicativo para la dirección (-1 izquierza, +1 derecha)

	int			airLevel;
	TimeClock	riseTime;
public:
	AircraftBehavior_BigBombardier(Scene* scene, int velocity, int enteringLimit, int horizontalMovementLength = 150);
	~AircraftBehavior_BigBombardier();
public:
	void update(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex);
	int  getLevel() const;
	bool isRemovable() const;
};

#endif
