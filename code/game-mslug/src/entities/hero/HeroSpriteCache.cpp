////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroSpriteCache
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/HeroSpriteCache.h>

#include <gamelib-sprites/SpriteSheet.h>

static Sprite* getSprite(SpriteSheet* sheet, const char* s1, const char* type = "", const char* s2 = "")
{
	std::string name;
	
	name += s1;
	name += type;
	name += s2;
	return sheet->getSprite(name.c_str());
}
HeroSpriteCache::HeroSpriteCache()
: weaponType(-1)
, legsIdle(null)
, legsJump(null)
, legsWalk(null)
, thoraxJump(null)
, thoraxIdle0(null)
, thoraxIdle30(null)
, thoraxIdle60(null)
, thoraxIdle90(null)
, thoraxIdleDown(null)
, thoraxBomb(null)
//, thoraxKnife
, crouch(null)
, standup(null)
, crouchedBomb(null)
//, crouchedKnife
, crouchedWalk(null)
, crouchedIdle(null)
, crouchedIdleAttack1(null)
, crouchedIdleAttack2(null)
, winner(null)
{
	thoraxKnife[0] = null;
	thoraxKnife[1] = null;
	crouchedKnife[0] = null;
	crouchedKnife[1] = null;
}
HeroSpriteCache::~HeroSpriteCache()
{
}
void HeroSpriteCache::reset(SpriteSheet* sheet, int wt)
{
	if(weaponType != wt)
	{
		const char* type = (wt == 0) ? "(P)" : "(H)";
		
		weaponType = wt;
		
		//
		// Animación primaria
		//
		legsIdle				= getSprite(sheet, "legs-idle");
		legsJump				= getSprite(sheet, "legs-jump");
		legsWalk				= getSprite(sheet, "legs-walk");
		
		//
		// Sprites animación secundaria (torax)
		//
		thoraxJump				= getSprite(sheet, "thorax", type, "-jump");
		thoraxIdle0				= getSprite(sheet, "thorax", type, "-idle(0)");
		thoraxIdle30			= getSprite(sheet, "thorax", type, "-idle(30)");
		thoraxIdle60			= getSprite(sheet, "thorax", type, "-idle(60)");
		thoraxIdle90			= getSprite(sheet, "thorax", type, "-idle(90)");
		thoraxIdleDown			= getSprite(sheet, "thorax", type, "-idle(down)");
		thoraxBomb				= getSprite(sheet, "thorax", type, "-bomb");
		thoraxKnife[0]			= getSprite(sheet, "thorax", type, "-knife1");
		thoraxKnife[1]			= getSprite(sheet, "thorax", type, "-knife2");
		
		//
		// Sprites animación secundaria (agachado)
		//
		crouch					= getSprite(sheet, "crouch", type);
		standup					= getSprite(sheet, "standup", type);
		crouchedBomb			= getSprite(sheet, "crouched", type, "-bomb");
		crouchedKnife[0]		= getSprite(sheet, "crouched", type, "-knife1");
		crouchedKnife[1]		= getSprite(sheet, "crouched", type, "-knife2");
		crouchedWalk			= getSprite(sheet, "crouched", type, "-walk");
		crouchedIdle			= getSprite(sheet, "crouched", type, "-idle1");
		crouchedIdleAttack1		= getSprite(sheet, "crouched", type, "-idle2");
		crouchedIdleAttack2		= getSprite(sheet, "crouched", type, "-idle3");
		
		// ...
		winner					= getSprite(sheet, "winner", type);
	}
}
