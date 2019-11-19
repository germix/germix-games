////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Vector2f
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Vector2f_h___
#define ___Vector2f_h___

class Vector2f
{
public:
	double x;
	double y;
public:
	Vector2f();
	Vector2f(double x, double y);
	Vector2f(const Vector2f& other);
public:
	Vector2f& operator = (const Vector2f& other);
	Vector2f& operator *= (double f);
	Vector2f& operator /= (double f);
	Vector2f& operator += (const Vector2f& other);
	Vector2f& operator -= (const Vector2f& other);
public:
	double getAngle() const;
	double getLength() const;
	double getDistanceOf(const Vector2f& o) const;
};

inline Vector2f::Vector2f() : x(0), y(0)
{
}
inline Vector2f::Vector2f(double _x, double _y) : x(_x), y(_y)
{
}
inline Vector2f::Vector2f(const Vector2f& other) : x(other.x), y(other.y)
{
}
inline Vector2f& Vector2f::operator = (const Vector2f& other)
{
	x = other.x;
	y = other.y;
	return *this;
}
inline Vector2f& Vector2f::operator *= (double f)
{
	x *= f;
	y *= f;
	return *this;
}
inline Vector2f& Vector2f::operator /= (double f)
{
	x /= f;
	y /= f;
	return *this;
}
inline Vector2f& Vector2f::operator += (const Vector2f& other)
{
	x += other.x;
	y += other.y;
	return *this;
}
inline Vector2f& Vector2f::operator -= (const Vector2f& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}
inline Vector2f operator / (const Vector2f& v, double f)
{
	return Vector2f(v.x/f, v.y/f);
}
inline Vector2f operator * (const Vector2f& v, double f)
{
	return Vector2f(v.x*f, v.y*f);
}
inline Vector2f operator - (const Vector2f& v1, const Vector2f& v2)
{
	return Vector2f(v1.x - v2.x, v1.y - v2.y);
}
inline Vector2f operator + (const Vector2f& v1, const Vector2f& v2)
{
	return Vector2f(v1.x + v2.x, v1.y + v2.y);
}
#endif
