////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Sprite
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/base/Sprite.h>

#include <mach/Texture.h>
#include <mach/Graphics.h>

Sprite::Sprite(Texture* tex, int count)
: texture(tex)
, startY(0)
, frameCount(count)
, frameWidth(tex->getWidth()/count)
, frameHeight(tex->getHeight())
{
}
Sprite::Sprite(Texture* tex, int count, int ___startY, int ___frameHeight)
: texture(tex)
, startY(___startY)
, frameCount(count)
, frameWidth(tex->getWidth()/count)
, frameHeight(___frameHeight)
{
}
Sprite::~Sprite()
{
}
void Sprite::render(Graphics* gr, int x, int y, int index) const
{
	int w = frameWidth;
	int h = frameHeight;
	int dx1 = x;
	int dy1 = y;
	int dx2 = dx1+w;
	int dy2 = dy1+h;
	int sx1 = index*w;
	int sy1 = startY;
	int sx2 = sx1+w;
	int sy2 = sy1+h;
	gr->drawTexture(texture, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2);
}
int Sprite::getFrameCount() const
{
	return frameCount;
}
int Sprite::getFrameWidth() const
{
	return frameWidth;
}
int Sprite::getFrameHeight() const
{
	return frameHeight;
}
