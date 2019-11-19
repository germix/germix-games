////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Entity
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Entity_h___
#define ___Entity_h___
#include <src/Direction.h>

#include <mach/Point.h>
#include <mach/Rectangle.h>

class Scene;
class Graphics;

class Entity
{
protected:
	int x;
	int y;
	Scene* scene;
public:
	Entity(Scene* scene, int x, int y)
	{
		this->x = x;
		this->y = y;
		this->scene = scene;
	}
	virtual ~Entity()
	{
	}
public:
	Point pos() const
	{
		return Point(x,y);
	}
	Rectangle rect8() const
	{
		return Rectangle(x, y, 8, 8);
	}
	Rectangle rect16() const
	{
		return Rectangle(x-4, y-4, 16, 16);
	}
	void setPosition(const Point& p)
	{
		this->x = p.x;
		this->y = p.y;
	}
	virtual void update(double dt) = 0;
	virtual void render(Graphics* gr) = 0;
protected:
	bool move(DIRECTION dir, unsigned int mask)
	{
		return move(dir, mask, rect8());
	}
	bool move(DIRECTION dir, unsigned int mask, const Rectangle& rect);
};

#endif
