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
class EntityParameters;

class Entity
{
protected:
	Vector2f		pos;
	Scene*			scene;
	bool			removable;
public:
	Entity(Scene* s, double x, double y);
	~Entity();
public:
	virtual void update(double dt) = 0;
	virtual void render(Graphics* gr) = 0;
	virtual Rectanglef bounds() const { return Rectanglef(); };
	virtual Rectanglef bounds(double px, double py) const { return Rectanglef(); };
	virtual void collides(Entity* e) {};
	
	bool isRemovable() const
	{
		return removable;
	}
	Vector2f getPosition() const
	{
		return pos;
	}
	virtual Rectanglef getCollisionRectangle() const { return bounds(); }
};

#endif
