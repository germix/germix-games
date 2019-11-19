////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformMoveTo
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___PlatformMoveTo_h___
#define ___PlatformMoveTo_h___
#include <src/entities/platforms/Platform.h>

class PlatformMoveTo : public Platform
{
	enum MODE
	{
		MODE_UP,
		MODE_DOWN,
		MODE_LEFT,
		MODE_RIGHT,
		MODE_STOPPED,
		MODE_UNKNOWN,
	};
	int				to;
	MODE			mode;
	bool			active;
public:
	PlatformMoveTo(Scene* s, double x, double y, const EntityParameters& params);
	~PlatformMoveTo();
public:
	void update(double dt);
};

#endif
