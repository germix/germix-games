////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyTank
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___EnemyTank_h___
#define ___EnemyTank_h___
#include <src/entities/Tank.h>

#include <vector>

#include <gamelib/TimeClock.h>

class EnemyTank : public Tank
{
	static const double MOVE_TIME_TANK_1;
	static const double MOVE_TIME_TANK_2;
	static const double MOVE_TIME_TANK_3;
	static const double MOVE_TIME_TANK_4;
	
	static const Direction allDirections[];
	
	TimeClock		moveClock;
	TimeClock		shootClock;
	
	bool			dead;
	int				health;
	int				deadScore;
	bool			canDropBonus;
	TimeClock		blinkBonusClock;
	int				blinkBonusIndex;
	
	TimeClock		blinkTank4Clock;
	int				blinkTank4Index;

	int				lastTankColor;
public:
	EnemyTank(Map* m, Scene* s, int x, int y, int model, bool bonus = false);
	~EnemyTank();
public:
	void update(double dt);
	
	void render(Graphics* gr);
	
	//!
	//! Generar un daño al tanque
	//!
	void hurt();
	
	//!
	//! Matar completamente al tanque
	//!
	void kill();
	
	//!
	//! Comprobar si está muerto
	//!
	//! \return true si está muerto, falso en caso contrario
	//!
	bool isDead() const
	{
		return dead;
	}
	
	//!
	//! Obtener el puntaje que se debe incrementar al héroe cuando se elimina al tanque enemigo
	//!
	//! \return Puntaje
	//!
	int getDeadScore() const
	{
		return deadScore;
	}
	//!
	//! Obtener el tipo de tanque enemigo (0 ... 3)
	//!
	//! \return Tipo de tanque enemigo
	//!
	int getTankEnemyType() const
	{
		return (tankModel-TANK_MODEL_ENEMY_1);
	}
private:
	void shoot();
	bool move(Direction dir);
	std::vector<Direction> getRandomDirections(Direction thisNot) const;
};

#endif
