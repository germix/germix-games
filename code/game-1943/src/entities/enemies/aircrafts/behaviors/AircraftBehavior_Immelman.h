////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AircraftBehavior_Immelman
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___AircraftBehavior_Immelman_h___
#define ___AircraftBehavior_Immelman_h___
#include <src/entities/enemies/aircrafts/behaviors/AircraftBehavior.h>

class Scene;

class AircraftBehavior_Immelman : public AircraftBehavior
{
	enum STATE
	{
		STATE_NORMAL_ADVANCE,			// Avance normal
	//	STATE_PITCH,					// Inclinarse con desaceleraci�n y aceleraci�n
		STATE_PITCH_DECELERATION,		// Inclinarse con desaceleraci�n
		STATE_PITCH_ACCELERATION,		// Inclinarse con aceleraci�n
		STATE_INVERT_RETURN,			// Retornar invertido
		STATE_ROLL_RETURN,				// Rotaci�n en el retorno
		STATE_NORMAL_RETURN,			// Retornar en normal
	};
	Scene*			scene;
	STATE			state;
	double			angle;
	double			velocity;
	double			maxVelocity;
	double			timeElapsed;		// Usado para: desaceleraci�n, aceleraci�n y rotaci�n
	bool			removable;
public:
	AircraftBehavior_Immelman(Scene* scene, double velocity);
	~AircraftBehavior_Immelman();
public:
	void update(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex);
	int  getLevel() const;
	bool isRemovable() const;
private:
	void move(Vector2f& pos, double len);
	void updateForNormalAdvance(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex);
	void updateForPitchDeceleration(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex);
	void updateForPitchAcceleration(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex);
	void updateForInvertReturn(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex);
	void updateForRollReturn(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex);
	void updateForNormalReturn(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex);
};

#endif
