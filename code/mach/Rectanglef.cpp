////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Rectanglef
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <mach/Rectanglef.h>
#include <mach/Math.h>
#include <mach/Point.h>

#include <ctype.h>
#include <stdlib.h>

Rectanglef::Rectanglef(const char* s)
{
	int x = atoi(s);
	while(isalnum(*s)) s++;		// Digitos
	s++;						// ','
	int y = atoi(s);
	while(isalnum(*s)) s++;		// Digitos
	s++;						// ','
	int w = atoi(s);
	while(isalnum(*s)) s++;		// Digitos
	s++;						// ','
	int h = atoi(s);
	
	x1 = double(x);
	y1 = double(y);
	x2 = double(x+w);
	y2 = double(y+h);
}
bool   Rectanglef::contains(const Point& p) const
{
	double l = getX();
	double r = getX();
	if(getWidth() < 0)
		l += getWidth();
	else
		r += getWidth();
	if(l == r) // null rect
		return false;

	if(p.x < l || p.x > r)
		return false;

	double t = getY();
	double b = getY();
	if(getHeight() < 0)
		t += getHeight();
	else
		b += getHeight();
	if(t == b) // null rect
		return false;

	if(p.y < t || p.y > b)
		return false;

	return true;
}
bool   Rectanglef::contains(const Rectanglef& r) const
{
	double l1 = getX();
	double r1 = getX();
	if(getWidth() < 0)
		l1 += getWidth();
	else
		r1 += getWidth();
	if(l1 == r1) // null rect
		return false;

	double l2 = r.getX();
	double r2 = r.getX();
	if(r.getWidth() < 0)
		l2 += r.getWidth();
	else
		r2 += r.getWidth();
	if(l2 == r2) // null rect
		return false;

	if(l2 < l1 || r2 > r1)
		return false;

	double t1 = getY();
	double b1 = getY();
	if(getHeight() < 0)
		t1 += getHeight();
	else
		b1 += getHeight();
	if(t1 == b1) // null rect
		return false;

	double t2 = r.getY();
	double b2 = r.getY();
	if(r.getHeight() < 0)
		t2 += r.getHeight();
	else
		b2 += r.getHeight();
	if(t2 == b2) // null rect
		return false;

	if(t2 < t1 || b2 > b1)
		return false;

	return true;
}
bool   Rectanglef::excluded(const Rectanglef& r) const
{
	if(r.x2 < x1) return true;
	if(r.y2 < y1) return true;
	if(r.x1 > x2) return true;
	if(r.y1 > y2) return true;
	return false;
}
bool   Rectanglef::intersects(const Rectanglef& r) const
{
	double l1 = getX();
	double r1 = getX();
	if(getWidth() < 0)
		l1 += getWidth();
	else
		r1 += getWidth();
	if(l1 == r1) // null rect
		return false;

	double l2 = r.getX();
	double r2 = r.getX();
	if(r.getWidth() < 0)
		l2 += r.getWidth();
	else
		r2 += r.getWidth();
	if(l2 == r2) // null rect
		return false;

	if(l1 >= r2 || l2 >= r1)
		return false;

	double t1 = getY();
	double b1 = getY();
	if(getHeight() < 0)
		t1 += getHeight();
	else
		b1 += getHeight();
	if(t1 == b1) // null rect
		return false;

	double t2 = r.getY();
	double b2 = r.getY();
	if(r.getHeight() < 0)
		t2 += r.getHeight();
	else
		b2 += r.getHeight();
	if(t2 == b2) // null rect
		return false;

	if(t1 >= b2 || t2 >= b1)
		return false;

	return true;
}
Rectanglef  Rectanglef::intersected(const Rectanglef& r) const
{
	double l1 = getX();
	double r1 = getX();
	if(getWidth() < 0)
		l1 += getWidth();
	else
		r1 += getWidth();
	if(l1 == r1) // null rect
		return Rectanglef();

	double l2 = r.getX();
	double r2 = r.getX();
	if(r.getWidth() < 0)
		l2 += r.getWidth();
	else
		r2 += r.getWidth();
	if(l2 == r2) // null rect
		return Rectanglef();

	if(l1 >= r2 || l2 >= r1)
		return Rectanglef();

	double t1 = getY();
	double b1 = getY();
	if(getHeight() < 0)
		t1 += getHeight();
	else
		b1 += getHeight();
	if(t1 == b1) // null rect
		return Rectanglef();

	double t2 = r.getY();
	double b2 = r.getY();
	if(r.getHeight() < 0)
		t2 += r.getHeight();
	else
		b2 += r.getHeight();
	if(t2 == b2) // null rect
		return Rectanglef();

	if(t1 >= b2 || t2 >= b1)
		return Rectanglef();

	double x = Math::max(l1, l2);
	double y = Math::max(t1, t2);
	double w = Math::min(r1, r2) - x;
	double h = Math::min(b1, b2) - y;
	return Rectanglef(x, y, w, h);
}


