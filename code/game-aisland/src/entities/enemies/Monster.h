////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Monster
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Monster_h___
#define ___Monster_h___
#include <src/entities/Enemy.h>

#include <gamelib/TimeClock.h>

class Sprite;
class SpriteSheet;

class Monster : public Enemy
{
	enum STATE
	{
		STATE_WALK,
		STATE_ATTACK,
		STATE_FALLING_HEAD,
		STATE_GO_OUT,
	};
	int				type;
	STATE			state;
	bool			alive;
	int				health;
	SpriteSheet*	sheet;
	Sprite*			bodySprite;
	int				bodySpriteIndex;
	Sprite*			headSprite;
	int				headSpriteIndex;
	Sprite*			bulletSprite;
	int				bulletSpriteIndex;

	int				startX;
	int				walkDir;
	
	TimeClock		walkClock;
	TimeClock		attackClock;
	TimeClock		bulletClock;
	TimeClock		nextAttackClock;

	Vector2f		headPosition;
	Vector2f		headVelocity;

	TimeClock		headDamagedClock;
public:
	Monster(Scene* s, double x, double y, int type);
	~Monster();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	Rectanglef getCollisionRectangle() const;
private:
	Rectanglef headRect() const;
};

#endif
