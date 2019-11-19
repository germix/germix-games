////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Hero | Héroe
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/Hero.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/Egg.h>
#include <src/entities/platforms/Platform.h>
#include <src/entities/hero/HeroBulletAx.h>
#include <src/entities/hero/HeroBulletFireball.h>
#include <src/entities/effects/ScoreEffect.h>
#include <src/entities/effects/SplashEffect.h>
#include <src/entities/HiddenEgg.h>
#include <src/entities/JumpSpring.h>

#include <mach/Math.h>
#include <mach/Mixer.h>
#include <mach/Keyboard.h>
#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const double	Hero::TIME_IDLE = 0.15;
const double	Hero::TIME_WALK = 0.1;
const double	Hero::TIME_WALK_POWER = 0.07;
const double	Hero::VELOCITY_WALK = 100;
const double	Hero::VELOCITY_WALK_POWER_ADDITION = 50;
const double	Hero::VELOCITY_SKATE = 130;
const double	Hero::VELOCITY_SKATE_POWER_REDUCTION = -40;
const int		Hero::DISTANCE_JUMP = 32;
const int		Hero::DISTANCE_JUMP_POWERED = 52;
const int		Hero::DISTANCE_SUPERJUMP = 52;
const int		Hero::DISTANCE_SUPERJUMP_POWERED = 92;

static const float ACCEL_WALK = 4.5;
static const float ACCEL_WALK_POWERED = 5.5;
static const float VELOCITY_WALK_POWERED = 140;

Hero::Hero(Scene* s, double x, double y, HeroInfo& i) : Entity(s, x, y)
, state(STATE_IDLE)

, velocity()

, info(i)

, sheet(res.findSpriteSheet("Hero"))
, sprite(null)
, spriteDir(1)
, spriteIndex(0)
, spriteClock(TIME_IDLE)

, onGround(false)
, collisionFlags(0)

, power(false)
, skate(false)
, brakeSkate(false)

, isAttacking(false)
, attackingClock(0.2)

, platform(null)
, honeygirl(null)

, winner(false)
{
	sprite = sheet->getSprite("Idle");

	deadSound = res.findSound("Dead");
}
Hero::~Hero()
{
}
void Hero::update(double dt)
{
	struct
	{
		bool	left;
		bool	right;
		bool	jump;
		bool	power;
		bool	attack;
	}control;

	control.left = Keyboard::isDown(Key::LEFT);
	control.right = Keyboard::isDown(Key::RIGHT);
	control.jump = Keyboard::isDown(Key::LETTER_X);
	control.power = Keyboard::isDown(Key::LETTER_Z);
	control.attack = (Keyboard::isPressed(Key::LETTER_Z) && !Keyboard::isRepeated(Key::LETTER_Z));
	
	bool oldPowerState = power;
	power = control.power;

	if(state == STATE_DEAD)
	{
		return;
	}
	if(spriteClock.update(dt))
	{
		if(++spriteIndex >= sprite->count())
			spriteIndex = 0;
	}
	if(winner && onGround)
	{
		float oldY = pos.y;
		velocity = Vector2f(VELOCITY_WALK, 0);
		motion(dt);
		if(pos.y > oldY)
			pos.y = oldY;
		onGround = true;
		return;
	}
	if(state == STATE_IDLE || state == STATE_WALK || state == STATE_STUMBLE)
	{
		if(pos.y-64 > scene->getCameraRect().getMaxY())
		{
			state = STATE_DEAD;
			Mixer::halt();
			Mixer::playChannel(deadSound);
			return;
		}
		int dx = 0;
		if(skate)
		{
			dx = 1;
			velocity.x = VELOCITY_SKATE;
			
			if(control.left)
			{
				if(!brakeSkate && onGround)
				{
					sprite = sheet->getSprite("Skate-Brake");
					spriteIndex = 0;
				}
				brakeSkate = true;
			}
			else
			{
				if(brakeSkate)
				{
					sprite = sheet->getSprite("Skate-Run");
					spriteIndex = 0;
				}
				brakeSkate = false;
			}
			if(brakeSkate)
				velocity.x += VELOCITY_SKATE_POWER_REDUCTION;
		}
		else
		{
			if(control.left)
				dx--;
			if(control.right)
				dx++;
			if(dx == 0)
			{
				if(state == STATE_WALK)
				{
					/*
					if(onGround)
					{
						state = STATE_IDLE;
						spriteClock.reset(TIME_IDLE);
						sprite = sheet->getSprite("Idle");
						spriteIndex = 0;
					}
					*/
					
					
					state = STATE_IDLE;
					spriteClock.reset(TIME_IDLE);
					if(onGround)
						sprite = sheet->getSprite("Idle");
					else
						sprite = sheet->getSprite("Jump");
					spriteIndex = 0;
				}
			}
			else
			{
				if(state == STATE_IDLE)
				{
					/*
					if(onGround)
					{
						state = STATE_WALK;
						if(!power)
							spriteClock.reset(TIME_WALK);
						else
							spriteClock.reset(TIME_WALK_POWER);
						sprite = sheet->getSprite("Walk");
						spriteIndex = 0;
					}
					*/
				
					state = STATE_WALK;
					if(!power)
						spriteClock.reset(TIME_WALK);
					else
						spriteClock.reset(TIME_WALK_POWER);
					if(onGround)
						sprite = sheet->getSprite("Walk");
					else
						sprite = sheet->getSprite("Jump");
					spriteIndex = 0;
				}
				//if(onGround)
					spriteDir = dx;

				if(power != oldPowerState)
				{
					if(!power)
						spriteClock.reset(TIME_WALK);
					else
						spriteClock.reset(TIME_WALK_POWER);
				}
			}
			//if(onGround)
			{
				/*
				velocity.x = (dx*VELOCITY_WALK);
				if(control.power && dx != 0)
					velocity.x += (VELOCITY_WALK_POWER_ADDITION * spriteDir);
				*/
				float accel = (control.power) ? ACCEL_WALK_POWERED : ACCEL_WALK;
				float limit = (control.power) ? VELOCITY_WALK_POWERED : VELOCITY_WALK;
				float reduce = onGround ? accel : accel/3;
				if(dx > 0)
				{
					velocity.x += accel;
					if(velocity.x > limit)
						velocity.x = limit;
				}
				else if(dx < 0)
				{
					velocity.x -= accel;
					if(velocity.x < -limit)
						velocity.x = -limit;
				}
				else
				{
					if(velocity.x > 0)
					{
						velocity.x -= reduce;
						if(velocity.x < 0)
							velocity.x = 0;
					}
					else if(velocity.x < 0)
					{
						velocity.x += reduce;
						if(velocity.x > 0)
							velocity.x = 0;
					}
				}
			}
			/*
			else
			{
				if((dx > 0 && velocity.x < 0) || (dx < 0 && velocity.x > 0))
				{
					velocity.x = -velocity.x*0.7;
				}
			}
			*/
		}
		if(control.jump)
		{
			if(onGround)
			{
				if(!control.power)
					velocity.y = -Math::sqrt(DISTANCE_JUMP*2*Scene::GRAVITY);
				else
					velocity.y = -Math::sqrt(DISTANCE_JUMP_POWERED*2*Scene::GRAVITY);
					
				if(!skate)
					sprite = sheet->getSprite("Jump");
				else
					sprite = sheet->getSprite("Skate-Jump");
				spriteIndex = 0;

				HiddenEgg* hiddenEgg;
				if(null != (hiddenEgg = scene->getHiddentEgg(bounds())))
				{
					hiddenEgg->drop();
				}
			}
		}
		//
		// Movimiento
		//
		motion(dt);
		
		//
		// No volver atrás de la camara
		//
		Rectanglef cameraRect = scene->getCameraRect();
		Rectanglef entityRect = bounds();
		
		if(cameraRect.getMinX() > entityRect.getMinX())
		{
			pos.x = (cameraRect.getMinX() + 8);
		}
		//
		// Atacar
		//
		if(info.weapon != WEAPON_NONE)
		{
			if(control.attack)
			{
				double vx = 280*spriteDir;
				//double vx = velocity.x + 180*spriteDir;
				double vy = -40;
				if(!isAttacking)
				{
					if(!skate)
					{
						sprite = sheet->getSprite("Attack");
						spriteIndex = 0;
					}
					isAttacking = true;
				}
				if(info.weapon == WEAPON_AX)
					scene->addEntity(new HeroBulletAx(scene, pos.x, pos.y-28, vx, vy));
				else
					scene->addEntity(new HeroBulletFireball(scene, pos.x, pos.y-28, vx, vy));
			}
			if(isAttacking)
			{
				if(attackingClock.update(dt))
				{
					if(skate)
					{
						
					}
					else
					{
						if(!onGround)
						{
							sprite = sheet->getSprite("Jump");
						}
						else
						{
							if(dx == 0)
								sprite = sheet->getSprite("Idle");
							else
								sprite = sheet->getSprite("Walk");
						}
						spriteIndex = 0;
					}
					isAttacking = false;
				}
			}
		}
	}
	else if(state == STATE_DYING)
	{
		collisionFlags = scene->moveEntity(this, dt, pos, velocity, Scene::GRAVITY_ACCELERATION, onGround, false);
		
		if(pos.y-64 > scene->getCameraRect().getMaxY())
		{
			state = STATE_DEAD;
			return;
		}
	}
}
void Hero::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteIndex, (spriteDir == -1) ? Sprite::FLIP_X : 0);

	if(Debug::showHeroVelocityMarks)
	{
		Rectanglef rc = bounds();

		if(velocity.y < 0)
		{
			gr->fillRect((int)rc.getX(), (int)rc.getMinY(), (int)rc.getWidth(), 5, Color(0,0,255));
		}
		else if(velocity.y > 0)
		{
			gr->fillRect((int)rc.getX(), (int)rc.getMaxY() - 5, (int)rc.getWidth(), 5, Color(0,0,255));
		}
	}
	if(Debug::showHeroCollisionEdges)
	{
		Rectanglef rc = bounds();
		
		if(0 != (collisionFlags & COLLISION_FLAG_LEFT))
			gr->fillRect((int)rc.getMinX(), (int)rc.getMinY(), 3, (int)rc.getHeight(), Color(0,255,255));
		if(0 != (collisionFlags & COLLISION_FLAG_RIGHT))
			gr->fillRect((int)rc.getMaxX()-3, (int)rc.getMinY(), 3, (int)rc.getHeight(), Color(0,255,255));
		if(0 != (collisionFlags & COLLISION_FLAG_TOP))
			gr->fillRect((int)rc.getX(), (int)rc.getMinY(), (int)rc.getWidth(), 3, Color(0,255,255));
		if(0 != (collisionFlags & COLLISION_FLAG_BOTTOM))
			gr->fillRect((int)rc.getX(), (int)rc.getMaxY() - 3, (int)rc.getWidth(), 3, Color(0,255,255));
	}
}
Rectanglef Hero::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef Hero::bounds(double px, double py) const
{
	return Rectanglef(px - 8, py - 32, 16, 32);
}
void Hero::collides(Entity* e)
{
	if(dynamic_cast<Egg*>(e))
	{
		((Egg*)e)->kick(velocity.x);
	}
	else if(dynamic_cast<JumpSpring*>(e))
	{
		JumpSpring* js = (JumpSpring*)e;
	}
}
Rectanglef Hero::getCollisionRectangle() const
{
	return bounds();
}
void Hero::dead()
{
	if(state != STATE_DYING)
	{
		state = STATE_DYING;
		sprite = sheet->getSprite("Dead");
		spriteIndex = 0;
		velocity.x = 0;
		velocity.y = -Math::sqrt(DISTANCE_JUMP*2*Scene::GRAVITY);
		
		Mixer::halt();
		Mixer::playChannel(deadSound);
	}
}
bool Hero::isDead() const
{
	return (state == STATE_DEAD);
}
void Hero::burn()
{
	if(state != STATE_DYING)
	{
		state = STATE_DYING;
		sprite = sheet->getSprite("Dead-Fire");
		spriteIndex = 0;
		velocity.x = 0;
		velocity.y = -Math::sqrt(DISTANCE_JUMP*2*Scene::GRAVITY);

		Mixer::halt();
		Mixer::playChannel(deadSound);
	}
}
void Hero::freeze()
{
	if(state != STATE_DYING)
	{
		state = STATE_DYING;
		sprite = sheet->getSprite("Dead-Freeze");
		spriteIndex = 0;
		velocity.x = 0;
		velocity.y = -Math::sqrt(DISTANCE_JUMP*2*Scene::GRAVITY);

		Mixer::halt();
		Mixer::playChannel(deadSound);
	}
}
void Hero::stumble()
{
	stumble(true);
}
void Hero::stumble(bool decreaseHealth)
{
	if(state != STATE_STUMBLE && state != STATE_DYING)
	{
		if(decreaseHealth)
		{
			info.health--;
			if(info.health == 0)
			{
				dead();
				return;
			}
		}
		state = STATE_STUMBLE;
		onGround = false;
		sprite = sheet->getSprite("Stumble");
		spriteIndex = 0;
		velocity = Vector2f((VELOCITY_WALK+10)*spriteDir, -120);
	}
}
void Hero::setPot()
{
	info.pot = true;
}
void Hero::addLife()
{
	info.lives++;
}
void Hero::setWeapon(int w)
{
	info.weapon = w;
}
bool Hero::hasSkate() const
{
	return skate;
}
void Hero::setSkate()
{
	skate = true;
	sprite = sheet->getSprite("Skate-Run");
	spriteDir = 1;
	spriteIndex = 0;
}
void Hero::releaseSkate()
{
	skate = false;

	state = STATE_STUMBLE;
	onGround = false;
	sprite = sheet->getSprite("Stumble");
	spriteIndex = 0;
	velocity = Vector2f(VELOCITY_WALK*spriteDir, -120);
}
void Hero::releaseSkate(const Vector2f& p)
{
	releaseSkate();
	addScore(50, 0);
	scene->addEntity(new ScoreEffect(scene, p.x, p.y, 50));
	scene->addEntity(new SplashEffect(scene, pos.x, pos.y));
	stumble(false);
}
void Hero::addScore(int score, int health)
{
	info.score += score;
	info.health += health;
	if(info.health >= HeroInfo::MAX_HEALTH)
		info.health = HeroInfo::MAX_HEALTH;
}
void Hero::setFullHealth()
{
	info.health = HeroInfo::MAX_HEALTH;
}
Vector2f Hero::getVelocity() const
{
	return velocity;
}
bool Hero::hasHoneygirl() const
{
	return honeygirl != null;
}
void Hero::setHoneygirl(Honeygirl* hg)
{
	honeygirl = hg;
}
void Hero::releaseHoneygirl()
{
	honeygirl = null;
}
void Hero::respawn(const Vector2f& respawnPosition)
{
	pos = respawnPosition;
	velocity = Vector2f(0,0);
	state = STATE_IDLE;
	spriteClock.reset(TIME_IDLE);
	info.reset();
	sprite = sheet->getSprite("Idle");
	spriteIndex = 0;
	info.weapon = WEAPON_NONE;
	spriteDir = 1;
	skate = false;
	winner = false;
	honeygirl = null;
}
void Hero::setPositionY(double y)
{
	pos.y = y;
	velocity.y = 0;
}
void Hero::translatePositionX(double dx)
{
	pos.x += dx;
}
void Hero::superJump()
{
	if(!power)
		velocity.y = -Math::sqrt(DISTANCE_SUPERJUMP*2*Scene::GRAVITY);
	else
		velocity.y = -Math::sqrt(DISTANCE_SUPERJUMP_POWERED*2*Scene::GRAVITY);
		
	if(!skate)
		sprite = sheet->getSprite("Jump");
	else
		sprite = sheet->getSprite("Skate-Jump");
	spriteIndex = 0;
	// ...
	platform = null;
	onGround = false;
}
void Hero::win()
{
	winner = true;
	if(onGround)
	{
		sprite = sheet->getSprite("Walk");
		spriteIndex = 0;
	}
}
void Hero::motion(double dt)
{
	Vector2f oldPosition = pos;
	Vector2f oldVelocity = velocity;
	Vector2f acceleration = Scene::GRAVITY_ACCELERATION;
	
	//
	// Ecuación cinemática de posición
	//
	// y' = y + v*dt + (a*dt^2)/2
	//
	Vector2f newPosition(
			oldPosition.x + oldVelocity.x*dt + (acceleration.x*dt*dt)/2,
			oldPosition.y + oldVelocity.y*dt + (acceleration.y*dt*dt)/2);
	
	//
	// Ecuación cinemática de velocidad
	//
	// v' = v + a*dt
	//
	Vector2f newVelocity(
		oldVelocity.x + acceleration.x*dt,
		oldVelocity.y + acceleration.y*dt);
	
	//
	// Detectar colisión con plataformas y terreno
	//
//	if(platform == null)
	{
		unsigned int cflags = 0;
		std::list<Platform*> platforms = scene->getPlatforms();
		
		for(std::list<Platform*>::const_iterator it = platforms.begin(); it != platforms.end(); it++)
		{
			Platform* p = *it;
			Rectanglef rc;
			Rectanglef pr = p->getCollisionRectangle();
			
			//
			// Colisión en Y
			//
			if(newVelocity.y > 0 || newVelocity.y < 0)
			{
				if(newVelocity.y > 0)
					rc = bounds(newPosition.x, Math::ceil(newPosition.y));
				else
					rc = bounds(newPosition.x, Math::floor(newPosition.y));
				if(rc.intersects(pr))
				{
					Rectanglef pi = rc.intersected(pr);
					
					if(newVelocity.y > 0)
					{
						if(oldPosition.y <= pi.getMinY())
						{
							newPosition.y = pi.getMinY();
							newVelocity.y = 0;
							cflags |= COLLISION_FLAG_BOTTOM;
						}
					}
				}
			}
			if(cflags != 0)
			{
				platform = p;
				platform->setHero(this);
				break;
			}
		}
		//
		// Detectar colisión con el terreno
		//
		//if(cflags == 0)
		{
			cflags |= scene->checkCollision(
					this,
					newPosition,
					newVelocity,
					oldPosition,
					oldVelocity,
					MAP_TERRAIN_SOLID|MAP_TERRAIN_TOPDOWN);
		}
		pos = newPosition;
		velocity = newVelocity;
		collisionFlags = cflags;
		if(0 != (collisionFlags & COLLISION_FLAG_BOTTOM))
		{
			if(!onGround)
			{
				if(winner)
				{
					sprite = sheet->getSprite("Walk");
				}
				else
				{
					if(!skate)
					{
						if(state == STATE_IDLE || state == STATE_STUMBLE)
						{
							state = STATE_IDLE;
							sprite = sheet->getSprite("Idle");
							spriteClock.reset(TIME_IDLE);
						}
						else
						{
							sprite = sheet->getSprite("Walk");
							spriteClock.reset(TIME_WALK);
						}
					}
					else
					{
						if(!brakeSkate)
							sprite = sheet->getSprite("Skate-Run");
						else
							sprite = sheet->getSprite("Skate-Brake");
					}
				}
				spriteIndex = 0;
			}
			onGround = true;
		}
		else
		{
			onGround = false;
			if(platform != null)
			{
				platform->releaseHero();
				platform = null;
			}
		}
	}
}
