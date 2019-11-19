////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Hero
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/Hero.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/sprites/Sprite.h>
#include <src/sprites/SpriteSheet.h>
#include <src/Scene.h>
#include <src/entities/enemies/bullets/EnemyBullet.h>
#include <src/entities/explosions/NormalExplosion.h>
#include <src/entities/hero/weapons/Weapon_Normal.h>
#include <src/entities/hero/SideFighterReinforcement.h>

#include <mach/Mixer.h>
#include <mach/Keyboard.h>

#define MIDDLE_NORMAL_INDEX		2

#define VELOCITY_NORMAL			210.0
#define VELOCITY_LOOPING_X		VELOCITY_NORMAL
#define VELOCITY_LOOPING_Y		(VELOCITY_NORMAL/2)
#define VELOCITY_ENTERING		150.0
#define VELOCITY_LEAVING		(VELOCITY_NORMAL-10)
#define VELOCITY_RELIVING		(VELOCITY_NORMAL+20)

static int SHOOT_KEY = Key::LETTER_X;
static int ATTACK_KEY = Key::LETTER_Z;

Hero::Hero(Scene* scene, double x, double y) : Entity(scene, x, y)
, state(STATE_READY)
, alive(true)
, loser(false)

, score()
, tmpScore()

, lives(3)

, health(100)
, maxHealth(100)

, sheet(null)
, sprite(null)
, spriteIndex(0)

, shootTime(0)
, primaryWeapon()
, secondaryWeapon()

, moveLeftTime(0)
, moveRightTime(0)

, loopingTime(0)

, ascendTime(0)

, descendTime(0)

, enteringTime(0.2)

, dyingTime(0.1)

, reinforcement(null)

, canHurt(true)
, hurtTime(0.4)
{
	sheet = res.findSpriteSheet("hero.classic");

	primaryWeapon.setWeapon(new Weapon_Normal());
}
Hero::~Hero()
{
	if(reinforcement)
	{
		delete reinforcement;
	}
}
Rectanglef Hero::rect() const
{
	if(state == STATE_NORMAL
		|| state == STATE_LOOPING
		|| state == STATE_ASCEND
		|| state == STATE_DESCEND
		|| state == STATE_ENTERING
		|| state == STATE_LEAVING)
	{
		return sprite->rect(pos);
	}
	return Rectanglef();
}
void Hero::update(double dt)
{
	if(hurtTime.update(dt))
	{
		canHurt = true;
	}
	switch(state)
	{
		case STATE_READY:
			break;
		case STATE_NORMAL:
		case STATE_LOOPING:
			if(state == STATE_NORMAL)
				updateForNormal(dt);
			else
				updateForLooping(dt);
			
			secondaryWeapon.update(dt);
			break;
		case STATE_ASCEND:
			updateForAscend(dt);
			break;
		case STATE_DESCEND:
			updateForDescend(dt);
			break;
		case STATE_ENTERING:
			updateForEntering(dt);
			break;
		case STATE_LEAVING:
			updateForLeaving(dt);
			break;
	//	case STATE_HURT:
	//		break;
		case STATE_DYING:
			updateForDying(dt);
			break;
		case STATE_DEAD:
			updateForDead(dt);
			break;
		case STATE_RELIVING:
			updateForReliving(dt);
			break;
	}
	//
	// Actualizar refuerzos
	//
	if(reinforcement != null)
	{
		if(reinforcement->update(dt))
		{
			delete reinforcement;
			reinforcement = null;
		}
	}
}
void Hero::render(Graphics* gr)
{
	if(state != STATE_READY && state != STATE_DEAD)
	{
		sprite->render(gr, pos.x, pos.y, spriteIndex);
	}
	//
	// Dibujar refuerzos
	//
	if(reinforcement != null)
	{
		reinforcement->render(gr);
	}
}
void Hero::enter(double x, double y)
{
	if(state == STATE_READY)
	{
		pos = Vector2f(x, y);
		state = STATE_ENTERING;
		// ...
		score.addScore(tmpScore.getScore());
		tmpScore.reset();
		// ...
		enteringTime.reset();
		// ...
		sprite = sheet->getSprite("Starting");
		spriteIndex = 0;
	}
}
void Hero::leave()
{
	if(alive)
	{
		state = STATE_LEAVING;
		sprite = sheet->getSprite("Normal");
		spriteIndex = 2;
	}
}
void Hero::ascend(double x, double y)
{
	if(state == STATE_READY)
	{
		pos = Vector2f(x, y);
		state = STATE_ASCEND;
		// ...
		score.addScore(tmpScore.getScore());
		tmpScore.reset();
		// ...
		ascendTime.reset(1.2);
		sprite = sheet->getSprite("Ascend");
		spriteIndex = 0;
	}
}
void Hero::descend()
{
	if(alive)
	{
		state = STATE_DESCEND;
		descendTime = 0;
		sprite = sheet->getSprite("Descend");
		spriteIndex = 0;
	}
}
bool Hero::isAlive() const
{
	return alive;
}
bool Hero::isReady() const
{
	return (state == STATE_READY);
}
bool Hero::isLoser() const
{
	return loser;
}
int Hero::getScore() const
{
	return score.getScore() + tmpScore.getScore();
}
void Hero::addScore(int value)
{
	tmpScore.addScore(value);
}
void Hero::resetTempScore()
{
	tmpScore.reset();
}
int Hero::getHealth() const
{
	return health;
}
int Hero::getMaxHealth() const
{
	return maxHealth;
}
void Hero::addHealth(int h)
{
	setHealth(health + h);
}
void Hero::setHealth(int h)
{
	health = h;
	if(health > maxHealth)
		health = maxHealth;
}
void Hero::hurt(int damage)
{
	if(canHurt)
	{
		canHurt = false;
		hurtTime.reset();
		// ...
		health -= damage;
		if(health <= 0)
		{
			alive = false;
			health = 0;
			state = STATE_DYING;
			dyingTime.reset();
			// ...
			sprite = sheet->getSprite("Dying");
			spriteIndex = 0;
			// ...
			if(reinforcement)
			{
				delete reinforcement;
				reinforcement = null;
			}
			Mixer::playChannel(res.findSound("explosions.hero.destroyed"));
		}
	}
}
int Hero::getLives() const
{
	return lives;
}
int Hero::getCollisionDamage() const
{
	return 10;
}
void Hero::checkHit(EnemyBullet* bullet)
{
	if(rect().intersects(bullet->rect()))
	{
		hurt(bullet->collisioned());
		if(isAlive())
		{
			scene->addEntity(new NormalExplosion(scene,
					bullet->position().x,
					bullet->position().y,
					null,
					"explosions.hero.hit",
					"explosions.hero.hit"));
		}
	}
	else if(reinforcement != null)
	{
		if(reinforcement->checkHit(bullet))
		{
			delete reinforcement;
			reinforcement = null;
		}
	}
}
void Hero::setSecondaryWeapon(Weapon* w)
{
	secondaryWeapon.setWeapon(w);
}
void Hero::reloadSecondaryWeapon()
{
	secondaryWeapon.reload();
}
void Hero::activateReinforcement()
{
	if(!reinforcement)
	{
		reinforcement = new SideFighterReinforcement(scene, this);
	}
}
void Hero::loop()
{
	printf("Enter to LOOPING state\n");
	if(state == STATE_NORMAL)
	{
		state = STATE_LOOPING;
		loopingTime = 0;
		sprite = sheet->getSprite("Looping");
		spriteIndex = 0;
	}
}
void Hero::tryShoot(double dt)
{
	if(Keyboard::isDown(SHOOT_KEY))
	{
		bool initialTrigger = !Keyboard::isRepeated(SHOOT_KEY);
		
		if(initialTrigger)
			shootTime = 0;
		else
			shootTime += dt;
		
		if(!secondaryWeapon.trigger(scene, pos.x, pos.y, initialTrigger, shootTime, isReinforced()))
		{
			primaryWeapon.trigger(scene, pos.x, pos.y, initialTrigger, shootTime, isReinforced());
		}
	}
}
void Hero::tryAttack()
{
	if(Keyboard::isDown(ATTACK_KEY))
	{
		scene->callSpecialAttack();
	}
}
bool Hero::isReinforced() const
{
	return (reinforcement != null);
}
void Hero::updateForEntering(double dt)
{
	pos.y -= (VELOCITY_ENTERING*dt);
	if(enteringTime.update(dt))
	{
		if(++spriteIndex >= sprite->count)
		{
			printf("Hero to NORMAL state\n");
			state = STATE_NORMAL;
			sprite = sheet->getSprite("Normal");
			spriteIndex = MIDDLE_NORMAL_INDEX;
			moveLeftTime = 0;
			moveRightTime = 0;
		}
	}
}
void Hero::updateForNormal(double dt)
{
	double velocity = (VELOCITY_NORMAL*dt);

	//
	// Loop
	//
	if(Keyboard::isDown(SHOOT_KEY) && Keyboard::isDown(ATTACK_KEY))
	{
		loop();
	}
	else
	{
		//
		// Movimiento vertical
		//
		if(Keyboard::isDown(Key::UP))
			pos.y -= velocity;
		if(Keyboard::isDown(Key::DOWN))
			pos.y += velocity;
		
		//
		// Movimiento horizontal
		//
		if((Keyboard::isDown(Key::LEFT) && Keyboard::isDown(Key::RIGHT)) || (!Keyboard::isDown(Key::LEFT) && !Keyboard::isDown(Key::RIGHT)))
		{
			spriteIndex = 2;
		}
		else
		{
			if(Keyboard::isDown(Key::LEFT))
			{
				pos.x -= velocity;
				if(spriteIndex > 0)
				{
					moveLeftTime += dt;
					if(moveLeftTime > 0.1)
					{
						moveLeftTime -= 0.1;
						spriteIndex--;
					}
				}
			}
			else
			{
				moveLeftTime = 0;
			}
			if(Keyboard::isDown(Key::RIGHT))
			{
				pos.x += velocity;
				if(spriteIndex < 4)
				{
					moveRightTime += dt;
					if(moveRightTime > 0.1)
					{
						moveRightTime -= 0.1;
						spriteIndex++;
					}
				}
			}
			else
			{
				moveRightTime = 0;
			}
		}
		
		//
		// Chequear posición
		//
		checkBounds();
		
		//
		// Comprobar disparo y ataque especial
		//
		tryShoot(dt);
		tryAttack();
	}
}
void Hero::updateForLooping(double dt)
{
	loopingTime += dt;
	if(loopingTime > 0.2)
	{
		loopingTime -= 0.2;
		if(++spriteIndex >= sprite->count)
		{
			state = STATE_NORMAL;
			sprite = sheet->getSprite("Normal");
			spriteIndex = MIDDLE_NORMAL_INDEX;
		}
	}
	if(state == STATE_LOOPING)
	{
		double velocity;
		
		//
		// Movimiento vertical
		//
		velocity = (VELOCITY_LOOPING_Y*dt);
		switch(spriteIndex)
		{
			case 0:
			case 1:
				pos.y -= velocity;
				break;
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				pos.y += velocity;
				break;
			case 7:
			case 8:
				pos.y -= velocity;
				break;
		}
		//
		// Movimiento horizontal
		//
		velocity = (VELOCITY_LOOPING_X*dt);
		if((Keyboard::isDown(Key::LEFT) && Keyboard::isDown(Key::RIGHT))
			|| (!Keyboard::isDown(Key::LEFT) && !Keyboard::isDown(Key::RIGHT)))
		{
		}
		else
		{
			if(Keyboard::isDown(Key::LEFT))
				pos.x -= velocity;
			if(Keyboard::isDown(Key::RIGHT))
				pos.x += velocity;
		}
		//
		// Chequear posición
		//
		checkBounds();
	}
}
void Hero::updateForLeaving(double dt)
{
	if(rect().getMaxY() < 0)		// Si ya salí del mapa, estoy listo para empezar de nuevo
	{
		state = STATE_READY;
		sprite = null;
	}
	pos.y -= (VELOCITY_LEAVING*dt);
}
void Hero::updateForDescend(double dt)
{
	descendTime += dt;
	if(descendTime > 0.2)
	{
		descendTime -= 0.2;
		if(++spriteIndex >= sprite->count)
		{
			state = STATE_READY;
			sprite = null;
		}
	}
	pos.x += (15*dt);
	pos.y -= (30*dt);
}
void Hero::updateForAscend(double dt)
{
	if(ascendTime.update(dt))
	{
		if(++spriteIndex >= sprite->count)
		{
			state = STATE_NORMAL;
			sprite = sheet->getSprite("Normal");
			spriteIndex = MIDDLE_NORMAL_INDEX;
		}
		if(spriteIndex == 1)
		{
			ascendTime.reset(0.2);
		}
		else if(spriteIndex == 4)
		{
			ascendTime.reset(0.2);
		}
		else if(spriteIndex == 9)
		{
			ascendTime.reset(0.5);
		}
		else if(spriteIndex == 10)
		{
			ascendTime.reset(0.2);
		}
	}
	if(state == STATE_ASCEND)
	{
		double velocity;
		
		//
		// Movimiento vertical
		//
		velocity = (VELOCITY_ENTERING*dt);
		switch(spriteIndex)
		{
			case 0:
			case 1:
			case 2:
			case 3:
				break;
			case 4:
			case 5:
				pos.y -= velocity;
				break;
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
				pos.y += velocity;
				break;
			case 12:
			case 13:
				pos.y -= velocity;
				break;
		}
		//
		// Chequear posición
		//
		checkBounds();
	}
}
void Hero::updateForDying(double dt)
{
	if(dyingTime.update(dt))
	{
		if(++spriteIndex >= sprite->count)
		{
			state = STATE_DEAD;
			sprite = null;
		}
	}
}
void Hero::updateForDead(double dt)
{
	if(lives > 0)
	{
		pos.x = 50;
		pos.y = SCENE_HEIGHT + 20;
		lives--;
		state = STATE_RELIVING;
		sprite = sheet->getSprite("Normal");
		spriteIndex = MIDDLE_NORMAL_INDEX;
	}
	else
	{
		loser = true;
	}
}
void Hero::updateForReliving(double dt)
{
	pos.x = 50;
	pos.y -= (VELOCITY_RELIVING*dt);
	if(pos.y < SCENE_HEIGHT-70)
	{
		alive = true;
		health = maxHealth;
		state = STATE_NORMAL;
		sprite = sheet->getSprite("Normal");
		spriteIndex = MIDDLE_NORMAL_INDEX;
	}
}
void Hero::checkBounds()
{
	double mw = sprite->width/2;
	double mh = sprite->height/2;
	double x1 = 0 + mw;
	double y1 = 20 + mh;
	double x2 = SCENE_WIDTH - mw;
	double y2 = SCENE_HEIGHT - mh - 5;

	if(pos.x < x1)
		pos.x = x1;
	else if(pos.x > x2)
		pos.x = x2;
	if(pos.y < y1)
		pos.y = y1;
	else if(pos.y > y2)
		pos.y = y2;
}
