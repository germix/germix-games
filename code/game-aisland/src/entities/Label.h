////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Label
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Label_h___
#define ___Label_h___
#include <src/Entity.h>

class Texture;

class Label : public Entity
{
	char			type;
	Texture*		texture;
public:
	Label(Scene* s, double x, double y, char type);
	~Label();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
