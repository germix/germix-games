////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Hero | Héroe
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Hero_h___
#define ___Hero_h___
#include <src/Entity.h>
#include <src/HeroInfo.h>

#include <gamelib/TimeClock.h>

class Sound;
class Sprite;
class SpriteSheet;

class Platform;
class Honeygirl;

class Hero : public Entity
{
public:
	enum
	{
		WEAPON_NONE = 0,
		WEAPON_AX = 1,
		WEAPON_FIREBALL = 2,
	};
private:
	enum STATE
	{
		STATE_IDLE,
		STATE_WALK,
//		STATE_JUMP,
		STATE_DYING,
		STATE_STUMBLE,
		STATE_DEAD,
	};

	STATE						state;
	
	Vector2f					velocity;
	
	HeroInfo&					info;
	
	SpriteSheet*				sheet;
	Sprite*						sprite;
	int							spriteDir;
	int							spriteIndex;
	TimeClock					spriteClock;

	bool						onGround;
	int							collisionFlags;
	
	bool						power;
	bool						skate;
	bool						brakeSkate;

	//
	// Ataque
	//
	bool						isAttacking;
	TimeClock					attackingClock;
	
	Platform*					platform;
	Honeygirl*					honeygirl;

	Sound*						deadSound;

	bool						winner;

	static const double			TIME_IDLE;
	static const double			TIME_WALK;
	static const double			TIME_WALK_POWER;
	static const double			VELOCITY_WALK;
	static const double			VELOCITY_WALK_POWER_ADDITION;
	static const double			VELOCITY_SKATE;
	static const double			VELOCITY_SKATE_POWER_REDUCTION;
	static const int			DISTANCE_JUMP;
	static const int			DISTANCE_JUMP_POWERED;
	static const int			DISTANCE_SUPERJUMP;
	static const int			DISTANCE_SUPERJUMP_POWERED;
public:
	Hero(Scene* s, double x, double y, HeroInfo& i);
	~Hero();
public:
	virtual void update(double dt);
	virtual void render(Graphics* gr);
	virtual Rectanglef bounds() const;
	virtual Rectanglef bounds(double px, double py) const;
	virtual void collides(Entity* e);
	virtual Rectanglef getCollisionRectangle() const;
public:
	void dead();
	bool isDead() const;
	void burn();
	void freeze();
	void stumble();
	void stumble(bool decreaseHealth);
	void setPot();
	void addLife();
	int getWeapon() const { return info.weapon; }
	void setWeapon(int w);
	bool hasSkate() const;
	void setSkate();
	void releaseSkate();
	void releaseSkate(const Vector2f& p);
	void addScore(int score, int health);
	void setFullHealth();
	Vector2f getVelocity() const;
	bool hasHoneygirl() const;
	void setHoneygirl(Honeygirl* hg);
	void releaseHoneygirl();
	void respawn(const Vector2f& respawnPosition);
	void setPositionY(double y);
	void translatePositionX(double dx);
	const HeroInfo& getInfo() const
	{
		return info;
	}
	int decreaseHealth()
	{
		return --info.health;
	}
	void superJump();
	bool isOnGround() const
	{
		return onGround;
	}
	void win();
	bool isWinner() const
	{
		return winner;
	}
private:
	void motion(double dt);
};

#endif
