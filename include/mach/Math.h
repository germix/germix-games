////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Math
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Math_h___
#define ___Math_h___
#include <math.h>
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

class Math
{
public:
	static const double PI;
	static const float FLOAT_EPSILON;
	static const double DOUBLE_EPSILON;
public:
	static int abs(int x) { return ::abs(x); }

	static float abs(float x) { return ::fabs(x); }
	static float sin(float x) { return ::sinf(x); }
	static float cos(float x) { return ::cosf(x); }
	static float tan(float x) { return ::tanf(x); }
	static float asin(float x) { return ::asinf(x); }
	static float acos(float x) { return ::acosf(x); }
	static float atan(float x) { return ::atanf(x); }
	static float sqrt(float x) { return ::sqrtf(x); }
	static float round(float x) { return (float)((int)x); }
	static float ceil(float x) { return ::ceilf(x); }
	static float floor(float x) { return ::floorf(x); }
	static float atan2(float y, float x) { return ::atan2f(y, x); }
	static float toRadians(float degree);
	static float toDegrees(float radian);
	
	static double abs(double x) { return ::abs(x); }
	static double sin(double x) { return ::sin(x); }
	static double cos(double x) { return ::cos(x); }
	static double tan(double x) { return ::tan(x); }
	static double asin(double x) { return ::asin(x); }
	static double acos(double x) { return ::acos(x); }
	static double atan(double x) { return ::atan(x); }
	static double sqrt(double x) { return ::sqrt(x); }
	static double round(double x) { return (double)((int)x); }
	static double ceil(double x) { return ::ceil(x); }
	static double floor(double x) { return ::floor(x); }
	static double atan2(double y, double x) { return ::atan2(y, x); }
	static double toRadians(double degree);
	static double toDegrees(double radian);

	/*
	static float min(float a, float b) { return ((a < b) ? a : b); }
	static float max(float a, float b) { return ((a > b) ? a : b); }
	static float min(float a, float b, float c) { return Math::min(a,Math::min(b,c)); }
	static float max(float a, float b, float c) { return Math::max(a,Math::max(b,c)); }
	static double min(double a, double b) { return ((a < b) ? a : b); }
	static double max(double a, double b) { return ((a > b) ? a : b); }
	static double min(double a, double b, double c) { return Math::min(a,Math::min(b,c)); }
	static double max(double a, double b, double c) { return Math::max(a,Math::max(b,c)); }
	*/
	static int rand();

	static bool isZero(float v);
	static bool isZero(double v);
	static bool isEquals(float v1, float v2);
	static bool isEquals(double v1, double v2);
	static float getReciprocal(float v) { return v; }
	static double getReciprocal(double v) { return v; }

	template <typename T>
	inline static const T min(const T& a, const T& b) { return ((a < b) ? a : b); }
	template <typename T>
	inline static const T min(const T& a, const T& b, const T& c) { return min(a,min(b,c)); }
	template <typename T>
	inline static const T max(const T& a, const T& b) { return ((a > b) ? a : b); }
	template <typename T>
	inline static const T max(const T& a, const T& b, const T& c) { return max(a,max(b,c)); }
	template <typename T>
	inline static const T clamp(const T& value, const T& low, const T& high) { return min(max(value, low), high); }
	template <class T>
	inline static void swap(T& a, T& b) { T c(a); a = b; b = c; }
};

#endif
