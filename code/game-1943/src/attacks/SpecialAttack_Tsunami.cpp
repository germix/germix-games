////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SpecialAttack_Tsunami
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/attacks/SpecialAttack_Tsunami.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <mach/Color.h>
#include <mach/Texture.h>
#include <mach/Graphics.h>

#define ATTACK_TSUNAMI_VELOCITY			800.0

#define ATTACK_TSUNAMI_ALPHA_MIN		50
#define ATTACK_TSUNAMI_ALPHA_MAX		100
#define ATTACK_TSUNAMI_ALPHA_TIME		20.0

SpecialAttack_Tsunami::SpecialAttack_Tsunami(Scene* s)
{
	finished = false;

	fadingDir = +1;
	fadingAlpha = ATTACK_TSUNAMI_ALPHA_MIN;
	fadingClock.reset(ATTACK_TSUNAMI_ALPHA_TIME);

	tsunamiOffset = 0;
	tsunamiTexture = res.findTexture("attack_tsunami");
}
SpecialAttack_Tsunami::~SpecialAttack_Tsunami()
{
}
void SpecialAttack_Tsunami::update(double dt)
{
	if(fadingClock.update(dt))
	{
		fadingAlpha += fadingDir;
		if(fadingAlpha <= ATTACK_TSUNAMI_ALPHA_MIN)
		{
			fadingDir = +1;
			fadingAlpha = ATTACK_TSUNAMI_ALPHA_MIN;
		}
		else if(fadingAlpha >= ATTACK_TSUNAMI_ALPHA_MAX)
		{
			fadingDir = -1;
			fadingAlpha = ATTACK_TSUNAMI_ALPHA_MAX;
		}
	}
	tsunamiOffset -= ATTACK_TSUNAMI_VELOCITY*dt;
	if((int)tsunamiOffset+tsunamiTexture->getHeight() < 0)
	{
		finished = true;
	}
}
void SpecialAttack_Tsunami::render(Graphics* gr) const
{
	gr->drawTexture(tsunamiTexture, 0, (int)tsunamiOffset, 178);
	
	gr->fillRect(SCENE_X, SCENE_Y, SCENE_WIDTH, SCENE_HEIGHT, Color(101, 182, 231, fadingAlpha));
}
bool SpecialAttack_Tsunami::isFinished() const
{
	return finished;
}
int  SpecialAttack_Tsunami::damageForHero() const
{
	return 8;
}
int  SpecialAttack_Tsunami::damageForAircrafts() const
{
	return 2;
}
int  SpecialAttack_Tsunami::damageForBattleships() const
{
	return 15;
}
