////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Hero
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Hero_h___
#define ___Hero_h___
#include <src/Entity.h>
#include <src/entities/hero/HeroScore.h>
#include <src/entities/hero/WeaponHandler.h>
#include <src/entities/hero/WeaponHandlerTemporary.h>

#include <gamelib/TimeClock.h>

class Sprite;
class SpriteSheet;
class EnemyBullet;
class SideFighterReinforcement;

class Hero : public Entity
{
	enum STATE
	{
	//	STATE_NONE,
		STATE_READY,				// Listo para iniciar
		STATE_NORMAL,				// Ejecución normal
		STATE_LOOPING,				// Loop
		STATE_ASCEND,				// Despegando del portaaviones (etapa A)
		STATE_DESCEND,				// Descender al final del mapa (etapa A)
		STATE_ENTERING,				// Entrado al inicio del mapa (etapa B)
		STATE_LEAVING,				// Saliendo al final del mapa (etapa B)
	//	STATE_HURT,					// Efecto de daño (¿Usar esto como estado?, talvez usar un boolean)
		STATE_DYING,				// Muriendo en la explosión
		STATE_DEAD,					// Está muerto
		STATE_RELIVING,				// Reviviendo
	};
	STATE						state;
	bool						alive;
	bool						loser;

	HeroScore					score;
	HeroScore					tmpScore;
	
	//
	// Vidas
	//
	int							lives;
	
	//
	// Salud
	//
	int							health;
	int							maxHealth;
	
	//
	// Sprites
	//
	SpriteSheet*				sheet;
	Sprite*						sprite;
	int							spriteIndex;

	//
	// Armas
	//
	double						shootTime;
	WeaponHandler				primaryWeapon;
	WeaponHandlerTemporary		secondaryWeapon;
	
	//
	// Estado: READY
	//
	
	//
	// Estado: NORMAL
	//
	double						moveLeftTime;
	double						moveRightTime;
	
	//
	// Estado: LOOPING
	//
	double						loopingTime;
	
	//
	// Estado: ASCEND
	//
	TimeClock					ascendTime;
	
	//
	// Estado: DESCEND
	//
	double						descendTime;
	
	//
	// Estado: ENTERING
	//
	TimeClock					enteringTime;
	
	//
	// Estado: LEAVING
	//

	//
	// Estado: DYING
	//
	TimeClock					dyingTime;
	
	//
	// Estado: DEAD
	//
	
	//
	// Estado: RELIVING
	//
	
	//
	// Refuerzos
	//
	SideFighterReinforcement*	reinforcement;

	bool						canHurt;
	TimeClock					hurtTime;
	
	friend class SideFighter;
public:
	Hero(Scene* scene, double x, double y);
	~Hero();
public:
	Rectanglef rect() const;
	void update(double dt);
	void render(Graphics* gr);
public:
	void enter(double x, double y);
	void leave();
	void ascend(double x, double y);
	void descend();
	bool isAlive() const;
	bool isReady() const;
	bool isLoser() const;
	int getScore() const;
	void addScore(int value);
	void resetTempScore();
	int getHealth() const;
	int getMaxHealth() const;
	void addHealth(int h);
	void setHealth(int h);
	void hurt(int damage);
	int getLives() const;
	int getCollisionDamage() const;
	void checkHit(EnemyBullet* bullet);

	void setSecondaryWeapon(Weapon* w);
	void reloadSecondaryWeapon();

	void activateReinforcement();
	
	const WeaponHandlerTemporary* getSecondaryWeapon() const
	{
		return &secondaryWeapon;
	}
private:
	void loop();
	void tryShoot(double dt);
	void tryAttack();
	bool isReinforced() const;
	void updateForEntering(double dt);
	void updateForNormal(double dt);
	void updateForLooping(double dt);
	void updateForLeaving(double dt);
	void updateForDescend(double dt);
	void updateForAscend(double dt);
	void updateForDying(double dt);
	void updateForDead(double dt);
	void updateForReliving(double dt);
	void checkBounds();
};

#endif
