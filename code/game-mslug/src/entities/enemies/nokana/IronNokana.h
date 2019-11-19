////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IronNokana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___IronNokana_h___
#define ___IronNokana_h___
#include <src/entities/enemies/Enemy.h>
#include <src/entities/enemies/nokana/IronNokanaCannon.h>
#include <src/entities/enemies/nokana/IronNokanaTurret.h>
#include <src/entities/enemies/nokana/IronNokanaLauncher.h>
#include <src/___/Hurtable.h>

#include <gamelib/TimeClock.h>

class Sprite;

class IronNokana : public Enemy, public Hurtable
{
	enum STATE
	{
		STATE_FIRST,
		STATE_IDLE,
		STATE_FLAT_TIRE,
		STATE_LIFT_UP,
		STATE_UP,
		STATE_DESTROYED1,
		STATE_DESTROYED2,
	};
	enum
	{
		MAX_WHEELS_LIFTUP = 19,
		MAX_WHEELS_FLATTIRE = 4,
		MAX_WHEELS_FULLHEALTH = 4,
		
		//
		// Indices de comienzo de frames correspondientes a cada Sprite y a cada estado
		//
		BASE_INDEX_BACKWHEELS_LIFTUP = 0,
		BASE_INDEX_BACKWHEELS_UP = 17,
		BASE_INDEX_BACKWHEELS_DESTROYED = BASE_INDEX_BACKWHEELS_UP,
		// ...
		BASE_INDEX_FRONTWHEELS_IDLE = 0,
		BASE_INDEX_FRONTWHEELS_FLATTIRE = 4,
		BASE_INDEX_FRONTWHEELS_LIFTUP = 8,
		BASE_INDEX_FRONTWHEELS_UP = 27,
		BASE_INDEX_FRONTWHEELS_DESTROYED = 28,
		// ...
		BASE_INDEX_CANNON_IDLE = 0,
		BASE_INDEX_CANNON_FLATTIRE = 5,
		BASE_INDEX_CANNON_UP = 10,
	};
	static const int wheelsToHull[];
	static const int hullToLauncher[];
	static const int hullToLauncherLength;
	
	STATE				state;
	int					indexWheels;
	
	TimeClock			clock;
	
	
	int					repeats;
	
	//
	// Sprites
	//
	int					currentFrameBackWheels;
	int					currentFrameFrontWheels;
	int					currentFrameCannon;
	int					currentFrameTurret;
	int					currentFrameTurretFlames;
	
	//
	// Partes del acorazado
	//
	IronNokanaCannon	cannonHandler;
	IronNokanaTurret	turretHandler;
	IronNokanaLauncher	launcherHandler;
	
	//
	// Salud/Daño
	//
	int					health;
	int					turretHealth;

	Sprite*				SPRITE_HULL;
	Sprite*				SPRITE_TURRET;
	Sprite*				SPRITE_FLAMES;
	Sprite*				SPRITE_CANNON;
	Sprite*				SPRITE_LAUNCHER;
	Sprite*				SPRITE_BACKWHEELS;
	Sprite*				SPRITE_FRONTWHEELS;
	
	HurtableRect*		hullHurtableRect;
	HurtableRect*		turretHurtableRect;

	friend class IronNokanaHullHurtableRect;
	friend class IronNokanaTurretHurtableRect;
public:
	IronNokana(Scene* scene, double x, double y);
	~IronNokana();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	
	void getHurtableRects(const Rectanglef& area, std::vector<HurtableRect*>& rects) const;
private:
	bool isAlive() const;
	Point getHullPosition() const;
	Rectanglef getHullRectangle() const;
	Point getTurretPosition() const;
	Rectanglef getFlamesRectangle() const;
	Point getCannonShotPosition() const;
	Point getRocketLauncherShootPosition() const;
	void updateStateIdle(double dt);
	void updateStateFlatTire(double dt);
	void updateStateLiftUp(double dt);
	void updateStateUp(double dt);
	void updateStateDestroyed1(double dt);
	void updateCannon(double dt);
	void updateTurret(double dt);
	void updateLauncher(double dt);
};

#endif
