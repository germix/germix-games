////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Image
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Image_h___
#define ___Image_h___
#include <mach/Color.h>

class Texture;

class Image
{
public:
	Image() {}
	virtual ~Image() {}
public:
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
	virtual Color getColor(int x, int y) const = 0;
	virtual Texture* toTexture() const = 0;
};

#endif
