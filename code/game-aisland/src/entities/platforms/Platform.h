////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Platform
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Platform_h___
#define ___Platform_h___
#include <src/Entity.h>

class Hero;
class Texture;

class Platform : public Entity
{
protected:
	Hero*			hero;
	const int		width;
	const int		height;
	Texture*		texture;
	const double	velocity;
public:
	Platform(Scene* s, double x, double y, const EntityParameters& params, double vel);
	~Platform();
public:
	virtual void render(Graphics* gr);
	virtual Rectanglef bounds() const 
	{
		return bounds(pos.x, pos.y);
	}
	virtual Rectanglef bounds(double px, double py) const
	{
		return Rectanglef(px, py, width, height);
	}
	virtual Rectanglef getCollisionRectangle() const
	{
		return bounds();
	}
public:
	virtual void setHero(Hero* h)
	{
		hero = h;
	}
	void releaseHero()
	{
		hero = null;
	}
};

#endif

