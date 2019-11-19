////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Utils
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Utils_h___
#define ___Utils_h___
#include <mach/Math.h>
#include <mach/Vector2f.h>

class Vector2f;

class Utils
{
public:
	static Vector2f getMoved(const Vector2f& v, double angle, double length)
	{
		return Vector2f(v.x + (Math::cos(angle)*length), v.y + (Math::sin(angle)*length));
	}

	static void move(Vector2f& pos, double angle, double len);

	//
	// Calcular el sprite activo en un avión de tipo 360, según su ángulo de inclinación
	//
	// También sirve para los sprites de cañones
	//
	static int spriteFromAngle(double radians, int count);
};

#endif
