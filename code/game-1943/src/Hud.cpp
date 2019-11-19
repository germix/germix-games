////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Hud
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Hud.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/weapons/Weapon.h>

#include <mach/String.h>
#include <mach/Texture.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>

#define ENERGY_X			5
#define ENERGY_WIDTH		70
#define ENERGY_DY			5
#define ENERGY_HEIGHT		10

Hud::Hud(Scene* s)
: scene(s)
{
	font = res.findFont("font.1");
	heart = res.findTexture("heart");
	healthBarBg = res.findTexture("health_bar.bg");
	healthBarProgress = res.findTexture("health_bar.progress");
}
Hud::~Hud()
{
}
void Hud::update(double dt)
{
}
void Hud::render(Graphics* gr)
{
	Hero* hero = scene->getHero();

	render_score(gr, hero);
	render_energy(gr, hero);
	render_weapon(gr, hero);
}
void Hud::render_score(Graphics* gr, Hero* hero)
{
	int px = 5;
	int py = 5;
	int lives = hero->getLives();
	String score = String::fromInt(hero->getScore());
	
	for(int i = 0; i < lives; i++)
	{
		gr->drawTexture(heart, px + (i*heart->getWidth()), py);
	}
	py += heart->getHeight() + 5;
	
	font->render(gr, px, py, score.c_str());
}
void Hud::render_energy(Graphics* gr, Hero* hero)
{
	int x = ENERGY_X;
	int y = SCENE_HEIGHT - (ENERGY_HEIGHT + (ENERGY_DY*2) + font->fontHeight());
	
	int health = hero->getHealth();
	int maxHealth = hero->getMaxHealth();
	
	int pivot = (health*ENERGY_WIDTH)/maxHealth;
	
	gr->drawTexture(healthBarBg, x-1, y-1);
	if(pivot > 0)
	{
		gr->drawTexture(healthBarProgress,
			0,
			0,
			pivot,
			healthBarProgress->getHeight(),
			
			x,
			y,
			x+pivot,
			y+healthBarProgress->getHeight());
	}
}
void Hud::render_weapon(Graphics* gr, Hero* hero)
{
	const WeaponHandlerTemporary* twh = hero->getSecondaryWeapon();
	double rt = twh->getRemainingTime();
	
	if(rt > 0)
	{
		String weaponName = twh->getWeapon()->name();
		String remainingTime = String::fromInt((int)rt);
		
		//
		// Mostrar nombre del arma
		//
		font->render(gr,
			(ENERGY_WIDTH/2) - (font->textWidth(weaponName.c_str())/2),
			(SCENE_HEIGHT - (font->fontHeight() + ENERGY_DY)),
			weaponName.c_str());

		//
		// Mostrar tiempo restante del arma
		//
		font->render(gr,
			(SCENE_WIDTH/2) - (font->textWidth(remainingTime.c_str())/2),
			(SCENE_HEIGHT - (font->fontHeight() + ENERGY_DY)),
			remainingTime.c_str());
	}
}
