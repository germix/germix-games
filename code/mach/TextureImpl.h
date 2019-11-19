////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TextureImpl
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TextureImpl_h___
#define ___TextureImpl_h___
#include <mach/Texture.h>
#include <sdl/SDL_image.h>

class TextureImpl : public Texture
{
public:
	int width;
	int height;
	SDL_Texture* texture;
public:
	TextureImpl(int w, int h, SDL_Texture* tex)
		: width(w)
		, height(h)
		, texture(tex)
	{
	}
	~TextureImpl()
	{
		SDL_DestroyTexture(texture);
	}
public:
	virtual int getWidth() const
	{
		return width;
	}
	virtual int getHeight() const
	{
		return height;
	}
};

#endif
