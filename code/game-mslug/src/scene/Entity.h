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

class Entity
{
protected:
	Scene*		scene;
	bool		removable;
	Vector2f	pos;
public:
	Entity(Scene* scene, double x, double y);
	virtual ~Entity();
public:
	virtual void		update(double dt);
	virtual void		render(Graphics* gr);
	virtual Rectanglef	bounds() const { return Rectanglef(); }
	virtual Rectanglef	bounds(double px, double py) const { return Rectanglef(); }
	bool				isRemovable() const { return removable; }
	Vector2f			getPosition() const { return pos; }
};

#endif
