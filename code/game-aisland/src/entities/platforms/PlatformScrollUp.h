////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformScrollUp
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PlatformScrollUp_h___
#define ___PlatformScrollUp_h___
#include <src/entities/platforms/Platform.h>

class PlatformScrollUp : public Platform
{
public:
	PlatformScrollUp(Scene* s, double x, double y, const EntityParameters& params);
	~PlatformScrollUp();
public:
	void update(double dt);
};

#endif
