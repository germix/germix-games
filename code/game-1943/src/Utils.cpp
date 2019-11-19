////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Utils
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Utils.h>

#include <mach/Math.h>
#include <mach/Vector2f.h>

void Utils::move(Vector2f& pos, double angle, double len)
{
	pos.x += (Math::cos(angle)*len);
	pos.y += (Math::sin(angle)*len);
}
int Utils::spriteFromAngle(double radians, int count)
{
	int index = -1;
	double degrees = radians * (180.0/Math::PI);

	if(degrees < 0.0)
		degrees = 360.0 + degrees;
	
	index = (int)(Math::round(degrees/(360.0/(double)(count)))) % count;
	
	return index;
}
