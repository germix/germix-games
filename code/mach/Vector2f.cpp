////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Vector2f
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <mach/Vector2f.h>
#include <math.h>
#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288   /**< pi */
#endif

double Vector2f::getAngle() const
{
	double a = atan2(y, x) * 180.0 / M_PI;
	if(a < 0)
		return 360 + a;
	return a;
}
double Vector2f::getLength() const
{
	return sqrt(x*x + y*y);
}
double Vector2f::getDistanceOf(const Vector2f& o) const
{
	double dx = (x-o.x);
	double dy = (y-o.y);
	return sqrt(dx*dx + dy*dy);
}

