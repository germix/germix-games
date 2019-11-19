////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SpecialAttack_Storm
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/attacks/SpecialAttack_Storm.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <mach/Color.h>
#include <mach/Texture.h>
#include <mach/Graphics.h>

#define ATTACK_STORM_ALPHA_MIN			50
#define ATTACK_STORM_ALPHA_MAX			180
#define ATTACK_STORM_ALPHA_TIME			(30.0/1000.0)

#define ATTACK_STORM_TEXTURES_MAX		3
#define ATTACK_STORM_TEXTURES_TIME		0.3

SpecialAttack_Storm::SpecialAttack_Storm(Scene* s)
{
	finished = false;
	
	fadingDir = +1;
	fadingAlpha = ATTACK_STORM_ALPHA_MIN;
	fadingClock.reset(ATTACK_STORM_ALPHA_TIME);
	
	textures[0] = res.findTexture("attack_storm.1");
	textures[1] = res.findTexture("attack_storm.2");
	textures[2] = res.findTexture("attack_storm.3");
	texturesIndex = 0;
	texturesClock.reset(ATTACK_STORM_TEXTURES_TIME);
	
	offsetFactor = (SCENE_HEIGHT - textures[0]->getHeight()) / (ATTACK_STORM_TEXTURES_MAX-1);
}
SpecialAttack_Storm::~SpecialAttack_Storm()
{
}
void SpecialAttack_Storm::update(double dt)
{
	if(fadingClock.update(dt))
	{
		fadingAlpha += fadingDir;
		if(fadingAlpha <= ATTACK_STORM_ALPHA_MIN)
		{
			fadingDir = +1;
			fadingAlpha = ATTACK_STORM_ALPHA_MIN;
		}
		else if(fadingAlpha >= ATTACK_STORM_ALPHA_MAX)
		{
			fadingDir = -1;
			fadingAlpha = ATTACK_STORM_ALPHA_MAX;
		}
	}
	if(texturesClock.update(dt))
	{
		texturesIndex++;
		if(texturesIndex >= ATTACK_STORM_TEXTURES_MAX)
		{
			finished = true;
		}
	}
}
void SpecialAttack_Storm::render(Graphics* gr) const
{
	if(!finished)
	{
		gr->fillRect(
				0,
				0,
				SCENE_WIDTH,
				SCENE_HEIGHT,
				Color(141, 182, 231, fadingAlpha));
		
		gr->drawTexture(textures[texturesIndex],
					0,
					(int)((texturesIndex) * offsetFactor));
	}
}
bool SpecialAttack_Storm::isFinished() const
{
	return finished;
}
int  SpecialAttack_Storm::damageForHero() const
{
	return 10;
}
int  SpecialAttack_Storm::damageForAircrafts() const
{
	return 10;
}
int  SpecialAttack_Storm::damageForBattleships() const
{
	return 0;
}
