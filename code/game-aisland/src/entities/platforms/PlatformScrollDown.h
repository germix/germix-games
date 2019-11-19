////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformScrollDown
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PlatformScrollDown_h___
#define ___PlatformScrollDown_h___
#include <src/entities/platforms/Platform.h>

class PlatformScrollDown : public Platform
{
public:
	PlatformScrollDown(Scene* s, double x, double y, const EntityParameters& params);
	~PlatformScrollDown();
public:
	void update(double dt);
};

#endif
