////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MissionHud
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/scene/MissionHud.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>

#include <mach/Texture.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>

MissionHud::MissionHud()
{
	font1 = res.findFont("Font.8x8.1");
	font2 = res.findFont("Font.8x8.2");
	fontNums = res.findFont("Font.Time");
	textureHud1 = res.findTexture("Hud.1");
	textureHud2 = res.findTexture("Hud.2");
	textureHeart = res.findTexture("Hud.Indicator.Heart");
	textureHostage = res.findTexture("Hud.Indicator.Hostage");
}
MissionHud::~MissionHud()
{
}
void MissionHud::update(Scene* scene, double dt)
{
}
void MissionHud::render(Scene* scene, Graphics* gr)
{
	Hero* hero = scene->getHero();
	if(hero)
	{
		renderTime(scene, gr, 2);
		renderScore(scene, gr, hero, 2);
		renderLives(scene, gr, hero, 0, 2);
		renderMunitions(scene, gr, hero, 64, 2);
	}
}
void MissionHud::renderTime(Scene* scene, Graphics* gr, int hudY)
{
	char sTime[10];
	itoa(scene->getTime(), sTime, 10);
	int  wTime = fontNums->textWidth(sTime);
	
	fontNums->render(gr, (SCREEN_WIDTH/2)-(wTime/2), hudY, sTime);
}
void MissionHud::renderScore(Scene* scene, Graphics* gr, Hero* hero, int hudY)
{
	int    y = hudY;
	int    x = SCREEN_WIDTH-8;
	int    hostages = hero->getHostages();
	for(int i = 0; i < hostages; i++)
	{
		gr->drawTexture(textureHostage, x, y);
		x -= 8;
	}
	y += 8+2;
	
	char   sScore[10];
	itoa(hero->getScore(), sScore, 10);
	int    wScore = font1->textWidth(sScore);
	
	font1->render(gr, SCREEN_WIDTH-wScore,  y, sScore);
}
void MissionHud::renderLives(Scene* scene, Graphics* gr, Hero* hero, int hudX, int hudY)
{
	int y = hudY+9;
	int x = hudX;
	int lives = hero->getLives();
	int health = hero->getHealth();
	
	gr->drawTexture(textureHud2, 0, 0, 8, 8, x, y, x+8, y+8);
	x += 8;
	for(int i = 0; i < Hero::MAX_HEALTH; i++)
	{
		if(!(i < health))
			gr->drawTexture(textureHud2, 8, 0, 8+16, 8, x, y, x+16, y+8);
		else
			gr->drawTexture(textureHud2, 24, 0, 24+16, 8, x, y, x+16, y+8);
		x += 16;
	}
	gr->drawTexture(textureHud2, 40, 0, 40+8, 8, x, y, x+8, y+8);
	x += 8;
	
	y = hudY+1;
	x = hudX+(((x-hudX)/2)-((textureHeart->getWidth()*lives)/2));
	for(int i = 0; i < lives; i++)
	{
		gr->drawTexture(textureHeart, x, y);
		x += textureHeart->getWidth();
	}
}
void MissionHud::renderMunitions(Scene* scene, Graphics* gr, Hero* hero, int hudX, int hudY)
{
	int arms = hero->getAmmo();
	int bombs = hero->getBombs();
	char sArms[10];
	char sBombs[10];
	
	gr->drawTexture(textureHud1, hudX, hudY);
	
	if(arms == -1)
	{
		sArms[0] = (char)137;
		sArms[1] = (char)138;
		sArms[2] = (char)139;
		sArms[3] = '\0';
	}
	else
	{
		itoa(arms, sArms, 10);
	}
	itoa(bombs, sBombs, 10);

	int wArms = font2->textWidth(sArms);
	font2->render(gr, hudX+((32/2)-(wArms/2)), hudY+9, sArms);
	int wBombs = font2->textWidth(sBombs);
	font2->render(gr, hudX+32+((32/2)-(wBombs/2)), hudY+9, sBombs);
}