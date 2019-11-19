////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformFallDown
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PlatformFallDown_h___
#define ___PlatformFallDown_h___
#include <src/entities/platforms/Platform.h>

class PlatformFallDown : public Platform
{
	bool started;
public:
	PlatformFallDown(Scene* s, double x, double y, const EntityParameters& params);
	~PlatformFallDown();
public:
	void update(double dt);
};

#endif
