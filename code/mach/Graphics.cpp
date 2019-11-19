////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Graphics
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <mach/Graphics.h>
#include <stdio.h>
#include <sdl/sdl.h>
#include <mach/Color.h>
#include <mach/Rectangle.h>
#include <mach/Rectanglef.h>

#include "mach.h"
#include "Debug.h"
#include "TextureImpl.h"

Graphics::Graphics()
{
}
Graphics::~Graphics()
{
}
void Graphics::clip(int x, int y, int w, int h)
{
	SDL_Rect rc;
	rc.x = x;
	rc.y = y;
	rc.w = w;
	rc.h = h;
	SDL_RenderSetClipRect(mach.renderer, &rc);
}
void Graphics::translate(int dx, int dy)
{
	mach.graphicsX += dx;
	mach.graphicsY += dy;
}
void Graphics::drawLine(int x1, int y1, int x2, int y2, const Color& color)
{
	SDL_RenderDrawLine(
			mach.renderer,
			x1+mach.graphicsX,
			y1+mach.graphicsY,
			x2+mach.graphicsX,
			y2+mach.graphicsY);
}
void Graphics::drawRect(const Rectanglef& r, const Color& c)
{
	drawRect((int)r.getX(), (int)r.getY(), (int)r.getWidth(), (int)r.getHeight(), c);
}
void Graphics::drawRect(int x, int y, int w, int h, const Color& c)
{
	int a = c.alpha();
	SDL_Rect r;
	r.x = x+mach.graphicsX;
	r.y = y+mach.graphicsY;
	r.w = w;
	r.h = h;
	if(a != 0)
	{
		if(a == 255)
			SDL_SetRenderDrawBlendMode(mach.renderer, SDL_BLENDMODE_NONE);
		else
			SDL_SetRenderDrawBlendMode(mach.renderer, SDL_BLENDMODE_BLEND);

		SDL_SetRenderDrawColor(mach.renderer, c.red(), c.green(), c.blue(), a);
		SDL_RenderDrawRect(mach.renderer, &r);
	}
}
void Graphics::fillRect(const Rectanglef& r, const Color& c)
{
	fillRect(int(r.getX()), int(r.getY()), int(r.getWidth()), int(r.getHeight()), c);
}
void Graphics::fillRect(int x, int y, int w, int h, const Color& c)
{
	int a = c.alpha();
	SDL_Rect r;
	r.x = x+mach.graphicsX;
	r.y = y+mach.graphicsY;
	r.w = w;
	r.h = h;
	if(a != 0)
	{
		if(a == 255)
			SDL_SetRenderDrawBlendMode(mach.renderer, SDL_BLENDMODE_NONE);
		else
			SDL_SetRenderDrawBlendMode(mach.renderer, SDL_BLENDMODE_BLEND);

		SDL_SetRenderDrawColor(mach.renderer, c.red(), c.green(), c.blue(), a);
		SDL_RenderFillRect(mach.renderer, &r);
	}
}
void Graphics::drawTexture(Texture* texture, int x, int y)
{
	if(texture == NULL)
	{
		Debug::warning("Can't draw null texture\n");
	}
	else
	{
		drawTexture(texture, x, y, 255);
	}
}
void Graphics::drawTexture(Texture* texture, int sx1, int sy1, int sx2, int sy2, int dx1, int dy1, int dx2, int dy2)
{
	if(texture == NULL)
	{
		Debug::warning("Can't draw null texture\n");
	}
	else
	{
		drawTexture(texture, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2, 255);
	}
}
void Graphics::drawTexture(Texture* texture, int x, int y, int alpha)
{
	if(texture == NULL)
	{
		Debug::warning("Can't draw null texture\n");
	}
	else
	{
		SDL_Rect dst;
		dst.x = x+mach.graphicsX;
		dst.y = y+mach.graphicsY;
		dst.w = ((TextureImpl*)texture)->width;
		dst.h = ((TextureImpl*)texture)->height;
		SDL_SetTextureAlphaMod(((TextureImpl*)texture)->texture, alpha);
		SDL_RenderCopy(mach.renderer, ((TextureImpl*)texture)->texture, NULL, &dst);
		SDL_SetTextureAlphaMod(((TextureImpl*)texture)->texture, 255);
	}
}
void Graphics::drawTexture(Texture* texture, int sx1, int sy1, int sx2, int sy2, int dx1, int dy1, int dx2, int dy2, int alpha)
{
	if(texture == NULL)
	{
		Debug::warning("Can't draw null texture\n");
	}
	else if(alpha > 0)
	{
		int tmp;
		unsigned int flip = 0;
		if(dx1 > dx2)
		{
			flip |= SDL_FLIP_HORIZONTAL;
			tmp = dx1;
			dx1 = dx2;
			dx2 = tmp;
		}
		if(dy1 > dy2)
		{
			flip |= SDL_FLIP_VERTICAL;
			tmp = dy1;
			dy1 = dy2;
			dy2 = tmp;
		}

		SDL_Rect src;
		src.x = sx1;
		src.y = sy1;
		src.w = (sx2-sx1);
		src.h = (sy2-sy1);
		SDL_Rect dst;
		dst.x = dx1+mach.graphicsX;
		dst.y = dy1+mach.graphicsY;
		dst.w = dx2-dx1;
		dst.h = dy2-dy1;
		
		SDL_SetTextureAlphaMod(((TextureImpl*)texture)->texture, alpha);
		
		if(!flip)
			SDL_RenderCopy(mach.renderer, ((TextureImpl*)texture)->texture, &src, &dst);
		else
			SDL_RenderCopyEx(mach.renderer, ((TextureImpl*)texture)->texture, &src, &dst, 0, null, (const SDL_RendererFlip)flip);

		SDL_SetTextureAlphaMod(((TextureImpl*)texture)->texture, 255);
	}
}
void Graphics::drawTexture(Texture* texture, int sx1, int sy1, int sx2, int sy2, int dx1, int dy1, int dx2, int dy2, const Color& color)
{
	if(texture == NULL)
	{
		Debug::warning("Can't draw null texture\n");
	}
	else
	{
		Uint8 r;
		Uint8 g;
		Uint8 b;
		SDL_Texture* tex = ((TextureImpl*)texture)->texture;
		
		SDL_GetTextureColorMod(tex, &r, &g, &b);
		SDL_SetTextureColorMod(tex, color.red(), color.green(), color.blue());
		drawTexture(texture, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2, color.alpha());
		SDL_SetTextureColorMod(tex, r, g, b);
	}
}
