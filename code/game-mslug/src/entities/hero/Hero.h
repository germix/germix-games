////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Hero | Héroe
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Hero_h___
#define ___Hero_h___
#include <src/scene/Entity.h>
#include <src/entities/hero/BombThrower.h>
#include <src/entities/hero/WeaponHandler.h>
#include <src/entities/hero/HeroSpriteCache.h>
#include <src/___/Collisionable.h>

#include <gamelib/TimeClock.h>

class Sound;
class Sprite;
class SpriteSheet;

class Hero : public Entity, public Collisionable
{
	enum FLAG
	{
		FLAG_ON_GROUND		= 0x0001,				// Indica si está tocando el suelo
		FLAG_IS_CROUCHING	= 0x0002,				// Indica si está agachado
	};
	enum STATE
	{
		STATE_IDLE,
		STATE_CROUCH,
		STATE_STANDUP,
		STATE_ATTACK_BOMB,
		STATE_ATTACK_KNIFE,
		STATE_ATTACK_WEAPON,
		STATE_DYING,
		STATE_DEAD,
		STATE_WINNER,			// Cuando completa el escenario
	};
public:
	enum
	{
		MAX_LIVES			= 3,
		MAX_HEALTH			= 3,
		
		//
		// Constantes de dirección de mirada Y
		//
		LOOK_DIR_Y_UP		= +1,
		LOOK_DIR_Y_NONE		= 0,
		LOOK_DIR_Y_DOWN		= -1,

		//
		// Constantes de dirección de mirada X
		//
		LOOK_DIR_X_LEFT		= -1,
//		LOOK_DIR_X_NONE		= 0,
		LOOK_DIR_X_RIGHT	= +1,
		
		
		EIGHT				= 8,
		
		KNIFE_RADIUS		= 20,
		KNIFE_DAMAGE		= 1,
	};
private:
//--------------------------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------------------------
	STATE					state;
	unsigned int			flags;
	SpriteSheet*			sheet;
	
	Rectanglef				rect;
	int						width;
	int						height;
	Vector2f				velocity;
	Vector2f				acceleration;
	
	int						lookX;
	int						lookY;
//	bool					onGround;				// Indica si está tocando el suelo
	double					lastGroundTouchY;		// Última posición 'Y' en la que se toca el suelo	
//	bool					isCrouching;			// ¿Está en cuclillas?
	
	//
	// Idle
	//

	//
	// Jump
	//
	bool					jump;
	int						jumpFrame;
	double					jumpPercent;

	//
	// Falling
	//
	bool					falling;
	
	//
	// Caminata
	//
	bool					walkingState;
	bool					oldWalkingState;
	int						walkingFrame;
	TimeClock				walkingClock;
	
	//
	// Puntaje/Salud/Vidas
	//
	int						score;
	int						lives;
	int						health;
	int						hostages;			// Contador de rehenes
	bool					alive;
	TimeClock				deadClock;
	bool					damaged;
	TimeClock				damagedClock;
	int						damagedFlicker;

	//
	// Armas y bombas
	//
	BombThrower				bombThrower;
	WeaponHandler			weaponHandler;
	
	//
	// Sprites
	//
	HeroSpriteCache			cache;
	Sprite*					sprite1;
	int						spriteIndex1;

	Sprite*					sprite2;
	int						spriteIndex2;
	TimeClock				spriteClock2;
	
	//
	// ...
	//
	Sound*					knifeSound;

	bool					controlsEnabled;
public:
	Hero(Scene* scene, double x, double y, const char* name = "marco", bool infiniteBombs = false);
	~Hero();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	
	void collide(Entity* other);
	Rectanglef collisionRect() const;
public:
	int			getLookX() const { return lookX; }
	int			getLookY() const { return lookY; }
	Vector2f	getVelocity() const { return velocity; }
//	bool		onAir() const { return (flags & (FLAG_IS_JUMPING|FLAG_IS_FALLING) != 0); 
	bool		onAir() const { return (flags & FLAG_ON_GROUND) == 0; }
	bool		onGround() const { return (flags & FLAG_ON_GROUND) != 0; }

//	bool		isJumping() const;
//	bool		isFalling() const;
//	bool		isWalking() const;
	
	//
	// Comprobar si está agachado
	//
	bool		isCrouching() const { return (flags & FLAG_IS_CROUCHING) != 0; }
	//
	// Comprobar si está atacando (Weapon/Knife/Bomb)
	//
	bool		isAttacking() const
	{
		return (state == STATE_ATTACK_WEAPON || state == STATE_ATTACK_KNIFE || state == STATE_ATTACK_BOMB);
	}
public:
	void win();
	void dead();
	void hurt();
	bool isDead() const;
	bool isAlive() const;
	bool isLoser() const;
	bool isWinner() const;
	int getScore() const;
	void addScore(int score);
	void addHostage();
	int getHostages() const;
	int getLives() const;
	int getHealth() const;
	int getBombs() const;
	void addBombs(int bombs);
	int getAmmo() const;
	Weapon* getWeapon() const;
	void setWeapon(int weaponId);
	double getShotAngle() const;

	void enableControls() { controlsEnabled = true; }
	void disableControls() { controlsEnabled = false; }
private:
	void lookUp()
	{
		if(lookY != LOOK_DIR_Y_UP)
		{
			lookY = LOOK_DIR_Y_UP;
		}
	}
	void lookDown()
	{
		if(lookY != LOOK_DIR_Y_DOWN)
		{
			lookY = LOOK_DIR_Y_DOWN;
		}
	}
	void lookAhead()
	{
		if(lookY != LOOK_DIR_Y_NONE)
		{
			lookY = LOOK_DIR_Y_NONE;
		}
	}
	//
	// Ataque primario (Weapon/Knife)
	//
	void		attack1();
	//
	// Ataque secundario (Bomb)
	//
	void		attack2();
	double		getThoraxY()
	{
		double y = pos.y;
		if(!isCrouching())
		{
			y -= 16;
			if(onAir())
			{
				y -= EIGHT;
			}
		}
		return y;
	}
	Sprite*		getIdleSprite(STATE lastState);
	void		doJump(double dt);
	void		doWalking(double dt, double dx);
	void		doPhysics(double dt, bool oldOnGround);
	void		gotoIdleState();
	void		gotoCrouchState();
	void		gotoStandupState();
	void		updateFirstAnimation(double dt);
	void		updateSecondAnimationIdle(double dt);
	void		updateSecondAnimationCrouch(double dt);
	void		updateSecondAnimationStandup(double dt);
	void		updateSecondAnimationAttackBomb(double dt);
	void		updateSecondAnimationAttackShoot(double dt);
	void		updateSecondAnimationAttackKnife(double dt);
	void		updateSecondAnimationAttackDying(double dt);
	void		updateSecondAnimationAttackWinner(double dt);
};

#endif
