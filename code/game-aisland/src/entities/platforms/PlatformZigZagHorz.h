////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformZigZagHorz
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PlatformZigZagHorz_h___
#define ___PlatformZigZagHorz_h___
#include <src/entities/platforms/PlatformZigZag.h>

class PlatformZigZagHorz : public PlatformZigZag
{
public:
	PlatformZigZagHorz(Scene* s, double x, double y, const EntityParameters& params);
	~PlatformZigZagHorz();
public:
	void update(double dt);
};

#endif
