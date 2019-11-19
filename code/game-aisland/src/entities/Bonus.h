////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_h___
#define ___Bonus_h___
#include <src/Entity.h>

class Hero;
class Texture;

class Bonus : public Entity
{
	int			dx;
	int			dy;
	Texture*	texture;
public:
	Bonus(Scene* s, double x, double y, int dx, int dy, Texture* tex);
	~Bonus();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef bounds() const { return bounds(pos.x, pos.y); }
	Rectanglef bounds(double px, double py) const;
protected:
	virtual void activated(Hero* h) = 0;
};

#endif
