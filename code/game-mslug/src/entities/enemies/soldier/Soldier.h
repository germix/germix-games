////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Soldier | Soldado
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Soldier_h___
#define ___Soldier_h___
#include <src/entities/enemies/Enemy.h>
#include <gamelib/TimeClock.h>
#include <src/___/Knifeable.h>
#include <src/___/Hurtable.h>
#include <src/___/HurtableRect.h>

class Sprite;
class SpriteSheet;

class Soldier : public Enemy, public Knifeable, public HurtableRect
{
	enum STATE
	{
		STATE_NONE,
		STATE_IDLE,
		STATE_WALK_BOMB,			// Caminar para tirar bomba
		STATE_THROW_BOMB,			// Tirar bomba
		STATE_ATTACK_SHOOT,
		STATE_DYING,
		STATE_FALLING,
		STATE_LAUGH,
	};
	STATE				state;
	SpriteSheet*		sheet;
	Sprite*				sprite;
	int					spriteFrame;
//	unsigned int		spriteHints;
	TimeClock			spriteClock;
	
	Vector2f			vel;
	Vector2f			accel;
	bool				onGround;
	int					lastGroundTouchY;
	
	int					lookX;
	
	//
	// Una vez generado el evento del 'actionTimer' se determinará la acción que se llevará a cabo
	//
	bool				activated;
	TimeClock			nextActionTimer;
public:
	Soldier(Scene* scene, double x, double y);
	~Soldier();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double x, double y) const;
public:
	void knifeHurt(int damage);
	bool isKnifeHurtable() const;

	void hurt(int damage);
	bool isHurtable() const;
	Rectanglef hurtableRect() const;
private:
	void die();
	void idle();
	void shoot();
	void walkBomb();
	void throwBomb();
	bool isAlive() const;
};

#endif
