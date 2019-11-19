////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Masknell | Helicóptero Masknell
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Masknell_h___
#define ___Masknell_h___
#include <src/entities/enemies/Enemy.h>
#include <src/___/HurtableRect.h>

#include <gamelib/TimeClock.h>

class Sprite;
class Route;
struct RouteCoordinate;

class Masknell : public Enemy, public HurtableRect
{
protected:
	Route*			route;
	Vector2f		basePos;
	int				health;
	double			traveled;
	Sprite*			sprite;
	int				spriteFrame;
	unsigned int	spriteHints;
	
	friend class MasknellFleet;

	Sprite*			blades[6];
	int				bladesIndex;
	TimeClock		bladesClock;
public:
	Masknell(Scene* scene, double x, double y, Route* r);
	~Masknell();
public:
	void render(Graphics* gr);

	void hurt(int damage);
	bool isHurtable() const;
	Rectanglef hurtableRect() const;
private:
	void destroy();
protected:
	void update(double dt, RouteCoordinate* rc);
};

#endif
