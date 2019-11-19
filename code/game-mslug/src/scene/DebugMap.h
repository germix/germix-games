////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugMap
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___DebugMap_h___
#define ___DebugMap_h___
#include <src/scene/Map.h>

class CollisionInfo;

class DebugMap : public Map
{
	int width;
	int height;
public:
	DebugMap(int w, int h) : width(w), height(h)
	{
	}
	~DebugMap()
	{
	}
public:
	virtual int getWidth() const { return width; }
	virtual int getHeight() const { return height; }
	virtual Vector2f getSuggestedSceneScroll(Entity* entity) const;
	virtual void update(Scene* scene, double dt) {}
	virtual void renderBackground(Graphics* gr, int sx, int sy) const;
	virtual void renderForeground(Graphics* gr, int sx, int sy) const;

	virtual unsigned int checkCollision(
								Entity* entity,
								Vector2f& newPosition,
								Vector2f& newVelocity,
								const Vector2f& oldPosition,
								const Vector2f& oldVelocity,
								unsigned int terrainType) const;
};

#endif
