////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroSpriteCache
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroSpriteCache_h___
#define ___HeroSpriteCache_h___

class Sprite;
class SpriteSheet;

class HeroSpriteCache
{
public:
	int						weaponType;
	//
	// Sprites animaci�n primaria
	//
	Sprite*					legsIdle;
	Sprite*					legsJump;
	Sprite*					legsWalk;
	
	//
	// Sprites animaci�n secundaria (torax)
	//
	Sprite*					thoraxJump;
	Sprite*					thoraxIdle0;
	Sprite*					thoraxIdle30;
	Sprite*					thoraxIdle60;
	Sprite*					thoraxIdle90;
	Sprite*					thoraxIdleDown;
	Sprite*					thoraxBomb;
	Sprite*					thoraxKnife[2];
	
	//
	// Sprites animaci�n secundaria (agachado)
	//
	Sprite*					crouch;
	Sprite*					standup;
	
	Sprite*					crouchedBomb;
	Sprite*					crouchedKnife[2];
	Sprite*					crouchedWalk;
	Sprite*					crouchedIdle;
	Sprite*					crouchedIdleAttack1;
	Sprite*					crouchedIdleAttack2;
	
	Sprite*					winner;
public:
	HeroSpriteCache();
	~HeroSpriteCache();
public:
	void reset(SpriteSheet* sheet, int weaponType);
};

#endif
