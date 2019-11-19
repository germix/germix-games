////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Hud
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Hud_h___
#define ___Hud_h___

class Hero;
class Scene;
class Font;
class Texture;
class Graphics;

class Hud
{
	Scene*			scene;
	Font*			font;
	Texture*		heart;
	Texture*		healthBarBg;
	Texture*		healthBarProgress;
public:
	Hud(Scene* s);
	~Hud();
public:
	void update(double dt);
	void render(Graphics* gr);
private:
	void render_score(Graphics* gr, Hero* hero);
	void render_energy(Graphics* gr, Hero* hero);
	void render_weapon(Graphics* gr, Hero* hero);
};

#endif
