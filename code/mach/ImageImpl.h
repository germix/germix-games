////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ImageImpl
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ImageImpl_h___
#define ___ImageImpl_h___
#include <mach/Image.h>

#include <sdl/SDL_image.h>

#include "mach.h"
#include "TextureImpl.h"

class ImageImpl : public Image
{
public:
	SDL_Surface* surface;
public:
	ImageImpl(SDL_Surface* s) : surface(s)
	{
	}
	virtual ~ImageImpl() {}
public:
	virtual int getWidth() const
	{
		return surface->w;
	}
	virtual int getHeight() const
	{
		return surface->h;
	}
	virtual Color getColor(int x, int y) const
	{
		Uint8 r;
		Uint8 g;
		Uint8 b;
		Uint8 a;
		Uint32 pixelPosition = y * (surface->pitch / sizeof(unsigned int)) + x;
		SDL_GetRGBA(((Uint32*)surface->pixels)[pixelPosition], surface->format, &r, &g, &b, &a);
		return Color(r, g, b, a);
	}
	virtual TextureImpl* toTexture() const
	{
		SDL_Texture* tex = SDL_CreateTextureFromSurface(mach.renderer, surface);
		if(tex)
			return new TextureImpl(surface->w, surface->h, tex);
		return null;
	}
};

#endif
