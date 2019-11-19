////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PixelMap
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/PixelMap.h>
#include <src/Config.h>
#include <src/Entity.h>

#include <string>

#include <mach/Math.h>
#include <mach/Image.h>
#include <mach/ImageLoader.h>
#include <mach/Texture.h>
#include <mach/Graphics.h>
#include <src/TexturedTileMap.h>

static const Color COLOR_COLLISION_FULL;				// Colisión total
static const Color COLOR_COLLISION_TOPDOWN(255,0,0);	// Colosión desde arriba hacia abajo

static bool checkIntersection(Image* image, const Rectanglef& testRectangle, const Rectanglef& spriteRectangle, Rectanglef& pixelIntersection, const Color& testColor)
{
	int dx1 = 0;
	int dy1 = 0;
	/*
	int dx2 = 0;
	int dy2 = 0;
	*/
	Rectanglef r1 = testRectangle;
	Rectanglef r2 = spriteRectangle;
	Rectanglef ri = r1.intersected(r2);

	if(!ri.isEmpty())
	{
		int minX = (int)ri.getWidth();
		int minY = (int)ri.getHeight();
		int maxX = 0;
		int maxY = 0;
		
		if(r2.getMinY() > r1.getMinY())
			dy1 = (int)(r2.getMinY() - r1.getMinY());
		if(r2.getMinX() > r1.getMinX())
			dx1 = (int)(r2.getMinX() - r1.getMinX());

		/*
		if(r1.getMinY() > r2.getMinY())
			dy2 = (int)(r1.getMinY() - r2.getMinY());
		if(r1.getMinX() > r2.getMinX())
			dx2 = (int)(r1.getMinX() - r2.getMinX());
		*/
		for(int y = 0; y < ri.getHeight(); y++)
		{
			for(int x = 0; x < ri.getWidth(); x++)
			{
				if(image->getColor(dx1 + x, dy1 + y) == testColor)
				{
					minX = Math::min(minX, x);
					minY = Math::min(minY, y);
					maxX = Math::max(maxX, x);
					maxY = Math::max(maxY, y);
				}
			}
		}
		pixelIntersection = Rectanglef((int)ri.getMinX() + minX, (int)ri.getMinY() + minY, maxX-minX+1, maxY-minY+1);
		
		return !pixelIntersection.isEmpty();
	}
	return false;
}
static bool checkIntersectionFromBottom(Image* image, const Rectanglef& testRectangle, const Rectanglef& spriteRectangle, Rectanglef& pixelIntersection, const Color& testColor)
{
	int dx1 = 0;
	int dy1 = 0;
	/*
	int dx2 = 0;
	int dy2 = 0;
	*/
	Rectanglef r1 = testRectangle;
	Rectanglef r2 = spriteRectangle;
	Rectanglef ri = r1.intersected(r2);

	if(!ri.isEmpty())
	{
		int minX = (int)ri.getWidth();
		int minY = (int)ri.getHeight();
		int maxX = 0;
		int maxY = 0;
		
		if(r2.getMinY() > r1.getMinY())
			dy1 = (int)(r2.getMinY() - r1.getMinY());
		if(r2.getMinX() > r1.getMinX())
			dx1 = (int)(r2.getMinX() - r1.getMinX());
		
		for(int y = (int)(ri.getHeight()-1); y >= 0; y--)
		{
			bool colorMatch = false;
			for(int x = 0; x < ri.getWidth(); x++)
			{
				if(testColor == image->getColor(dx1 + x, dy1 + y))
				{
					minX = Math::min(minX, x);
					minY = Math::min(minY, y);
					maxX = Math::max(maxX, x);
					maxY = Math::max(maxY, y);
					colorMatch = true;
				}
			}
			if(!colorMatch)
				break;
		}
		pixelIntersection = Rectanglef((int)ri.getMinX() + minX, (int)ri.getMinY() + minY, maxX-minX+1, maxY-minY+1);
		
		return !pixelIntersection.isEmpty();
	}
	return false;
}
PixelMap::PixelMap(Image* img)
: testImage(img)
, testRectangle(0, 0, testImage->getWidth(), testImage->getHeight())
, testTexture(null)
, testTexturedTileMap(null)
{
	if(Debug::showPixelMap)
	{
		testTexture = testImage->toTexture();
	}
}
PixelMap::PixelMap(const char* fname)
: testImage(ImageLoader::load(fname))
, testRectangle(0, 0, testImage->getWidth(), testImage->getHeight())
, testTexture(null)
, testTexturedTileMap(null)
{
	if(Debug::showPixelMap)
	{
		char* p;
		char fullPath[256];
		std::string tmapfname;
		std::string tsetfname;
		
		strcpy(fullPath, fname);
		p = (char*)strchr(fullPath, '.');
		strcpy(p, "-tilemap.txt");
		tmapfname = fullPath;
		strcpy(p, "-tileset.png");
		tsetfname = fullPath;
		
		testTexturedTileMap = new TexturedTileMap(
					testImage->getWidth(),
					testImage->getHeight(),
					tmapfname.c_str(),
					tsetfname.c_str());
	}
}
PixelMap::~PixelMap()
{
	delete testImage;
	if(testTexture)
		delete testTexture;
	if(testTexturedTileMap)
		delete testTexturedTileMap;
}
unsigned int PixelMap::checkCollision(
						Entity* entity,
						Vector2f& newPosition,
						Vector2f& newVelocity,
						const Vector2f& oldPosition,
						const Vector2f& oldVelocity,
						unsigned int terrainType,
						unsigned int collisionFlags) const
{
	unsigned int flags = 0;
	Rectanglef rc;
	Rectanglef pixelIntersection;
	
	if(terrainType & MAP_TERRAIN_SOLID)
	{
		//
		// Colisión en X
		//
		if((newVelocity.x > 0 && collisionFlags&COLLISION_FLAG_RIGHT) || 
			(newVelocity.x < 0 && collisionFlags&COLLISION_FLAG_LEFT))
		{
			if(newVelocity.x > 0)
			{
				rc = entity->bounds(Math::ceil(newPosition.x), oldPosition.y);
			}
			else
			{
				rc = entity->bounds(Math::floor(newPosition.x), oldPosition.y);
			}
			if(checkIntersection(testImage, testRectangle, rc, pixelIntersection, COLOR_COLLISION_FULL))
			{
				if(((int)pixelIntersection.getHeight() == 1 || (int)pixelIntersection.getHeight() == 2)
						&& (rc.getMaxY() == pixelIntersection.getMaxY()))
				{
					//if(newVelocity.y > 0)
					{
						newPosition.y = pixelIntersection.getMinY();
						newVelocity.y = 0;
						flags |= COLLISION_FLAG_BOTTOM;
					}
				}
				else
				{
					if(newVelocity.x < 0)
						flags |= COLLISION_FLAG_LEFT;
					if(newVelocity.x > 0)
						flags |= COLLISION_FLAG_RIGHT;
					newVelocity.x = 0;
					newPosition.x = oldPosition.x;
				}
			}
		}
		//
		// Colisión en Y
		//
		if(newVelocity.y > 0 || newVelocity.y < 0)
		{
			if(newVelocity.y > 0)
			{
				rc = entity->bounds(newPosition.x, Math::ceil(newPosition.y));
			}
			else
			{
				rc = entity->bounds(newPosition.x, Math::floor(newPosition.y));
				rc = Rectanglef(rc.getX(), rc.getWidth(), rc.getMaxY()-2, 2);
			}
			
			if(checkIntersection(testImage, testRectangle, rc, pixelIntersection, COLOR_COLLISION_FULL))
			{
				if(newVelocity.y > 0)
				{
					flags |= COLLISION_FLAG_BOTTOM;
					newPosition.y = pixelIntersection.getMinY();
					newVelocity.y = 0;
				}
				else if(newVelocity.y < 0)
				{
					//if(pixelIntersection.getMinY() == rc.getMinY())
					{
						flags |= COLLISION_FLAG_TOP;
						newPosition.y = (int)(pixelIntersection.getMaxY()+rc.getHeight());
						newVelocity.x = 0;
						newVelocity.y /= 2;
					}
				}
			}
		}
	}
	if(terrainType & MAP_TERRAIN_TOPDOWN)
	{
		//
		// Colisión en Y
		//
		if(newVelocity.y > 0)
		{
			rc = entity->bounds(newPosition.x, Math::ceil(newPosition.y));
			if(checkIntersectionFromBottom(testImage, testRectangle, rc, pixelIntersection, COLOR_COLLISION_TOPDOWN))
			{
			//	if((int)rc.getMaxY() == (int)pixelIntersection.getMaxY())
				{
					flags |= COLLISION_FLAG_BOTTOM;
					newPosition.y = pixelIntersection.getMinY();
					newVelocity.y = 0;
				}
			}
		}
	}
	return flags;
}
void PixelMap::render(Graphics* gr, int sx1, int sy1, int sx2, int sy2, int dx1, int dy1, int dx2, int dy2)
{
	if(testTexture)
		gr->drawTexture(testTexture, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2);
	else if(testTexturedTileMap)
		testTexturedTileMap->render(gr, sx1, sy1);
}
