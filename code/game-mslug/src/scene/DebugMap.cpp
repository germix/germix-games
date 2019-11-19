////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugMap
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/scene/DebugMap.h>
#include <src/Config.h>
#include <src/scene/Entity.h>
#include <src/___/CollisionInfo.h>

#include <mach/Color.h>
#include <mach/Graphics.h>

Vector2f DebugMap::getSuggestedSceneScroll(Entity* entity) const
{
	if(entity)
	{
		Vector2f pos = entity->getPosition();
		int      minX = 0;
		int      maxX = width;
		double   scrollX = pos.x - SCREEN_WIDTH/2;
		
		//
		// Calcular desplazamiento en X
		//
		if(scrollX < minX)
			scrollX = minX;
		else if(scrollX >= maxX-SCREEN_WIDTH)
			scrollX = maxX-SCREEN_WIDTH-1;
		
		return Vector2f(scrollX, 0);
	}
	return  Vector2f();
}
void DebugMap::renderBackground(Graphics* gr, int sx, int sy) const
{
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(0, 162, 232));
	gr->fillRect(0, SCREEN_HEIGHT-DEBUG_GROUND_HEIGHT, SCREEN_WIDTH, DEBUG_GROUND_HEIGHT, Color(34, 177, 76));
}
void DebugMap::renderForeground(Graphics* gr, int sx, int sy) const
{
}
unsigned int DebugMap::checkCollision(
							Entity* entity,
							Vector2f& newPosition,
							Vector2f& newVelocity,
							const Vector2f& oldPosition,
							const Vector2f& oldVelocity,
							unsigned int terrainType) const
{
	if(newPosition.y >= SCREEN_HEIGHT-DEBUG_GROUND_HEIGHT)
	{
		newVelocity.y = 0;
		newPosition.y = SCREEN_HEIGHT-DEBUG_GROUND_HEIGHT;
		
		return COLLISION_FLAG_BOTTOM;
	}
	return 0;
}
