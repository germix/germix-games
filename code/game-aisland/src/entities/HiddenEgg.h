////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HiddenEgg
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HiddenEgg_h___
#define ___HiddenEgg_h___
#include <src/Entity.h>

#include <mach/String.h>

class HiddenEgg : public Entity
{
	String bonus;
	bool dropped;
public:
	HiddenEgg(Scene* s, double x, double y, const String& bonus);
	~HiddenEgg();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	Rectanglef getCollisionRectangle() const;
public:
	void drop();
};

#endif
