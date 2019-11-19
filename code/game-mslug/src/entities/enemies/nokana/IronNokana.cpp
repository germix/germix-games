////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IronNokana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/nokana/IronNokana.h>
#include <src/Debug.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/NormalExplosionB.h>
#include <src/entities/enemies/nokana/IronNokanaRocket.h>
#include <src/entities/enemies/nokana/IronNokanaCannonShot.h>
#include <src/entities/enemies/nokana/IronNokanaCannonBullet.h>
#include <src/entities/friendly/Hostage.h>
#include <src/entities/bonus/Bonus_Bombs.h>
#include <src/entities/bonus/Bonus_WeaponH.h>

#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>


#define TIME_FLAT_TIRE			0.1
#define TIME_LIFT_UP			0.14
#define TIME_DESTROYED2			1.00

const int IronNokana::wheelsToHull[] =
{
	// FullHealth = [0..3]
	0,1,0,1, 
	// FlatTire   = [4..7]
	2,3,2,3,
	// LiftUp     = [8..26]
	3,				// 1º
	4,				// 2º
	5,				// 3º
	5,				// 4º
	6,				// 5º
	7,				// 6º
	8,				// 7º (Sin cañón)
	8,				// 8º (Sin cañón)
	8,				// 9º (Sin cañón)
	8,				// 10º (Sin cañón)
	8,				// 11º (Sin cañón)
	8,				// 12º (Sin cañón)
	8,				// 13º (Sin cañón)
	8,				// 14º (Sin cañón)
	8,				// 15º (Sin cañón)
	8,				// 16º (Sin cañón)
	8,				// 17º (Sin cañón)
	8,				// 18º (Sin cañón)
	9,				// 19º
	// Up         = [27]
	8,
	// Destroyed  = [28]
	10
};
const int IronNokana::hullToLauncher[] =
{
	0,1,
	2,3,
	4,
	5,
	6,
	7,
	8,
	7,9
};
const int IronNokana::hullToLauncherLength = (sizeof(hullToLauncher)/sizeof(hullToLauncher[0]));

class IronNokanaHullHurtableRect : public HurtableRect
{
	IronNokana* ironNokana;
public:
	IronNokanaHullHurtableRect(IronNokana* e) : ironNokana(e)
	{
	}
public:
	void hurt(int damage)
	{
		ironNokana->health -= damage;
		if(ironNokana->health <= 0)
		{
			ironNokana->state = IronNokana::STATE_DESTROYED1;
			ironNokana->destroyed = true;
			ironNokana->indexWheels = 0;
			ironNokana->turretHandler.destroy();
			//
			// Asignar puntaje
			//
			ironNokana->scene->getHero()->addScore(500);
		}
		else if(ironNokana->health <= 300)
		{
			if(ironNokana->state == IronNokana::STATE_IDLE)
			{
				ironNokana->state = IronNokana::STATE_FLAT_TIRE;
				ironNokana->indexWheels = 0;
				ironNokana->repeats = 0;
				ironNokana->clock.reset(TIME_FLAT_TIRE);
				ironNokana->cannonHandler.stop();
			}
		}
	}
	bool isHurtable() const
	{
		return ironNokana->isAlive();
	}
	Rectanglef hurtableRect() const
	{
		return ironNokana->getHullRectangle();
	}
};
class IronNokanaTurretHurtableRect : public HurtableRect
{
	IronNokana* ironNokana;
public:
	IronNokanaTurretHurtableRect(IronNokana* e) : ironNokana(e)
	{
	}
public:
	void hurt(int damage)
	{
		if(ironNokana->turretHealth > 0)
		{
			ironNokana->turretHealth -= damage;
			if(ironNokana->turretHealth <= 0)
			{
				ironNokana->turretHealth = 0;
				ironNokana->turretHandler.destroy();
				// ...
				Point turretPos = ironNokana->getTurretPosition();
				Rectanglef turretRect = ironNokana->SPRITE_TURRET->rectangle(turretPos.x, turretPos.y, ironNokana->currentFrameTurret, 0);
				int px = (int)turretRect.getCenterX();
				int py = (int)turretRect.getMinY();
				
				ironNokana->scene->addEntity(new Hostage(ironNokana->scene, px-16, py, Bonus_Bombs::NAME));
				ironNokana->scene->addEntity(new Hostage(ironNokana->scene, px+16, py, Bonus_WeaponH::NAME));
			}
		}
	}
	bool isHurtable() const
	{
		return (ironNokana->state == IronNokana::STATE_UP && ironNokana->currentFrameTurret != -1 && ironNokana->turretHealth > 0);
	}
	Rectanglef hurtableRect() const
	{
		Point turretPos = ironNokana->getTurretPosition();
		return ironNokana->SPRITE_TURRET->rectangle("Hit", turretPos.x, turretPos.y, ironNokana->currentFrameTurret, 0);
	}
};

IronNokana::IronNokana(Scene* scene, double x, double y) : Enemy(scene, x, y)
, state(STATE_FIRST)
, indexWheels(0)

, clock(0.07)

, repeats(0)

, currentFrameBackWheels(-1)
, currentFrameFrontWheels(-1)
, currentFrameCannon(-1)
, currentFrameTurret(-1)
, currentFrameTurretFlames(-1)

, cannonHandler()
, turretHandler()
, launcherHandler()

, health(500)
, turretHealth(140)
{
	SpriteSheet* sheet = res.findSpriteSheet("IronNokana");
	SPRITE_HULL = sheet->getSprite("Hull");
	SPRITE_TURRET = sheet->getSprite("Turret");
	SPRITE_FLAMES = sheet->getSprite("Turret.Flames");
	SPRITE_CANNON = sheet->getSprite("Cannon");
	SPRITE_LAUNCHER = sheet->getSprite("Launcher");
	SPRITE_BACKWHEELS = sheet->getSprite("Wheels.Back");
	SPRITE_FRONTWHEELS = sheet->getSprite("Wheels.Front");

	hullHurtableRect = new IronNokanaHullHurtableRect(this);
	turretHurtableRect = new IronNokanaTurretHurtableRect(this);
}
IronNokana::~IronNokana()
{
}
void IronNokana::update(double dt)
{
	switch(state)
	{
		case STATE_FIRST:
			state = STATE_IDLE;
			cannonHandler.init();
			indexWheels = 0;
		case STATE_IDLE:
			updateStateIdle(dt);
			break;
		case STATE_FLAT_TIRE:
			updateStateFlatTire(dt);
			break;
		case STATE_LIFT_UP:
			updateStateLiftUp(dt);
			break;
		case STATE_UP:
			updateStateUp(dt);
			break;
		case STATE_DESTROYED1:
			updateStateDestroyed1(dt);
			break;
		case STATE_DESTROYED2:
			if(clock.update(dt))
			{
				Rectanglef r = getHullRectangle();
				scene->addEntity(new NormalExplosionB(scene, r.getCenterX()-70, r.getCenterY()));
				scene->addEntity(new NormalExplosionB(scene, r.getCenterX(), r.getCenterY()));
				scene->addEntity(new NormalExplosionB(scene, r.getCenterX()+70, r.getCenterY()));
				removable = true;
			}
			break;
	}
	//
	// Seleccionar frame correspondiente a cada parte
	//
	currentFrameBackWheels = -1;
	currentFrameFrontWheels = -1;
	currentFrameCannon = -1;
	currentFrameTurret = -1;
	currentFrameTurretFlames = -1;
	
	switch(state)
	{
		case STATE_FIRST:
		case STATE_IDLE:
			currentFrameFrontWheels = BASE_INDEX_FRONTWHEELS_IDLE+indexWheels;
			
			currentFrameCannon = BASE_INDEX_CANNON_IDLE+cannonHandler.renderableFrame();
			break;
		case STATE_FLAT_TIRE:
			currentFrameFrontWheels = BASE_INDEX_FRONTWHEELS_FLATTIRE+indexWheels;

			currentFrameCannon = BASE_INDEX_CANNON_FLATTIRE+cannonHandler.renderableFrame();
			break;
		case STATE_LIFT_UP:
			currentFrameFrontWheels = BASE_INDEX_FRONTWHEELS_LIFTUP+indexWheels;
			//
			// El '2' es porque hay 2 frames menos
			//
			if(indexWheels >= 2)
			{
				currentFrameBackWheels = BASE_INDEX_BACKWHEELS_LIFTUP+indexWheels-2;
			}
			//
			// En el frame 0, se utiliza un sprite de FLAT_TIRE, que no tiene cañón
			//
			if(indexWheels == 0)
			{
				currentFrameCannon = BASE_INDEX_CANNON_FLATTIRE;
			}
			//
			// El '8', es porque el frame 8 de los frames "LiftUp" no tiene cañón, se utiliza el primero de "Up"
			//
			else if(wheelsToHull[currentFrameFrontWheels] == 8)
			{
				currentFrameCannon = BASE_INDEX_CANNON_UP;
			}
			break;
		case STATE_UP:
			currentFrameBackWheels = BASE_INDEX_BACKWHEELS_UP;
			currentFrameFrontWheels = BASE_INDEX_FRONTWHEELS_UP;
			
			currentFrameCannon = 10+cannonHandler.renderableFrame();
			currentFrameTurret = turretHandler.renderableTurretFrame();
			currentFrameTurretFlames = turretHandler.renderableTurretFlameShotFrame();
			
			break;
		case STATE_DESTROYED1:
		case STATE_DESTROYED2:
			currentFrameBackWheels = BASE_INDEX_BACKWHEELS_DESTROYED;
			currentFrameFrontWheels = BASE_INDEX_FRONTWHEELS_DESTROYED;
			
			currentFrameTurret = turretHandler.renderableTurretFrame();
			break;
		
	}
	//
	// Comprobar intersección del heroe con las llamas
	//
	if(currentFrameTurretFlames != -1)
	{
		Hero* hero = scene->getHero();
		
		if(hero->bounds().intersects(getFlamesRectangle()))
		{
			hero->hurt();
		}
	}
}
void IronNokana::render(Graphics* gr)
{
	if(removable)
		return;
	
	//
	// Dibujar ruedas posteriores
	//
	if(currentFrameBackWheels != -1)
	{
		SPRITE_BACKWHEELS->render(gr, pos.x, pos.y, currentFrameBackWheels, 0);
	}
	//
	// Dibujar armazón
	//
	{
		Point hullPos = SPRITE_FRONTWHEELS->point("Hull", pos.x, pos.y, currentFrameFrontWheels, 0);
		int   hullFrame = wheelsToHull[currentFrameFrontWheels];
		
		//
		// Dibujar lanza cohetes
		//
		if(hullFrame < hullToLauncherLength)
		{
			int launcherFrame = hullToLauncher[hullFrame];
			Point launcherPos = SPRITE_HULL->point("Launcher", hullPos.x, hullPos.y, hullFrame, 0);
			SPRITE_LAUNCHER->render(gr, launcherPos.x, launcherPos.y, launcherFrame, 0);
		}
		// ...
		SPRITE_HULL->render(gr, hullPos.x, hullPos.y, hullFrame, 0);
		
		//
		// Dibujar cañón
		//
		if(currentFrameCannon != -1)
		{
			Point cannonPos = SPRITE_HULL->point("Cannon", hullPos.x, hullPos.y, hullFrame, 0);
			
			SPRITE_CANNON->render(gr, cannonPos.x, cannonPos.y, currentFrameCannon, 0);
		}
	}
	//
	// Dibujar torreta
	//
	if(currentFrameTurret != -1)
	{
		Point turretPos = SPRITE_FRONTWHEELS->point("Turret", pos.x, pos.y, currentFrameFrontWheels, 0);
		SPRITE_TURRET->render(gr, turretPos.x, turretPos.y, currentFrameTurret, 0);
		
		if(currentFrameTurretFlames != -1)
		{
			Point flamesPos = SPRITE_TURRET->point("Flames", turretPos.x, turretPos.y, currentFrameTurret, 0);
			
			SPRITE_FLAMES->render(gr, flamesPos.x, flamesPos.y, currentFrameTurretFlames, 0);
		}
	}
	//
	// Dibujar ruedas frontales
	//
	if(currentFrameFrontWheels != -1)
	{
		SPRITE_FRONTWHEELS->render(gr, pos.x, pos.y, currentFrameFrontWheels, 0);
	}
	if(Debug::showEnemyRects)
	{
		gr->drawRect(bounds(), Debug::colorEnemyRects);
		
		if(hullHurtableRect->isHurtable())
		{
			gr->drawRect(hullHurtableRect->hurtableRect(), Debug::colorEnemyRects);
		}
		if(turretHurtableRect->isHurtable())
		{
			gr->drawRect(turretHurtableRect->hurtableRect(), Debug::colorEnemyRects);
		}
		if(currentFrameTurretFlames != -1)
		{
			gr->drawRect(getFlamesRectangle(), Debug::colorEnemyRects);
		}
	}
}
Rectanglef IronNokana::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef IronNokana::bounds(double px, double py) const
{
	return Rectanglef(px-88,py-150, 176, 150);
}
void IronNokana::getHurtableRects(const Rectanglef& area, std::vector<HurtableRect*>& rects) const
{
	if(isAlive())
	{
		if(hullHurtableRect->isHurtable() && hullHurtableRect->hurtableRect().intersects(area))
		{
			rects.push_back(hullHurtableRect);
		}
		if(turretHurtableRect->isHurtable() && turretHurtableRect->hurtableRect().intersects(area))
		{
			rects.push_back(turretHurtableRect);
		}
	}
}
bool IronNokana::isAlive() const
{
	return true;
}
Point IronNokana::getHullPosition() const
{
	return SPRITE_FRONTWHEELS->point("Hull", pos.x, pos.y, currentFrameFrontWheels, 0);
}
Rectanglef IronNokana::getHullRectangle() const
{
	Point hullPos = getHullPosition();
	return SPRITE_HULL->rectangle("Hit", hullPos.x, hullPos.y, wheelsToHull[currentFrameFrontWheels], 0);
}
Point IronNokana::getTurretPosition() const
{
	return SPRITE_FRONTWHEELS->point("Turret", pos.x, pos.y, currentFrameFrontWheels, 0);
}
Rectanglef IronNokana::getFlamesRectangle() const
{
	if(currentFrameTurretFlames != -1)
	{
		Point turretPos = getTurretPosition();
		Point flamesPos = SPRITE_TURRET->point("Flames", turretPos.x, turretPos.y, currentFrameTurret, 0);
		
		return SPRITE_FLAMES->rectangle("Burn", flamesPos.x, flamesPos.y, currentFrameTurretFlames, 0);
	}
	return Rectanglef();
}
Point IronNokana::getCannonShotPosition() const
{
	Point hullPos = getHullPosition();
	Point cannonPos = SPRITE_HULL->point("Cannon", hullPos.x, hullPos.y, wheelsToHull[currentFrameFrontWheels], 0);
	Point cannonShotPos = SPRITE_CANNON->point("Shot", cannonPos.x, cannonPos.y, currentFrameCannon, 0);
	
	return cannonShotPos;
}
Point IronNokana::getRocketLauncherShootPosition() const
{
	Point hullPos = getHullPosition();
	int   hullFrame = wheelsToHull[currentFrameFrontWheels];
	Point launcherPos = SPRITE_HULL->point("Launcher", hullPos.x, hullPos.y, hullFrame, 0);
	Point shootingPos = SPRITE_LAUNCHER->point("Shoot1", launcherPos.x, launcherPos.y, hullToLauncher[hullFrame], 0);
	
	return shootingPos;
}
void IronNokana::updateStateIdle(double dt)
{
	//
	// Actualizar cañon
	//
	updateCannon(dt);
	
	//
	// Actualizar animación
	//
	if(clock.update(dt))
	{
		indexWheels++;
		if(indexWheels >= MAX_WHEELS_FULLHEALTH)
		{
			indexWheels = 0;
		}
	}
}
void IronNokana::updateStateFlatTire(double dt)
{
	//
	// Actualizar animación
	//
	if(clock.update(dt))
	{
		indexWheels++;
		if(indexWheels >= MAX_WHEELS_FLATTIRE)
		{
			indexWheels = 0;
			
			repeats++;
			if(repeats == 2)
			{
				state = STATE_LIFT_UP;
				repeats = 0;
				clock.reset(TIME_LIFT_UP);
			}
		}
	}
}
void IronNokana::updateStateLiftUp(double dt)
{
	//
	// Actualizar animación
	//
	if(clock.update(dt))
	{
		indexWheels++;
		if(indexWheels >= MAX_WHEELS_LIFTUP)
		{
			state = STATE_UP;
			indexWheels = 0;
			repeats = 0;
			cannonHandler.init();
		}
	}
}
void IronNokana::updateStateUp(double dt)
{
	updateCannon(dt);
	updateTurret(dt);
	updateLauncher(dt);
}
void IronNokana::updateStateDestroyed1(double dt)
{
	updateTurret(dt);
	if(turretHandler.isDestroyed())
	{
		state = STATE_DESTROYED2;
		clock.reset(TIME_DESTROYED2);
	}
}
void IronNokana::updateCannon(double dt)
{
	if(cannonHandler.update(dt))
	{
		Point shot = getCannonShotPosition();
		
		scene->addEntity(new IronNokanaCannonShot(scene, shot.x, shot.y));
		scene->addEntity(new IronNokanaCannonBullet(scene, shot.x, shot.y));
	}
}
void IronNokana::updateTurret(double dt)
{
	if(turretHandler.update(dt))
	{
		Point turretPos = getTurretPosition();
		Rectanglef r = SPRITE_TURRET->rectangle(turretPos.x, turretPos.y, currentFrameTurret, 0);
		
		scene->addEntity(new NormalExplosionB(scene, r.getCenterX(), r.getCenterY()));
	}
}
void IronNokana::updateLauncher(double dt)
{
	if(turretHandler.isDestroyed())
	{
		Route* route;
		
		if(null != (route = launcherHandler.update(dt)))
		{
			Point shoot = getRocketLauncherShootPosition();
			scene->addEntity(new IronNokanaRocket(scene, shoot.x, shoot.y, route));
		}
	}
}
