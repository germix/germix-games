////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Debug
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Debug_h___
#define ___Debug_h___
#include <mach/Color.h>

class Debug
{
public:
	static const bool showHeroPos;
	static const bool showHeroRect;
	
	static const bool showBonusRects;
	static const Color colorBonusRects;
	
	static const bool showBulletRects;
	static const Color colorBulletRects;
	
	static const bool showFriendlyRects;
	static const Color colorFriendlyRects;
	
	static const bool showEnemyRects;
	static const Color colorEnemyRects;
	
	static const bool showShootableRect;
	static const Color colorShootableRect;
	// ...
	static const bool showCollisionRect;
	static const Color colorCollisionRect;
	
	static const bool enemyPassive;
};

#endif
