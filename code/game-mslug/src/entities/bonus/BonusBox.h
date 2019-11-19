////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusBox | Caja contenedora de bonus
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___BonusBox_h___
#define ___BonusBox_h___
#include <src/scene/Entity.h>
#include <src/___/Knifeable.h>
#include <src/___/HurtableRect.h>

#include <string>

#include <gamelib/TimeClock.h>

class Sprite;

class BonusBox: public Entity, public Knifeable, public HurtableRect
{
	Vector2f			vel;
	Vector2f			accel;
	bool				onGround;
	Sprite*				sprite;
	int					spriteFrame;
	TimeClock			spriteClock;
	bool				destroyed;
	const std::string	droppableBonus;
public:
	BonusBox(Scene* scene, double x, double y, const char* bonus);
	~BonusBox();
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
private:
	void destroyMe();
};

#endif

