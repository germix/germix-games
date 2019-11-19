////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Sprite
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Sprite_h___
#define ___Sprite_h___
#include <string>
#include <map>
#include <vector>
#include <mach/Point.h>
#include <mach/Rectangle.h>
#include <mach/Rectanglef.h>

class Color;
class Graphics;
class SpriteFrame;

class Sprite
{
public:
	enum
	{
		FLIP_X = 0x01,
		FLIP_Y = 0x02,
	};
public:
	std::string							name;
	std::vector<SpriteFrame*>			frames;
	std::map<std::string, Point>		attachedPoints;
	std::map<std::string, Rectangle>	attachedRectangles;
public:
	Sprite();
	~Sprite();
public:
	int			count() const { return frames.size(); }
	void		render(Graphics* gr, double px, double py, int index, unsigned int hints) const;
	void		render(Graphics* gr, double px, double py, int index, unsigned int hints, const Color& color) const;

	Point		point(double px, double py, int index, unsigned int hints);
	Point		point(const char* name, double px, double py, int index, unsigned int hints) const;
	
	Rectanglef	rectangle(double x, double y, int index, unsigned int hints) const;
	Rectanglef	rectangle(const char* name, double x, double y, int index, unsigned int hints) const;
};

#endif