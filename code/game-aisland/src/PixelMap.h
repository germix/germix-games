////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PixelMap
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PixelMap_h___
#define ___PixelMap_h___
#include <mach/Vector2f.h>
#include <mach/Rectanglef.h>

class Image;
class Texture;
class Entity;
class Graphics;
class TexturedTileMap;

#define MAP_TERRAIN_SOLID		0x01
#define MAP_TERRAIN_TOPDOWN		0x02

#define COLLISION_FLAG_LEFT		0x01
#define COLLISION_FLAG_RIGHT	0x02
#define COLLISION_FLAG_TOP		0x04
#define COLLISION_FLAG_BOTTOM	0x08

class PixelMap
{
	Image*				testImage;
	Rectanglef			testRectangle;
	Texture*			testTexture;
	TexturedTileMap*	testTexturedTileMap;
public:
	PixelMap(Image* img);
	PixelMap(const char* fname);
	~PixelMap();
public:
	int getWidth() const { return (int)testRectangle.getWidth(); }
	int getHeight() const { return (int)testRectangle.getHeight(); }

	unsigned int checkCollision(
							Entity* entity,
							Vector2f& newPosition,
							Vector2f& newVelocity,
							const Vector2f& oldPosition,
							const Vector2f& oldVelocity,
							unsigned int terrainType,
							unsigned int collisionFlags) const;
	
	void render(Graphics* gr, int sx1, int sy1, int sx2, int sy2, int dx1, int dy1, int dx2, int dy2);
};

#endif
