////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Hero | Héroe
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/Hero.h>
#include <src/Debug.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Weapon.h>
#include <src/___/Knifeable.h>

#include <string>

#include <mach/Math.h>
#include <mach/Random.h>
#include <mach/Mixer.h>
#include <mach/Color.h>
#include <mach/Graphics.h>
#include <mach/Keyboard.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>
#include <gamelib-sprites/SpriteSheetLoader.h>


#define KEY_JUMP		Key::LETTER_S
#define KEY_BOMB		Key::LETTER_D
#define KEY_SHOOT		Key::LETTER_A
#define KEY_UP			Key::UP
#define KEY_DOWN		Key::DOWN
#define KEY_LEFT		Key::LEFT
#define KEY_RIGHT		Key::RIGHT

//
// ...
//

#define DISTANCE_JUMP					56
#define VELOCITY_WALK_CROUCHING			50.0
#define VELOCITY_WALK_STANDINGUP		100.0

#define TIME_BOMB						0.047
#define TIME_KNIFE						0.045
#define TIME_CROUCH						0.074
#define TIME_STANDUP					0.074
#define TIME_IDLE_CROUCHED				0.14
#define TIME_IDLE_STANDING				0.14
#define TIME_WINNER						0.05
#define TIME_DYING						0.08
#define TIME_WALKING_STANDUP			0.042
#define TIME_WALKING_CROUCHED			0.078

#define TIME_DEAD						1

Hero::Hero(Scene* scene, double x, double y, const char* name, bool infiniteBombs) : Entity(scene, x, y)
, state(STATE_IDLE)
, flags(0)
, sheet(null)

, rect()
, width(16)
, height(32)
, velocity()
, acceleration(0, GRAVITY_CONSTANT*GRAVITY_DOWN)

, lookX(LOOK_DIR_X_RIGHT)
, lookY(LOOK_DIR_Y_NONE)
//, onGround(false)
//, lastGroundTouchY(0)
, lastGroundTouchY(y)

, jump(false)
, jumpFrame(0)
, jumpPercent(0)

, falling(false)

, walkingState(false)
, oldWalkingState(false)
, walkingFrame(0)
, walkingClock(4)

, score(0)
, lives(MAX_LIVES)
, health(MAX_HEALTH)
, hostages(0)
, alive(true)
, deadClock(TIME_DEAD)
, damaged(false)
, damagedClock(0.03)
, damagedFlicker(0)

, bombThrower(infiniteBombs)
, weaponHandler(this)

, sprite1(null)
, spriteIndex1(0)
, sprite2(null)
, spriteIndex2(0)
, spriteClock2()

, knifeSound(null)

, controlsEnabled(true)
{
	std::string sheetFileName;
	sheetFileName += "mslug/heroes/";
	sheetFileName += name;
	sheetFileName += "/";
	sheetFileName += name;
	sheetFileName += ".xml";
	sheet = SpriteSheetLoader::load(sheetFileName.c_str());
	knifeSound = res.findSound("Knife");
	
	setWeapon(WEAPON_PISTOL);
	gotoIdleState();
}
Hero::~Hero()
{
	delete sheet;
}
void Hero::update(double dt)
{
	bool oldOnGround = onGround();
	
	if(scene->isMissionCompleted())
	{
		if(state != STATE_WINNER && onGround())
		{
			win();
		}
	}
//	if(!isDead())
	if(!isDead() && !isWinner())
	{
		if(controlsEnabled && Keyboard::isPressed(KEY_SHOOT) && !Keyboard::isRepeated(KEY_SHOOT))
		{
			attack1();
		}
		else if(controlsEnabled && Keyboard::isPressed(KEY_BOMB) && !Keyboard::isRepeated(KEY_BOMB))
		{
			attack2();
		}
		else
		{
			int dx = 0;
			
			//
			// Intentar saltar
			//
			if(controlsEnabled && Keyboard::isDown(KEY_JUMP))
			{
				if(onGround())
				{
					doJump(dt);
				}
			}
			//
			// Intentar caminar
			// 1º: Si no se está agachando
			// 2º: Si no se está parando
			// 3º: Si no esta muriendo
			// 4º: Si no ganó la misión
			// 5º: Si no está agachado y disparando
			//
			if(!(state == STATE_CROUCH
					|| state == STATE_STANDUP
					|| state == STATE_DYING
					|| state == STATE_WINNER
					|| isCrouching() && isAttacking()))
			{
				if(controlsEnabled)
				{
					if(Keyboard::isDown(KEY_LEFT))
						dx -= 1;
					if(Keyboard::isDown(KEY_RIGHT))
						dx += 1;
				}
			}
			// ...
			doWalking(dt, dx);
			// ...
			if(controlsEnabled && Keyboard::isDown(KEY_UP))
			{
				lookUp();
			}
			else
			{
				if(lookY == LOOK_DIR_Y_UP)
				{
					lookAhead();
				}
			}
			if(controlsEnabled && Keyboard::isDown(KEY_DOWN))
			{
				if(onGround())
				{
					gotoCrouchState();
				}
				else
				{
					lookDown();
				}
			}
			else
			{
				if(lookY == LOOK_DIR_Y_DOWN)
				{
					lookAhead();
				}
				gotoStandupState();
			}
		}
		//
		// Control de armamento
		//
		if(weaponHandler.update(scene, dt, pos.x, getThoraxY(), lookX, lookY))
		{
			//
			// Volver a la pistola
			//
			if(weaponHandler.getAmmo() == 0)
			{
				setWeapon(WEAPON_PISTOL);
			}
		}
	}
	//
	// Control de física
	//
	if(state != STATE_DEAD && state != STATE_WINNER)
	{
		doPhysics(dt, oldOnGround);
	}
	
	//
	// Controlar parpadeo de daño
	//
	if(damaged)
	{
		if(damagedClock.update(dt))
		{
			damagedFlicker++;
			if(damagedFlicker >= 20)
			{
				damaged = false;
			}
		}
	}
	//
	// Actualizar animaciones
	//
	{
		//
		// Primera animación
		//
		updateFirstAnimation(dt);
		
		//
		// Segunda animación
		//
		switch(state)
		{
			case STATE_IDLE:
				updateSecondAnimationIdle(dt);
				break;
			case STATE_CROUCH:
				updateSecondAnimationCrouch(dt);
				break;
			case STATE_STANDUP:
				updateSecondAnimationStandup(dt);
				break;
			case STATE_ATTACK_BOMB:
				updateSecondAnimationAttackBomb(dt);
				break;
			case STATE_ATTACK_KNIFE:
				updateSecondAnimationAttackKnife(dt);
				break;
			case STATE_ATTACK_WEAPON:
				updateSecondAnimationAttackShoot(dt);
				break;
			case STATE_DYING:
				updateSecondAnimationAttackDying(dt);
				break;
			case STATE_DEAD:
				if(lives > 0 && deadClock.update(dt))
				{
					pos.y = 0;
					alive = true;
					damaged = false;
					damagedFlicker = 0;
					health = MAX_HEALTH;
					flags &= ~(FLAG_ON_GROUND);
					oldOnGround = false;
					lastGroundTouchY = 0;
					setWeapon(WEAPON_PISTOL);
					bombThrower.reset();
					gotoIdleState();
				}
				break;
			case STATE_WINNER:
				updateSecondAnimationAttackWinner(dt);
				break;
		}
	}
	rect = bounds();
}
void Hero::render(Graphics* gr)
{
	if(((damagedFlicker&1) != 0) || (state == STATE_DEAD))
	{
		return;
	}
	int posX = (int)pos.x;
	int posY = (int)pos.y;
	int hints = (lookX == LOOK_DIR_X_LEFT) ? Sprite::FLIP_X : 0;

	//
	// Renderizar primera animación
	//
	if(!isCrouching())
	{
		switch(state)
		{
			case STATE_IDLE:
			case STATE_ATTACK_BOMB:
			case STATE_ATTACK_KNIFE:
			case STATE_ATTACK_WEAPON:
				if(sprite1 != null)
					sprite1->render(gr, posX, posY, spriteIndex1, hints);
				// ...
				posY -= 16;
				if(onAir())
				{
					posY -= EIGHT;
				}
				break;
			default:
				break;
		}
	}
	//
	// Renderizar segunda animación
	//
	if(state == STATE_ATTACK_WEAPON)
	{
		weaponHandler.render(gr, posX, posY, hints);
	}
	else if(sprite2 != null)
	{
		sprite2->render(gr, posX, posY, spriteIndex2, hints);
	}
	//
	// ...
	//
	if(Debug::showHeroPos)
	{
		gr->drawRect((int)pos.x-2, (int)pos.y-2, 4, 4, Color(255, 0, 255));
	}
	if(Debug::showHeroRect)
	{
		gr->drawRect(bounds(), Color(0, 0, 0));
	}
}
Rectanglef Hero::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef Hero::bounds(double px, double py) const
{
	double rectX = 0;
	double rectY = 0;
	double rectWidth = 0;
	double rectHeight = 0;

	if(onGround())
	{
		if(isCrouching())
		{
			rectX = px - width/2;
			rectY = py - (height - EIGHT*2);
			rectWidth = width;
			rectHeight = height - EIGHT*2;
		}
		else
		{
			rectX = px - width/2;
			rectY = py - height;
			rectWidth = width;
			rectHeight = height;
		}
	}
	else
	{
		rectX = px - width/2;
		rectY = (py - (height + EIGHT));
		rectWidth = width;
		rectHeight = height + EIGHT;
	}
	return Rectanglef(rectX, rectY, rectWidth, rectHeight);
}
void Hero::collide(Entity* other)
{
}
Rectanglef Hero::collisionRect() const
{
	if(alive && !damaged && state != STATE_WINNER)
		return bounds();
	return Rectanglef();
}
void Hero::win()
{
	state = STATE_WINNER;
	sprite2 = cache.winner;
	spriteIndex2 = 0;
	spriteClock2.reset(TIME_WINNER);
	// ...
	velocity.x = 0;
}
void Hero::dead()
{
	if(state != STATE_DYING)
	{
		velocity.x = 0;
		lives--;
		health = 0;
		alive = false;
		hostages = 0;
		state = STATE_DYING;
		sprite2 = sheet->getSprite("dying");
		spriteIndex2 = 0;
		spriteClock2.reset(TIME_DYING);
	}
}
void Hero::hurt()
{
	if(alive && !damaged)
	{
		health--;
		damaged = true;
		damagedClock.reset();
		damagedFlicker = 0;

		if(health == 0)
		{
			dead();
		}
	}
}
bool Hero::isDead() const
{
	return (state == STATE_DYING || state == STATE_DEAD);
}
bool Hero::isAlive() const
{
	return alive;
}
bool Hero::isLoser() const
{
	return (state == STATE_DEAD && lives == 0);
}
bool Hero::isWinner() const
{
	return (state == STATE_WINNER);
}
int Hero::getScore() const
{
	return score;
}
void Hero::addScore(int s)
{
	score += s;
}
void Hero::addHostage()
{
	hostages++;
}
int Hero::getHostages() const
{
	return hostages;
}
int Hero::getLives() const
{
	return lives;
}
int Hero::getHealth() const
{
	return health;
}
int Hero::getBombs() const
{
	return bombThrower.getCount();
}
void Hero::addBombs(int bombs)
{
	bombThrower.addBombs(bombs);
}
int Hero::getAmmo() const
{
	return weaponHandler.getAmmo();
}
Weapon* Hero::getWeapon() const
{
	return weaponHandler.getWeapon();
}
void Hero::setWeapon(int weaponId)
{
	cache.reset(sheet, weaponHandler.setWeapon(sheet, weaponId));
	if(state == STATE_IDLE)
	{
		sprite2 = getIdleSprite(state);
		spriteIndex2 = 0;
	}
}
double Hero::getShotAngle() const
{
	return weaponHandler.getShotAngle();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void		Hero::attack1()
{
	if(state == STATE_IDLE || state == STATE_ATTACK_BOMB /*|| state == STATE_ATTACK_KNIFE*/ || state == STATE_ATTACK_WEAPON)
	{
		//
		// Intentar un ataque con cuchillo si hay entidades cerca
		//
		double knifeX = (double)(pos.x+lookX*width/2);
		double knifeY = (double)(pos.y-height/2);
		std::vector<Knifeable*> nearbyKnifeables = scene->getNearbyKnifeableEntities(knifeX, knifeY, KNIFE_RADIUS);
		
		if(!nearbyKnifeables.empty())
		{
			for(unsigned int i = 0; i < nearbyKnifeables.size(); i++)
			{
				nearbyKnifeables[i]->knifeHurt(KNIFE_DAMAGE);
			}
			//
			// Seleccionar una animación en modo aleatorio
			//
			state = STATE_ATTACK_KNIFE;
			int knifeAnimation = Random().nextInt(2);
			if(!isCrouching())
				sprite2 = cache.thoraxKnife[knifeAnimation];
			else
				sprite2 = cache.crouchedKnife[knifeAnimation];
			spriteIndex2 = 0;
			spriteClock2.reset(TIME_KNIFE);
			Mixer::playChannel(knifeSound);
		}
		else
		{
			//
			// Disparar
			//
			if(weaponHandler.trigger(scene, pos.x, getThoraxY(), lookX))
			{
				//
				// Establecer nuevo estado y animación
				//
				state = STATE_ATTACK_WEAPON;
				
				//
				// Volver a la pistola
				//
				if(weaponHandler.getAmmo() == 0)
				{
					setWeapon(WEAPON_PISTOL);
				}
			}
		}
	}
}
//
// Ataque secundario (Bomb)
//
void		Hero::attack2()
{
	if(state == STATE_IDLE || state == STATE_ATTACK_BOMB || state == STATE_ATTACK_KNIFE || state == STATE_ATTACK_WEAPON)
	{
		//
		// Lanzar bomba
		//
		if(!bombThrower.isEmpty())
		{
			//
			// Cancelar disparos
			//
			if(state == STATE_ATTACK_WEAPON)
			{
				weaponHandler.stop();
			}
			// ...
			double bombMaxH = 25;
			double bombPosX = pos.x+lookX*width;
			double bombPosY = rect.getMinY();
			double bombVelocityX = lookX*100.0;
			double bombVelocityY = GRAVITY_UP*Math::sqrt(2*GRAVITY_CONSTANT*bombMaxH);
			
			if(bombThrower.throwBomb(scene, bombPosX, bombPosY, bombVelocityX, bombVelocityY))
			{
				//
				// Establecer nuevo estado y animación
				//
				state = STATE_ATTACK_BOMB;
				// ...
				if(!isCrouching())
					sprite2 = cache.thoraxBomb;
				else
					sprite2 = cache.crouchedBomb;
				spriteIndex2 = 0;
				spriteClock2.reset(TIME_BOMB);
			}
		}
	}
}
Sprite*		Hero::getIdleSprite(STATE lastState)
{
	Sprite* spr = null;
	if(!isCrouching())
	{
		int shotAngle = (int)weaponHandler.getShotAngle();
		
		if(shotAngle == 0)								{	spr = cache.thoraxIdle0;	}
		else if(shotAngle > 0 && shotAngle < 30)		{	spr = cache.thoraxIdle30;	}
		else if(shotAngle >= 30 && shotAngle < 90)		{	spr = cache.thoraxIdle60;	}
		else if(shotAngle == 90)						{	spr = cache.thoraxIdle90;	}
		else if(shotAngle == -90)						{	spr = cache.thoraxIdleDown;	}
		else
		{
			printf("Ángulo no válido=%f", shotAngle);
		}
	}
	else
	{
		switch(lastState)
		{
			case STATE_ATTACK_BOMB:
			case STATE_ATTACK_KNIFE:
				spr = cache.crouchedIdleAttack2;
				break;
			case STATE_ATTACK_WEAPON:
				spr = cache.crouchedIdleAttack1;
				break;
			default:
				spr = cache.crouchedIdle;
				break;
		}
	}
	return spr;
}
void		Hero::doJump(double dt)
{
	if(state == STATE_IDLE || isAttacking())
	{
		jump = true;
		falling = false;
		flags &= ~(FLAG_ON_GROUND|FLAG_IS_CROUCHING);
		
		velocity.y = GRAVITY_UP*Math::sqrt(DISTANCE_JUMP*2*GRAVITY_CONSTANT);
	}
}
void		Hero::doWalking(double dt, double dx)
{
	oldWalkingState = walkingState;
	if(dx != 0)
	{
		walkingState = true;
		if(isCrouching())
			velocity.x = (dx*VELOCITY_WALK_CROUCHING);
		else
			velocity.x = (dx*VELOCITY_WALK_STANDINGUP);
		
	}
	else
	{
		walkingState = false;
		if(onGround())
			velocity.x = 0;
	}
}
void		Hero::doPhysics(double dt, bool oldOnGround)
{
	CollisionInfo ci = scene->moveEntity(
			this,
			dt,
			pos,
			velocity,
			acceleration,
			onGround(),
			MAP_TERRAIN_SOLID|MAP_TERRAIN_TOPDOWN);
	pos = scene->boundsInScene(pos);
	
	if(ci.flags & COLLISION_FLAG_BOTTOM)
	{
		jump = false;
		falling = false;
//TODO		onGround = true;
		flags |= FLAG_ON_GROUND;
		velocity.y = 0;
		if(!oldOnGround && !isDead())
		{
			gotoIdleState();
		}
		lastGroundTouchY = pos.y;
		
	}
	else
	{
		//
		// Comprobar caída
		//
		if((pos.y-lastGroundTouchY)>16)
		{
			falling = true;
//TODO			onGround = false;
			flags &= ~(FLAG_ON_GROUND);
		}
	}
//	if(ci.hasCollisionY())
	if(ci.flags & COLLISION_FLAG_BOTTOM)
	{
		velocity.y = 0;
	}
	if(onGround())
	{
		if(velocity.x < 0)
			lookX = LOOK_DIR_X_LEFT;
		else if(velocity.x > 0)
			lookX = LOOK_DIR_X_RIGHT;
	}
	else
	{
		jumpPercent = ((lastGroundTouchY-pos.y)/DISTANCE_JUMP)*100;
	}
}
void		Hero::gotoIdleState()
{
	STATE lastState = state;
	
	//
	// Establecer nuevo estado y animación
	//
	state = STATE_IDLE;
	sprite2 = getIdleSprite(lastState);
	spriteIndex2 = 0;
	if(!isCrouching())
	{
		spriteClock2.reset(TIME_IDLE_STANDING);
		walkingClock.reset(TIME_WALKING_STANDUP);
	}
	else
	{
		spriteClock2.reset(TIME_IDLE_CROUCHED);
		walkingClock.reset(TIME_WALKING_CROUCHED);
	}
}
void		Hero::gotoCrouchState()
{
	if(onGround() && !isCrouching())
	{
		flags |= FLAG_IS_CROUCHING;
		lookY = LOOK_DIR_Y_NONE;
		// ...
		state = STATE_CROUCH;
		// ...
		sprite2 = cache.crouch;
		spriteIndex2 = 0;
		spriteClock2.reset(TIME_CROUCH);
		weaponHandler.setShotAngle(0);
	}
}
void		Hero::gotoStandupState()
{
	if(isCrouching())
	{
		flags &= ~FLAG_IS_CROUCHING;
		// ...
		state = STATE_STANDUP;
		// ...
		sprite2 = cache.standup;
		spriteIndex2 = 0;
		spriteClock2.reset(TIME_STANDUP);
	}
}
void		Hero::updateFirstAnimation(double dt)
{
	if(!isCrouching())
	{
		if(onAir())
		{
			if(jumpPercent <= 30)							jumpFrame = 0;
			else if(jumpPercent > 30 && jumpPercent <= 50)	jumpFrame = 1;
			else if(jumpPercent > 50 && jumpPercent <= 70)	jumpFrame = 2;
			else if(jumpPercent > 70 && jumpPercent <= 80)	jumpFrame = 3;
			else if(jumpPercent > 80 && jumpPercent <= 90)	jumpFrame = 4;
			else if(jumpPercent > 90)						jumpFrame = 5;
			
			// ...
			sprite1 = cache.legsJump;
			spriteIndex1 = jumpFrame;
		}
		else if(walkingState)
		{
			if(!oldWalkingState)
			{
				walkingFrame = 0;
			}
			else if(walkingClock.update(dt))
			{
				walkingFrame++;
				if(walkingFrame >= cache.legsWalk->count())
					walkingFrame = 4;
			}
			sprite1 = cache.legsWalk;
			spriteIndex1 = walkingFrame;
		}
		else
		{
			sprite1 = cache.legsIdle;
			spriteIndex1 = 0;
		}
	}
	else
	{
		sprite1 = null;
	}
}
void		Hero::updateSecondAnimationIdle(double dt)
{
	if(isCrouching())
	{
		if(walkingState)
		{
			if(!oldWalkingState)
			{
				walkingFrame = 0;
			}
			else if(walkingClock.update(dt))
			{
				walkingFrame++;
				if(walkingFrame >= cache.crouchedWalk->count())
					walkingFrame = 0;
			}
			sprite2 = cache.crouchedWalk;
			spriteIndex2 = walkingFrame;
		}
		else
		{
			if(oldWalkingState)
			{
				sprite2 = getIdleSprite(state);
				spriteIndex2 = 0;
			}
			else if(spriteClock2.update(dt))
			{
				if(++spriteIndex2 >= sprite2->count())
				{
					spriteIndex2 = 0;
				}
			}
		}
	}
	else if(onAir() && lookY == LOOK_DIR_Y_NONE)
	{
		//
		// Calcular frame de salto (ó caida)
		//
		if(velocity.y < 0)
		{
			if(jumpPercent <= 30)							jumpFrame = 0;
			else if(jumpPercent > 30 && jumpPercent <= 50)	jumpFrame = 1;
			else if(jumpPercent > 50 && jumpPercent <= 70)	jumpFrame = 2;
			else if(jumpPercent > 70 && jumpPercent <= 80)	jumpFrame = 3;
			else if(jumpPercent > 80 && jumpPercent <= 90)	jumpFrame = 4;
			else if(jumpPercent > 90)						jumpFrame = 5;
			
		}
		else
		{
			if(jumpPercent <= 80)							jumpFrame = 3;
			if(jumpPercent <= 80)							jumpFrame = 3;
			else if(jumpPercent > 80 && jumpPercent <= 90)	jumpFrame = 4;
			else if(jumpPercent > 90)						jumpFrame = 5;
		}
		jumpFrame = 5-jumpFrame;
		sprite2 = cache.thoraxJump;
		spriteIndex2 = jumpFrame;
	}
	else
	{
		int currentAngle = (int)weaponHandler.getShotAngle();
		int previousAngle = (int)weaponHandler.getPreviousShotAngle();
		
		if(currentAngle != previousAngle)
		{
			sprite2 = getIdleSprite(state);
			spriteIndex2 = 0;
		}
		else if(sprite2 != null && sprite2->count() > 1)
		{
			if(spriteClock2.update(dt))
			{
				if(++spriteIndex2 >= sprite2->count())
				{
					spriteIndex2 = 0;
				}
			}
		}
	}
}
void		Hero::updateSecondAnimationCrouch(double dt)
{
	if(spriteClock2.update(dt))
	{
		if(++spriteIndex2 >= sprite2->count())
		{
			gotoIdleState();
		}
	}
}
void		Hero::updateSecondAnimationStandup(double dt)
{
	if(spriteClock2.update(dt))
	{
		if(++spriteIndex2 >= sprite2->count())
		{
			gotoIdleState();
		}
	}
}
void		Hero::updateSecondAnimationAttackBomb(double dt)
{
	if(spriteClock2.update(dt))
	{
		if(++spriteIndex2 >= sprite2->count())
		{
			gotoIdleState();
		}
	}
}
void		Hero::updateSecondAnimationAttackShoot(double dt)
{
	//
	// Si terminó de disparar, ir a estado IDLE
	//
	if(!weaponHandler.isShooting())
	{
		gotoIdleState();
	}
}
void		Hero::updateSecondAnimationAttackKnife(double dt)
{
	if(spriteClock2.update(dt))
	{
		if(++spriteIndex2 >= sprite2->count())
		{
			gotoIdleState();
		}
	}
}
void		Hero::updateSecondAnimationAttackDying(double dt)
{
	if(spriteClock2.update(dt))
	{
		if(++spriteIndex2 >= sprite2->count())
		{
			spriteIndex2--;
			if(onGround())
			{
				state = STATE_DEAD;
			}
		}
	}
}
void		Hero::updateSecondAnimationAttackWinner(double dt)
{
	if(spriteClock2.update(dt))
	{
		if(++spriteIndex2 >= sprite2->count())
		{
			spriteIndex2 = 0;
		}
	}
}