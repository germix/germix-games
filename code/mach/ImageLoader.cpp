////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ImageLoader
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <mach/ImageLoader.h>

#include "Debug.h"
#include "ImageImpl.h"

Image* ImageLoader::load(const char* fileName)
{
	SDL_Surface* surf = IMG_Load(fileName);
	if(surf)
	{
		return new ImageImpl(surf);
	}
	Debug::warning("Can't load the image \"%s\". %s.\n", fileName, SDL_GetError());
	return NULL;
}
