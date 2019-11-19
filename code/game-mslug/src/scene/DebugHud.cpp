////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugHud
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/scene/DebugHud.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/Weapon.h>

#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>

#define HUD_TOP			0
#define HUD_BOTTOM		20

DebugHud::DebugHud()
{
	font = res.findFont("Font.8x8.1");
}
DebugHud::~DebugHud()
{
}
void DebugHud::update(Scene* scene, double dt)
{
}
void DebugHud::render(Scene* scene, Graphics* gr)
{
	int sw = SCREEN_WIDTH;
#if 1
	int sh = HUD_BOTTOM;
	int ry = SCREEN_HEIGHT-HUD_BOTTOM;
#else
	int sh = SCREEN_HEIGHT-HUD_BOTTOM;
	int ry = HUD_TOP+sh+HUD_BOTTOM;
#endif
	char text[32];
	Hero* hero = scene->getHero();
	Rectanglef camera = scene->getCameraRect();
	
	gr->fillRect(0, ry, sw, HUD_BOTTOM, Color());
	
	if(hero == null)
	{
		return;
	}
	//
	// Tipo de arma
	//
	sprintf(text, "Arma: %s", hero->getWeapon()->name());
	font->render(gr, 0+2, ry+2, text);
	
	//
	// Ángulo de disparo
	//
	sprintf(text, "Angulo: %d", (int)hero->getShotAngle());
	font->render(gr, 0+2, ry+2 + font->fontHeight(), text);

	//
	// Cantidad de balas y bombas
	//
	sprintf(text, "Ammo=%d", (int)hero->getAmmo());
	font->render(gr, 0+200, ry+2, text);
	sprintf(text, "Bombs=%d", (int)hero->getBombs());
	font->render(gr, 0+200, ry+2 + font->fontHeight(), text);
	
	//
	// Posición de la cámara
	//
//	sprintf(text, "Camera=(%d,%d)", (int)camera.getMinX(), (int)camera.getMaxX());
//	font->render(gr, 0+180, ry+2, text);
}
