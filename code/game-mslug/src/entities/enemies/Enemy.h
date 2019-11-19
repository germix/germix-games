////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Enemy | Enemigo
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Enemy_h___
#define ___Enemy_h___
#include <src/scene/Entity.h>

class Enemy : public Entity
{
protected:
	bool destroyed;
public:
	Enemy(Scene* scene, double x, double y) : Entity(scene, x, y), destroyed(false)
	{
	}
	~Enemy()
	{
	}
public:
	bool isDestroyed() const { return destroyed; }
};

#endif
