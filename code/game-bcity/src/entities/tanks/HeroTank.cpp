////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroTank
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/tanks/HeroTank.h>
#include <src/Config.h>
#include <src/base/Sprite.h>
#include <src/base/Player.h>
#include <src/entities/ScoreEffect.h>
#include <src/Scene.h>
#include <src/entities/tanks/EnemyTank.h>
#include <src/entities/bullets/HeroBullet.h>
#include <src/entities/explosions/BigExplosion.h>

#include <mach/Mixer.h>
#include <mach/Keyboard.h>

HeroTank::HeroTank(Player* p, Map* m, Scene* s, int x, int y, int color) : Tank(m, s, x, y, TANK_MODEL_HERO_1+p->getStars(), color)
, state(STATE_NONE)
, lifes(p->getLifes())
, stars(p->getStars())

, hasHelmet(false)
, helmetIndex(0)
, helmetBlinkClock(0.05)
, helmetDurationClock()

, bullet(null)
, canShoot(true)
, shootClock(0.5)

, moveClock(0.026)

, blink()
, initialX(x)
, initialY(y)

, player(p)
{
	keys[0] = KeyMovement(Key::UP,		DIRECTION_UP,		0,		-1	);
	keys[1] = KeyMovement(Key::DOWN,	DIRECTION_DOWN,		0,		+1	);
	keys[2] = KeyMovement(Key::LEFT,	DIRECTION_LEFT,		-1,		0	);
	keys[3] = KeyMovement(Key::RIGHT,	DIRECTION_RIGHT,	+1,		0	);

	victims[0] = victims[1] = victims[2] = victims[3] = 0;
}
HeroTank::~HeroTank()
{
}
void HeroTank::update(double dt)
{
	switch(state)
	{
		case STATE_NONE:
			updateStateNone(dt);
			break;
		case STATE_DEAD:
			updateStateDead(dt);
			break;
		case STATE_PLAYING:
			updateStatePlaying(dt);
			break;
		case STATE_STARTING:
			updateStateStarting(dt);
			break;
		default:
			break;
	}
}
void HeroTank::render(Graphics* gr)
{
	switch(state)
	{
		case STATE_NONE:
			break;
		case STATE_DEAD:
			break;
		case STATE_PLAYING:
			Tank::render(gr);
			if(hasHelmet)
			{
				Config::helmet->render(gr, x, y, helmetIndex);
			}
			break;
		case STATE_STARTING:
			blink.render(gr, x, y);
			break;
		default:
			break;
	}
}
void HeroTank::start()
{
	state = STATE_STARTING;
	x = initialX;
	y = initialY;
}
void HeroTank::damage()
{
	if(lifes > 0 && state == STATE_PLAYING && !hasHelmet)
	{
		//
		// Generar una explosión
		//
		scene->addEntity(new BigExplosion(map, scene, x + width/2 - 2, y + height/2));
		scene->addEntity(new BigExplosion(map, scene, x + width/2 + 4, y + height/2 - 4));

		lifes--;
		stars = 0;
		// ...
		player->setLifes(lifes);
		player->setStars(stars);
		if(lifes == 0)
		{
			removable = true;
			scene->setGameOver();
		}
		else
		{
			start();

			selectTankModel(TANK_MODEL_HERO_1);
		}
	}
}
void HeroTank::addStar()
{
	if(stars < LIMIT_STARS)
	{
		player->setStars(++stars);
		selectTankModel(tankModel+1);
	}
}
void HeroTank::addLife()
{
	player->setLifes(++lifes);
}
void HeroTank::addScore(int s)
{
	player->addScore(s);
}
void HeroTank::addVictim(EnemyTank* victim)
{
	int s = victim->getDeadScore();
	player->addScore(s);
	victims[victim->getTankEnemyType()]++;
//	totalVictims++;
	
	//
	// Generar efecto del puntaje
	//
	scene->addEntity(new ScoreEffect(map, scene, victim->getX(), victim->getY(), s));
}
void HeroTank::activateHelmet(double seconds)
{
	hasHelmet = true;
	helmetDurationClock.reset(seconds);
}
bool HeroTank::isAlive() const
{
	return (lifes > 0);
}
int HeroTank::getScore() const
{
	return player->getScore();
}
int HeroTank::getLifes() const
{
	return lifes;
}
Player* HeroTank::getPlayer() const
{
	return player;
}
const int* HeroTank::getVictims() const
{
	return victims;
}
void HeroTank::shoot()
{
	Point pos = getShootPosition(dir);
	scene->addEntity(bullet = new HeroBullet(
			map,
			scene,
			pos.x,
			pos.y,
			dir,
			this,
			stars >= STAR_SPEED,
			stars >= STAR_STRONG));
	
	Mixer::playChannel(Config::auShot);
}
void HeroTank::updateStateNone(double dt)
{
	start();
}
void HeroTank::updateStateDead(double dt)
{
}
void HeroTank::updateStatePlaying(double dt)
{
	//
	// Comprobar movimiento
	//
	if(moveClock.update(dt))
	{
		for(int i = 0; i < 4; i++)
		{
			if(Keyboard::isDown(keys[i].key))
			{
				if(!keys[i].down)
					keys[i].firstDown = true;
				else
					keys[i].firstDown = false;
				keys[i].down = true;
			}
			else
			{
				keys[i].down = false;
				keys[i].firstDown = false;
			}
		}
		for(int i = 0; i < 4; i++)
		{
			if(keys[i].firstDown)
			{
				dir = keys[i].dir;
				KeyMovement tmp = keys[0];
				keys[0] = keys[i];
				keys[i] = tmp;
			}
		}
		for(int i = 0; i < 4; i++)
		{
			if(keys[i].down && Tank::move(keys[i].dx, keys[i].dy))
			{
				dir = keys[i].dir;
				break;
			}
		}
	}
	
	//
	// Comprobar disparos
	//
	if(stars >= STAR_REPEAT)
	{
		if(shootClock.update(dt))
		{
			canShoot = true;
		}
	}
	else if(bullet == null)
//	else if((bullet == null) || (bullet != null && bullet->isRemovable()))
	{
		canShoot = true;
	}
	if(canShoot)
	{
		if(Keyboard::isDown(Key::SPACE) && !Keyboard::isRepeated(Key::SPACE))
		{
			shoot();
			canShoot = false;
		}
	}
	//
	// Comprobar estado del escudo
	//
	if(hasHelmet)
	{
		if(helmetBlinkClock.update(dt))
		{
			if(++helmetIndex == Config::helmet->getFrameCount())
				helmetIndex = 0;
		}
		if(helmetDurationClock.update(dt))
		{
			hasHelmet = false;
		}
	}
}
void HeroTank::updateStateStarting(double dt)
{
	if(blink.update(dt))
	{
		state = STATE_PLAYING;
		activateHelmet(3);
	}
}

