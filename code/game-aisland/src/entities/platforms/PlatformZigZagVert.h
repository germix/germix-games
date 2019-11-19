////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformZigZagVert
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PlatformZigZagVert_h___
#define ___PlatformZigZagVert_h___
#include <src/entities/platforms/PlatformZigZag.h>

class PlatformZigZagVert : public PlatformZigZag
{
public:
	PlatformZigZagVert(Scene* s, double x, double y, const EntityParameters& params);
	~PlatformZigZagVert();
public:
	void update(double dt);
};

#endif
