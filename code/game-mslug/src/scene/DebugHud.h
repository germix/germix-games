////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugHud
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___DebugHud_h___
#define ___DebugHud_h___
#include <src/scene/Hud.h>

class Font;

class DebugHud : public Hud
{
	Font* font;
public:
	DebugHud();
	~DebugHud();
public:
	virtual void update(Scene* scene, double dt);
	virtual void render(Scene* scene, Graphics* gr);
};

#endif
