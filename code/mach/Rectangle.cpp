////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Rectangle
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <mach/Rectangle.h>
#include <mach/Math.h>
#include <mach/Point.h>

#include <ctype.h>
#include <stdlib.h>

Rectangle::Rectangle(const char* s)
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
	
	x1 = x;
	y1 = y;
	x2 = x+w-1;
	y2 = y+h-1;
}
bool Rectangle::intersects(const Rectangle &r) const
{
	if(isNull() || r.isNull())
		return false;

	int l1 = x1;
	int r1 = x1;
	if(x2 - x1 + 1 < 0)
		l1 = x2;
	else
		r1 = x2;

	int l2 = r.x1;
	int r2 = r.x1;
	if(r.x2 - r.x1 + 1 < 0)
		l2 = r.x2;
	else
		r2 = r.x2;

	if(l1 > r2 || l2 > r1)
		return false;

	int t1 = y1;
	int b1 = y1;
	if(y2 - y1 + 1 < 0)
		t1 = y2;
	else
		b1 = y2;

	int t2 = r.y1;
	int b2 = r.y1;
	if(r.y2 - r.y1 + 1 < 0)
		t2 = r.y2;
	else
		b2 = r.y2;

	if(t1 > b2 || t2 > b1)
		return false;

	return true;
}
Rectangle Rectangle::intersected(const Rectangle& r) const
{
	if(isNull() || r.isNull())
		return Rectangle();

	int l1 = x1;
	int r1 = x1;
	if(x2 - x1 + 1 < 0)
		l1 = x2;
	else
		r1 = x2;

	int l2 = r.x1;
	int r2 = r.x1;
	if(r.x2 - r.x1 + 1 < 0)
		l2 = r.x2;
	else
		r2 = r.x2;

	if (l1 > r2 || l2 > r1)
		return Rectangle();

	int t1 = y1;
	int b1 = y1;
	if(y2 - y1 + 1 < 0)
		t1 = y2;
	else
		b1 = y2;

	int t2 = r.y1;
	int b2 = r.y1;
	if(r.y2 - r.y1 + 1 < 0)
		t2 = r.y2;
	else
		b2 = r.y2;

	if(t1 > b2 || t2 > b1)
		return Rectangle();

	Rectangle tmp;
	tmp.x1 = Math::max(l1, l2);
	tmp.x2 = Math::min(r1, r2);
	tmp.y1 = Math::max(t1, t2);
	tmp.y2 = Math::min(b1, b2);
	return tmp;
}
