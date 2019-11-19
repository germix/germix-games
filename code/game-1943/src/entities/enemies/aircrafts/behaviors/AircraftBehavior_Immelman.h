////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AircraftBehavior_Immelman
//
// Germán Martínez
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
	//	STATE_PITCH,					// Inclinarse con desaceleración y aceleración
		STATE_PITCH_DECELERATION,		// Inclinarse con desaceleración
		STATE_PITCH_ACCELERATION,		// Inclinarse con aceleración
		STATE_INVERT_RETURN,			// Retornar invertido
		STATE_ROLL_RETURN,				// Rotación en el retorno
		STATE_NORMAL_RETURN,			// Retornar en normal
	};
	Scene*			scene;
	STATE			state;
	double			angle;
	double			velocity;
	double			maxVelocity;
	double			timeElapsed;		// Usado para: desaceleración, aceleración y rotación
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
