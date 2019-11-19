////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Sprite
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/sprites/Sprite.h>

#include <mach/Texture.h>
#include <mach/Graphics.h>
#include <mach/Vector2f.h>

Sprite::Sprite()
: width(0)
, height(0)
, count(0)
, texture(0)
{
}
Sprite::~Sprite()
{
	delete texture;
}
Rectanglef Sprite::rect(const Vector2f& pos) const
{
	double mw = width/2;
	double mh = height/2;
	return Rectanglef(pos.x-mw, pos.y-mh, width, height);
}
void       Sprite::render(Graphics* gr, double x, double y, int index)
{
	int dx1 = (int)(x - width/2);
	int dy1 = (int)(y - height/2);
	int dx2 = dx1 + width;
	int dy2 = dy1 + height;
	int sx1 = index*width;
	int sy1 = 0;
	int sx2 = sx1 + width;
	int sy2 = height;
	gr->drawTexture(texture, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2);
}
void       Sprite::render(Graphics* gr, double x, double y, int index, int alpha)
{
	int dx1 = (int)(x - width/2);
	int dy1 = (int)(y - height/2);
	int dx2 = dx1 + width;
	int dy2 = dy1 + height;
	int sx1 = index*width;
	int sy1 = 0;
	int sx2 = sx1 + width;
	int sy2 = height;
	gr->drawTexture(texture, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2, alpha);
}
