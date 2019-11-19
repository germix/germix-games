////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Rectangle
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Rectangle_h___
#define ___Rectangle_h___

class Point;

class Rectangle
{
	int x1;
	int y1;
	int x2;
	int y2;
public:
	Rectangle() : x1(0), y1(0), x2(0), y2(0)
	{
	}
	Rectangle(const char* s);
	Rectangle(const Rectangle& o) : x1(o.x1), y1(o.y1), x2(o.x2), y2(o.y2)
	{
	}
	Rectangle(int x, int y, int w, int h) : x1(x), y1(y), x2(x+w-1), y2(y+h-1)
	{
	}
	~Rectangle()
	{
	}
public:
	Rectangle& operator = (const Rectangle& o)
	{
		x1 = o.x1;
		y1 = o.y1;
		x2 = o.x2;
		y2 = o.y2;
		return *this;
	}
	bool isNull() const { return x2 == x1 - 1 && y2 == y1 - 1; }
	bool isEmpty() const { return x1 > x2 || y1 > y2; }
	bool isValid() const { return x1 <= x2 && y1 <= y2; }

	int getX() const						{ return x1; }
	int getY() const						{ return y1; }
	int getMinX() const						{ return x1; }
	int getMinY() const						{ return y1; }
	int getMaxX() const						{ return x2; }
	int getMaxY() const						{ return y2; }
	int getWidth() const					{ return (x2-x1+1); }
	int getHeight() const					{ return (y2-y1+1); }
	int getCenterX() const					{ return (x1+x2)/2; }
	int getCenterY() const					{ return (y1+y2)/2; }
	Rectangle& inflate(int d)
	{
		x1 -= d;
		y1 -= d;
		x2 += d;
		y2 += d;
		return *this;
	}
	Rectangle& inflate(int dx, int dy)
	{
		x1 -= dx;
		y1 -= dy;
		x2 += dx;
		y2 += dy;
		return *this;
	}
	void       translate(int dx, int dy)
	{
		x1 += dx;
		x2 += dx;
		y1 += dy;
		y2 += dy;
	}
	bool      contains(const Point& p) const;
	bool      contains(const Rectangle& r) const;
	bool      excluded(const Rectangle& r) const;
	bool      intersects(const Rectangle& r) const;
	Rectangle intersected(const Rectangle& r) const;
};

#endif
