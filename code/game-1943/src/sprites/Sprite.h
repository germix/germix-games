////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Sprite
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Sprite_h___
#define ___Sprite_h___
#include <mach/Rectanglef.h>

class Vector2f;
class Texture;
class Graphics;

class Sprite
{
public:
	int			width;
	int			height;
	int			count;
	Texture*	texture;

	friend class SpriteSheet;
private:
	Sprite();
	~Sprite();
public:
	Rectanglef rect(const Vector2f& pos) const;
	void       render(Graphics* gr, double x, double y, int index);
	void       render(Graphics* gr, double x, double y, int index, int alpha);
};

#endif
