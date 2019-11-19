////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MissionMapRenderable
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/scene/MissionMapRenderable.h>
#include <src/Config.h>

#include <mach/Math.h>
#include <mach/Texture.h>
#include <mach/Graphics.h>
#include <mach/Rectanglef.h>

static int makePosition(int cameraPos, int cameraSize, int backgroundPos, int backgroundSize, int imageSize)
{
	int min = backgroundPos;
	int size1;
	int size2;
	
	if(backgroundSize < cameraSize)
	{
		size1 = backgroundSize-imageSize;
		size2 = size1;
	}
	else
	{
		size1 = backgroundSize-cameraSize;
		size2 = backgroundSize-imageSize;
	}
	int dist = cameraPos-min;
	if(dist < 0)
		dist = 0;
	if(dist >= size1) dist = size1;
	
	double percent = (size1==0) ? 0 : (dist*100.0)/(double)size1;
	double position = ((percent*(double)size2)/100.0);
	
	return min + (int)position;
}
void MissionMapRenderable::update(double dt)
{
	if(textures.size() && clock.update(dt))
	{
		if(++currentTexture >= textures.size())
		{
			currentTexture = 0;
		}
	}
}
void MissionMapRenderable::render(Graphics* gr, int sx, int sy)
{
	Rectangle cameraRect(sx, sy, SCREEN_WIDTH, SCREEN_HEIGHT);
	Rectangle intersectionRect = rect.intersected(cameraRect);

	if(!intersectionRect.isEmpty())
	{
		Texture* tex = textures[currentTexture];
		
		if(type == TYPE_FIXED)
		{
			int dstX1 = intersectionRect.getX()-sx;
			int dstY1 = intersectionRect.getY()-sy;
			int dstX2 = dstX1+intersectionRect.getWidth();
			int dstY2 = dstY1+intersectionRect.getHeight();
			
			intersectionRect = Rectangle(
					Math::max(0, sx-rect.getX()),
					Math::max(0, sy-rect.getY()),
					intersectionRect.getWidth(),
					intersectionRect.getHeight()).intersected(
						Rectangle(
							0,
							0,
							tex->getWidth(),
							tex->getHeight()));
			int srcX1 = intersectionRect.getMinX();
			int srcY1 = intersectionRect.getMinY();
			int srcX2 = intersectionRect.getMaxX();
			int srcY2 = intersectionRect.getMaxY();

			gr->drawTexture
			(
				tex,
				srcX1,
				srcY1,
				srcX2,
				srcY2,
				dstX1,
				dstY1,
				dstX2,
				dstY2
			);
		}
		else
		{
			Rectangle camera(sx, sy, SCREEN_WIDTH, SCREEN_HEIGHT);
			
			if(camera.intersects(rect))
			{
				int imageW = textures[currentTexture]->getWidth();
				int imageH = textures[currentTexture]->getHeight();
				
				int imageX = makePosition(camera.getX(), camera.getWidth(), rect.getX(), rect.getWidth(), imageW);
				int imageY = makePosition(camera.getY(), camera.getHeight(), rect.getY(), rect.getHeight(), imageH);
				
				gr->drawTexture(textures[currentTexture], imageX-sx, imageY-sy);
			}
		}
	}
}

