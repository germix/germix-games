////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MissionMapRenderable
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MissionMapRenderable_h___
#define ___MissionMapRenderable_h___

#include <vector>

#include <mach/Rectangle.h>

#include <gamelib/TimeClock.h>

class Texture;
class Graphics;

class MissionMapRenderable
{
public:
	enum
	{
		TYPE_FIXED,
		TYPE_PARALLAX,
	};
public:
	int						type;
	Rectangle				rect;
	std::vector<Texture*>	textures;
	unsigned int			currentTexture;
	TimeClock				clock;
public:
	MissionMapRenderable() : type(0), currentTexture(0), clock(0.04)
	{
	}
	~MissionMapRenderable()
	{
	}
public:
	void update(double dt);
	void render(Graphics* gr, int sx, int sy);
};

#endif
