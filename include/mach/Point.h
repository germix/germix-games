////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Point
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Point_h___
#define ___Point_h___

class Point
{
public:
	int x;
	int y;
public:
	Point();
	Point(int x, int y);
	Point(const char* s);
	Point(const Point& other);
public:
	Point& operator = (const Point& other);
};


inline Point::Point() : x(0), y(0)
{
}
inline Point::Point(int _x, int _y) : x(_x), y(_y)
{
}
inline Point::Point(const Point& other) : x(other.x), y(other.y)
{
}
inline Point& Point::operator = (const Point& other)
{
	x = other.x;
	y = other.y;
	return *this;
}

#endif
