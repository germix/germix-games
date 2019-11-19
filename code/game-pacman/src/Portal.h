////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Portal
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Portal_h___
#define ___Portal_h___
#include <mach/Point.h>
#include <mach/Rectangle.h>

class Portal
{
	Rectangle	rect;
	Point		destination;
public:
	Portal(int x, int y, int w, int h, int dstX, int dstY) : rect(x,y,w,h), destination(dstX,dstY)
	{
	}
public:
	const Rectangle& getRectangle() const
	{
		return rect;
	}
	const Point& getDestination() const
	{
		return destination;
	}
};

#endif
