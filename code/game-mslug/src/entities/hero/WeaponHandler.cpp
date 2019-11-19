////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WeaponHandler | Controlador de arma
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/WeaponHandler.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/Weapon.h>
#include <src/entities/hero/weapons/Pistol.h>
#include <src/entities/hero/weapons/HeavyMachineGun.h>
#include <src/entities/hero/weapons/ShotGun.h>
#include <src/entities/hero/weapons/RocketLauncher.h>

const double WeaponHandler::NO_ANGLE = 0;
const double WeaponHandler::MIN_ANGLE = -90;
const double WeaponHandler::MAX_ANGLE = 90;

WeaponHandler::WeaponHandler(Hero* h)
: hero(h)
, weapon(null)
, weaponIndex(-1)
, ammo(0)
, step(700)
, shotAngle(0)
, prevShotAngle(0)
{
	weaponList.push_back(new Pistol());
	weaponList.push_back(new HeavyMachineGun());
	weaponList.push_back(new ShotGun());
	weaponList.push_back(new RocketLauncher());
}
WeaponHandler::~WeaponHandler()
{
	for(unsigned int i = 0; i < weaponList.size(); i++)
		delete weaponList[i];
	weaponList.clear();
}
bool		WeaponHandler::isShooting() const
{
	return weapon->isShooting();
}
int			WeaponHandler::setWeapon(SpriteSheet* sheet, int widx)
{
	Weapon* w = weaponList[widx];
	bool    firstTime = ((weapon == null) ? true : (widx != weaponIndex));
	int     addedAmmo = w->getAmmo(firstTime);
	
	if(firstTime || addedAmmo == -1)
		ammo = addedAmmo;
	else
		ammo += addedAmmo;
	
	weapon = w;
	weaponIndex = widx;
	shotAngle = 0;
	prevShotAngle = 0;
	weapon->reset(sheet);
	
#if 1
//	printf("Cambio de arma: %s (%s), balas: %d\n", w->name(), (firstTime : "true" : "false"), ammo);
#endif
	return weapon->type();
}
void		WeaponHandler::setShotAngle(int angle)
{
	shotAngle = angle;
	prevShotAngle = angle;
}
void		WeaponHandler::stop()
{
}
void		WeaponHandler::reset(SpriteSheet* sheet)
{
	weapon->reset(sheet);
}
void		WeaponHandler::render(Graphics* gr, int posX, int posY, int hints)
{
	weapon->render(gr, posX, posY, hints);
}
bool		WeaponHandler::update(Scene* scene, double dt, double posX, double posY, int lookX, int lookY)
{
	//
	// Actualizar ángulo:
	// 1º Caso: Si no está disparando
	// 2º Caso: Está disparando pero el arma actual permite cambio de ángulo durante el disparo
	//
	if(!isShooting() || (isShooting() && weapon->canChangeAngleWhileShooting()))
	{
		updateAngle(dt, lookY);
	}
	int lastAmmo = ammo;
	ammo = weapon->update(scene, hero, dt, posX, posY, lookX, (int)shotAngle, ammo);
	return (lastAmmo != ammo);
}
bool		WeaponHandler::trigger(Scene* scene, double posX, double posY, int lookX)
{
	ammo = weapon->trigger(scene, hero, posX, posY, lookX, (int)shotAngle, ammo);
	return weapon->isShooting();
}
void		WeaponHandler::updateAngle(double dt, int lookY)
{
	prevShotAngle = shotAngle;
	if(hero->isCrouching())
	{
		shotAngle = 0;
	}
	else
	{
		switch(lookY)
		{
			case Hero::LOOK_DIR_Y_UP:
				shotAngle += step*dt;
				if(shotAngle >= MAX_ANGLE)
				{
					shotAngle = MAX_ANGLE;
				}
				break;
			case Hero::LOOK_DIR_Y_NONE:
#if 0
				if(false)
				{
					//
					// Modo: "ya"
					//
					shotAngle = NO_ANGLE;
				}
else
				#endif
				{
					//
					// Modo: "paso a paso"
					//
					if(shotAngle > NO_ANGLE)
					{
						shotAngle -= step*dt;
						if(shotAngle < NO_ANGLE)
							shotAngle = NO_ANGLE;
					}
					else if(shotAngle < NO_ANGLE)
					{
						shotAngle = 0;
#if 0
						shotAngle += step*dt;
						if(shotAngle > NO_ANGLE)
							shotAngle = NO_ANGLE;
#endif
					}
				}
				break;
			case Hero::LOOK_DIR_Y_DOWN:
				if(hero->onAir())
				{
					shotAngle = MIN_ANGLE;
				}
				else
				{
					shotAngle = NO_ANGLE;
				}
#if 0
				shotAngle -= step*dt;
				if(shotAngle <= MIN_ANGLE)
				{
					shotAngle = MIN_ANGLE;
				}
#endif
				break;
		}
	}
}

