////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Entity
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Entity_h___
#define ___Entity_h___
#include <mach/Rectangle.h>

class Map;
class Scene;

class Graphics;

class Entity
{
protected:
	Map*	map;
	Scene*	scene;
	int		x;
	int		y;
	int		width;
	int		height;
	bool	removable;
public:
	Entity(Map* m, Scene* s, int x, int y, int w = 16, int h = 16);
	~Entity();
public:
	virtual void update(double dt) = 0;
	virtual void render(Graphics* gr) = 0;
	
	virtual void collides(Entity* other) {}
	
	virtual Rectangle getCollisionRectangle() const
	{
		return !removable ? Rectangle(x,y,width,height) : Rectangle();
	}

	int getX() const { return x; }
	int getY() const { return y; }
	bool isRemovable() const { return removable; }
};

#endif
