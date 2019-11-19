////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformFixed
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PlatformFixed_h___
#define ___PlatformFixed_h___
#include <src/entities/platforms/Platform.h>

class PlatformFixed : public Platform
{
public:
	PlatformFixed(Scene* s, double x, double y, const EntityParameters& params);
	~PlatformFixed();
public:
	void update(double dt);
};

#endif
