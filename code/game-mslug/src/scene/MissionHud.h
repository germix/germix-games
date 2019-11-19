////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MissionHud
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MissionHud_h___
#define ___MissionHud_h___
#include <src/scene/Hud.h>

class Hero;

class Font;
class Texture;

class MissionHud : public Hud
{
	Font*			font1;
	Font*			font2;
	Font*			fontNums;
	Texture*		textureHud1;
	Texture*		textureHud2;
	Texture*		textureHeart;
	Texture*		textureHostage;
public:
	MissionHud();
	~MissionHud();
public:
	virtual void update(Scene* scene, double dt);
	virtual void render(Scene* scene, Graphics* gr);
private:
	//
	// Dibujar tiempo
	//
	void renderTime(Scene* scene, Graphics* gr, int hudY);

	//
	// Dibujar puntaje
	//
	void renderScore(Scene* scene, Graphics* gr, Hero* hero, int hudY);

	//
	// Dibujar barra de salud y vidas
	//
	void renderLives(Scene* scene, Graphics* gr, Hero* hero, int hudX, int hudY);

	//
	// Dibujar cantidad de munición y bombas
	//
	void renderMunitions(Scene* scene, Graphics* gr, Hero* hero, int hudX, int hudY);
};

#endif
