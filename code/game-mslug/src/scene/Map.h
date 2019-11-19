////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Map
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Map_h___
#define ___Map_h___
#include <mach/Vector2f.h>

class Scene;
class Entity;
class Graphics;

class Map
{
public:
	Map();
	virtual ~Map();
public:
	virtual int getX() const { return 0; }
	virtual int getY() const { return 0; }
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
	virtual Vector2f getSuggestedSceneScroll(Entity* entity) const = 0;
	virtual void update(Scene* scene, double dt) = 0;
	virtual void renderBackground(Graphics* gr, int sx, int sy) const = 0;
	virtual void renderForeground(Graphics* gr, int sx, int sy) const = 0;

	virtual unsigned int checkCollision(
								Entity* entity,
								Vector2f& newPosition,
								Vector2f& newVelocity,
								const Vector2f& oldPosition,
								const Vector2f& oldVelocity,
								unsigned int terrainType) const = 0;
};

#endif

