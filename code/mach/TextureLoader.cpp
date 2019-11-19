////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TextureLoader
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <mach/Texture.h>
#include <mach/TextureLoader.h>

#include "mach.h"
#include "Debug.h"
#include "TextureImpl.h"

Texture* TextureLoader::load(const char* fileName)
{
	SDL_Texture* tex = IMG_LoadTexture(mach.renderer, fileName);
	if(tex)
	{
		int w;
		int h;
		Uint32 fmt;
		SDL_QueryTexture(tex, &fmt, NULL, &w, &h);
		return new TextureImpl(w, h, tex);
	}
	Debug::warning("Can't load the image \"%s\". %s.\n", fileName, SDL_GetError());
	return NULL;
}

