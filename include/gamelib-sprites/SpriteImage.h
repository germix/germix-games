////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SpriteImage
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SpriteImage_h___
#define ___SpriteImage_h___
#include <map>
#include <string>
#include <mach/Point.h>

class Texture;

class SpriteImage
{
public:
	int									x;
	int									y;
	int									width;
	int									height;
	Texture*							texture;
	Point								anchor;
	std::map<std::string, Point>		attachedPoints;
	std::map<std::string, Rectangle>	attachedRectangles;
public:
	SpriteImage() {}
	~SpriteImage() {}
};

#endif
