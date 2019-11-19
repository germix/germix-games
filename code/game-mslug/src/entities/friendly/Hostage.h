////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Hostage | Rehén
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Hostage_h___
#define ___Hostage_h___
#include <src/scene/Entity.h>
#include <src/___/Knifeable.h>
#include <src/___/HurtableRect.h>
#include <src/___/Collisionable.h>

#include <string>

#include <gamelib/TimeClock.h>

class Sprite;
class SpriteSheet;

class Hostage : public Entity, public Knifeable, public HurtableRect, public Collisionable
{
	enum STATE
	{
		STATE_CAPTURED,			// Capturado
		STATE_UNTYING,			// Desatándose
		STATE_RELEASED,			// Liberado
		STATE_GIVING_BONUS,		// Dando bonus
		STATE_SALUTE,			// Saludar
		STATE_FLEEING,			// Huyendo
	};
	STATE				state;
	Vector2f			vel;
	Vector2f			accel;
	int					lookX;
	bool				onGround;
	
	SpriteSheet*		sheet;
	Sprite*				sprite;
	int					spriteFrame;
	TimeClock			spriteClock;
	
	int					walkTo;
	
	bool				active;
	const std::string	droppableBonus;
public:
	Hostage(Scene* scene, double x, double y, const char* bonus);
	~Hostage();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;

	void knifeHurt(int damage);
	bool isKnifeHurtable() const;
	
	void hurt(int damage);
	bool isHurtable() const;
	Rectanglef hurtableRect() const;
	
	void collide(Entity* other);
	Rectanglef collisionRect() const;
private:
	void release();
};

#endif
