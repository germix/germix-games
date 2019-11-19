////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformZigZag
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PlatformZigZag_h___
#define ___PlatformZigZag_h___
#include <src/entities/platforms/Platform.h>

class PlatformZigZag : public Platform
{
protected:
	int dir;
	double min;
	double max;
	double position;
public:
	PlatformZigZag(Scene* s, double x, double y, const EntityParameters& params, int dir, int min, int max, double pos);
	~PlatformZigZag();
public:
	void update(double dt);
};

#endif
