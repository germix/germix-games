////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Entity
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Entity_h___
#define ___Entity_h___
#include <mach/Vector2f.h>
#include <mach/Rectanglef.h>

class Scene;
class Graphics;
class Rectangle;

class Entity
{
protected:
	Vector2f		pos;
	Scene*			scene;
	bool			removable;
public:
	Entity(Scene* s, double x, double y) : pos(x, y), scene(s), removable(false)
	{
	}
	virtual ~Entity()
	{
	}
public:
	bool					isRemovable() const { return removable; }
	virtual Vector2f		position() const { return pos; }
	virtual Rectanglef		rect() const = 0;
	virtual void			update(double dt) = 0;
	virtual void			render(Graphics* gr) = 0;
};

#endif
