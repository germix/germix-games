////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Sprite
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteFrame.h>
#include <gamelib-sprites/SpriteImage.h>
#include <mach/Graphics.h>
#include <math.h>

double round(double x)
{
	return (double)((int)x);
}
Sprite::Sprite()
{
}
Sprite::~Sprite()
{
	for(unsigned int i = 0; i < frames.size(); i++)
		delete frames[i];
	frames.clear();
}
void		Sprite::render(Graphics* gr, double px, double py, int index, unsigned int hints) const
{
	int tmp;
	int pivotX = frames[index]->image->anchor.x;
	int pivotY = frames[index]->image->anchor.y;
	int imageX = frames[index]->image->x;
	int imageY = frames[index]->image->y;
	int imageWidth = frames[index]->image->width;
	int imageHeight = frames[index]->image->height;
	int dx1 = (int)round(px);
	int dy1 = (int)round(py);
	int dx2 = dx1+imageWidth;
	int dy2 = dy1+imageHeight;
	int sx1 = imageX;
	int sy1 = imageY;
	int sx2 = imageX+imageWidth;
	int sy2 = imageY+imageHeight;
	
	if((hints & FLIP_X) == 0)
	{
		dx1 -= pivotX;
		dx2 -= pivotX;
	}
	else
	{
		tmp = dx1;
		dx1 = dx2;
		dx2 = tmp;
		dx1 -= (imageWidth-pivotX)-1;
		dx2 -= (imageWidth-pivotX)-1;
	}
	if((hints & FLIP_Y) == 0)
	{
		dy1 -= pivotY;
		dy2 -= pivotY;
	}
	else
	{
		tmp = dy1;
		dy1 = dy2;
		dy2 = tmp;
		dy1 -= (imageHeight-pivotY)-1;
		dy2 -= (imageHeight-pivotY)-1;
	}
#if 0
	printf("sx1: %d, sy1: %d, sx2: %d, sy2: %d\n", sx1, sy1, sx2, sy2);
	printf("dx1: %d, dy1: %d, dx2: %d, dy2: %d\n", dx1, dy1, dx2, dy2);
#endif
	gr->drawTexture(frames[index]->image->texture, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2);
}
void		Sprite::render(Graphics* gr, double px, double py, int index, unsigned int hints, const Color& color) const
{
	int tmp;
	int pivotX = frames[index]->image->anchor.x;
	int pivotY = frames[index]->image->anchor.y;
	int imageX = frames[index]->image->x;
	int imageY = frames[index]->image->y;
	int imageWidth = frames[index]->image->width;
	int imageHeight = frames[index]->image->height;
	int dx1 = (int)round(px);
	int dy1 = (int)round(py);
	int dx2 = dx1+imageWidth;
	int dy2 = dy1+imageHeight;
	int sx1 = imageX;
	int sy1 = imageY;
	int sx2 = imageX+imageWidth;
	int sy2 = imageY+imageHeight;
	
	if((hints & FLIP_X) == 0)
	{
		dx1 -= pivotX;
		dx2 -= pivotX;
	}
	else
	{
		tmp = dx1;
		dx1 = dx2;
		dx2 = tmp;
		dx1 -= (imageWidth-pivotX)-1;
		dx2 -= (imageWidth-pivotX)-1;
	}
	if((hints & FLIP_Y) == 0)
	{
		dy1 -= pivotY;
		dy2 -= pivotY;
	}
	else
	{
		tmp = dy1;
		dy1 = dy2;
		dy2 = tmp;
		dy1 -= (imageHeight-pivotY)-1;
		dy2 -= (imageHeight-pivotY)-1;
	}
#if 0
	printf("sx1: %d, sy1: %d, sx2: %d, sy2: %d\n", sx1, sy1, sx2, sy2);
	printf("dx1: %d, dy1: %d, dx2: %d, dy2: %d\n", dx1, dy1, dx2, dy2);
#endif
	gr->drawTexture(frames[index]->image->texture, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2, color);
}
Point		Sprite::point(double px, double py, int index, unsigned int hints)
{
	Point anchor = frames[index]->image->anchor;
	int posX = 0;
	int posY = 0;
	
	if((hints & Sprite::FLIP_X) == 0)
		posX = (int)(px-anchor.x);
	else
		posX = (int)(px+anchor.x);
	
	if((hints & Sprite::FLIP_Y) == 0)
		posY = (int)(py-anchor.y);
	else
		posY = (int)(py+anchor.y);
	
	return Point(posX, posY);
}
Point		Sprite::point(const char* name, double px, double py, int index, unsigned int hints) const
{
	SpriteImage* image = frames[index]->image;
	Point attach;
	std::map<std::string, Point>::const_iterator it = image->attachedPoints.find(name);
	if(it != image->attachedPoints.end())
		attach = it->second;
	else
		attach = attachedPoints.find(name)->second;
	Point anchor = image->anchor;
	int posX = 0;
	int posY = 0;
	int anchorX = anchor.x-attach.x;
	int anchorY = anchor.y-attach.y;
	
	if((hints & Sprite::FLIP_X) == 0)
		posX = (int)(px-anchorX);
	else
		posX = (int)(px+anchorX);
	
	if((hints & Sprite::FLIP_Y) == 0)
		posY = (int)(py-anchorY);
	else
		posY = (int)(py+anchorY);
	
	return Point(posX, posY);
}
Rectanglef	Sprite::rectangle(double x, double y, int index, unsigned int hints) const
{
	double boundX = 0;
	double boundY = 0;
	SpriteImage* image = frames[index]->image;
	
	if((hints & Sprite::FLIP_X) == 0)
		boundX = (x - image->anchor.x);
	else
		boundX = (x - (image->width - image->anchor.x-1));
		
	if((hints & Sprite::FLIP_Y) == 0)
		boundY = (y - image->anchor.y);
	else
		boundY = (y - (image->height - image->anchor.y-1));
	
	return Rectanglef(boundX, boundY, double(image->width), double(image->height));
}
Rectanglef	Sprite::rectangle(const char* name, double x, double y, int index, unsigned int hints) const
{
	Rectangle rect;
	bool found = false;
	SpriteImage* image = frames[index]->image;
	std::map<std::string, Rectangle>::const_iterator it = image->attachedRectangles.find(name);
	if(it != image->attachedRectangles.end())
	{
		rect = it->second;
		found = true;
	}
	else
	{
		it = attachedRectangles.find(name);
		if(it != attachedRectangles.end())
		{
			rect = it->second;
			found = true;
		}
	}
	if(found)
	{
		double rx = 0;
		double ry = 0;
		Rectangle rect = it->second;
		
		if((hints & Sprite::FLIP_X) == 0)
			rx = (x - image->anchor.x) + rect.getX();
		else
			rx = (x - (rect.getWidth()-(image->anchor.x - rect.getX())-1));
			
		if((hints & Sprite::FLIP_Y) == 0)
			ry = (y - image->anchor.y) + rect.getY();
		else
			ry = (y - (rect.getHeight()-(image->anchor.y - rect.getY())-1));
		
		return Rectanglef(rx, ry, double(rect.getWidth()), double(rect.getHeight()));
	}
	return Rectanglef();
}
