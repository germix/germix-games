////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Egg
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Egg_h___
#define ___Egg_h___
#include <src/Entity.h>

#include <mach/String.h>

#include <gamelib/TimeClock.h>

class Sprite;
class SpriteSheet;

class Egg : public Entity
{
	static const char* BONUS_AX;
	static const char* BONUS_FIREBALL;
	static const char* BONUS_MILK;
	static const char* BONUS_SKATE;
	static const char* BONUS_FLOWER;
	static const char* BONUS_EGGPLANT;
	static const char* BONUS_HONEYGIRL;

	SpriteSheet*		sheet;
	Sprite*				sprite;

	int					state;	// 0=Normal, 1=Quebrado
	
	String				bonus;
	bool				kicked;
	Vector2f			velocity;
	Vector2f			acceleration;
	
	bool				ready;
	TimeClock			readyClock;
public:
	Egg(Scene* s, double x, double y, const String& bonus);
	~Egg();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	void collides(Entity* e);
	Rectanglef getCollisionRectangle() const;
public:
	void kick(double x);
private:
	void dropBonus();
};

#endif
