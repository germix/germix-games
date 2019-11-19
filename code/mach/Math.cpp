////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Math
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <mach/Math.h>
#include <float.h>
#include <stdlib.h>

#ifndef M_E
#define M_E        2.71828182845904523536
#define M_LOG2E    1.44269504088896340736
#define M_LOG10E   0.434294481903251827651
#define M_LN2      0.693147180559945309417
#define M_LN10     2.30258509299404568402
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616
#define M_1_PI     0.318309886183790671538
#define M_2_PI     0.636619772367581343076
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT1_2  0.707106781186547524401
#endif

const double Math::PI = M_PI;
const float Math::FLOAT_EPSILON = FLT_EPSILON;
const double Math::DOUBLE_EPSILON = DBL_EPSILON;

int Math::rand()
{
	return ::rand();
}
float Math::toRadians(float degree)
{
	return (float)(degree * M_PI / 180.0);
}
float Math::toDegrees(float radian)
{
	return (float)(radian * 180.0 / M_PI);
}
double Math::toRadians(double degree)
{
	return (degree * M_PI / 180.0);
}
double Math::toDegrees(double radian)
{
	return (radian * 180.0 / M_PI);
}
bool Math::isZero(float v)
{
	return (Math::abs(v) <= Math::FLOAT_EPSILON);
}
bool Math::isZero(double v)
{
	return (Math::abs(v) <= Math::DOUBLE_EPSILON);
}
bool Math::isEquals(float v1, float v2)
{
	return (Math::abs(v1-v2) <= Math::FLOAT_EPSILON);
}
bool Math::isEquals(double v1, double v2)
{
	return (Math::abs(v1-v2) <= Math::DOUBLE_EPSILON);
}
