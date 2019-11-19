////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Weapon | Arma
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Weapon_h___
#define ___Weapon_h___
#include <gamelib/TimeClock.h>

enum WEAPON
{
	WEAPON_PISTOL,
	WEAPON_HEAVY_MACHINE_GUN,
	WEAPON_SHOT_GUN,
	WEAPON_ROCKET_LAUNCHER,
};

class Hero;
class Scene;
class Graphics;
class Sprite;
class SpriteSheet;

class Weapon
{
protected:
	Sprite*		sprite;
	int			spriteFrame;
	bool		shooting;
	TimeClock	shootingClock;
public:
	Weapon()
		: sprite(null)
		, spriteFrame(0)
		, shooting(false)
	{
	}
	virtual ~Weapon()
	{
	}
public:
	//
	// Obtener el tipo del arma
	// Tipo 0: Pistola
	// Tipo 1: Escopeta de ráfagas
	// Tipo 2: Escopeta de un disparo
	//
	virtual int         type() const = 0;
	
	//
	// Obtener el nombre del arma
	//
	virtual const char* name() const = 0;
	
	virtual int         getAmmo(bool firstTime) const = 0;
	virtual bool        canChangeAngleWhileShooting() const = 0;
	
	void                render(Graphics* gr, double posX, double posY, int hints);
	virtual void        reset(SpriteSheet* sheet) = 0;
	virtual int         update(Scene* scene, Hero* hero, double dt, double posX, double posY, int lookX, int shotAngle, int ammo) = 0;
	virtual int         trigger(Scene* scene, Hero* hero, double posX, double posY, int lookX, int shotAngle, int ammo) = 0;

	bool                isShooting() const { return shooting; }
};

#endif
