////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Rectanglef
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Rectanglef_h___
#define ___Rectanglef_h___

class Point;

class Rectanglef
{
public:
	double x1;
	double y1;
	double x2;
	double y2;
public:
	Rectanglef() : x1(0), y1(0), x2(0), y2(0)
	{
	}
	Rectanglef(const char* s);
	Rectanglef(const Rectanglef& o) : x1(o.x1), y1(o.y1), x2(o.x2), y2(o.y2)
	{
	}
	Rectanglef(double x, double y, double w, double h) : x1(x), y1(y), x2(x+w), y2(y+h)
	{
	}
	~Rectanglef()
	{
	}
public:
	Rectanglef& operator = (const Rectanglef& o)
	{
		x1 = o.x1;
		y1 = o.y1;
		x2 = o.x2;
		y2 = o.y2;
		return *this;
	}
	bool isEmpty() const
	{
		return ((x2-x1) <= 0.0 || (y2-y1) <= 0.0);
	}
	double getX() const							{ return x1; }
	double getY() const							{ return y1; }
	double getMinX() const						{ return x1; }
	double getMinY() const						{ return y1; }
	double getMaxX() const						{ return x2; }
	double getMaxY() const						{ return y2; }
	double getWidth() const						{ return (x2-x1); }
	double getHeight() const					{ return (y2-y1); }
	double getCenterX() const					{ return (x1+x2)/2.0; }
	double getCenterY() const					{ return (y1+y2)/2.0; }
	Rectanglef& inflate(double d)
	{
		x1 -= d;
		y1 -= d;
		x2 += d;
		y2 += d;
		return *this;
	}
	Rectanglef& inflate(double dx, double dy)
	{
		x1 -= dx;
		y1 -= dy;
		x2 += dx;
		y2 += dy;
		return *this;
	}
	void       translate(double dx, double dy)
	{
		x1 += dx;
		x2 += dx;
		y1 += dy;
		y2 += dy;
	}
	bool       contains(const Point& p) const;
	bool       contains(const Rectanglef& r) const;
	bool       excluded(const Rectanglef& r) const;
	bool       intersects(const Rectanglef& r) const;
	Rectanglef intersected(const Rectanglef& r) const;
};

#endif
