////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformFallUp
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PlatformFallUp_h___
#define ___PlatformFallUp_h___
#include <src/entities/platforms/Platform.h>

class PlatformFallUp : public Platform
{
	bool started;
public:
	PlatformFallUp(Scene* s, double x, double y, const EntityParameters& params);
	~PlatformFallUp();
public:
	void update(double dt);
};

#endif
