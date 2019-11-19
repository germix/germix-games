////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SideFighterReinforcement
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SideFighterReinforcement_h___
#define ___SideFighterReinforcement_h___

class Hero;
class Scene;
class Graphics;
class SideFighter;
class EnemyBullet;

class SideFighterReinforcement
{
	enum
	{
		MAX_SIDE_FIGHTERS = 2,
	};
	SideFighter* fighters[MAX_SIDE_FIGHTERS];
public:
	SideFighterReinforcement(Scene* scene, Hero* hero);
	~SideFighterReinforcement();
public:
	bool update(double dt);
	void render(Graphics* gr);
	bool checkHit(EnemyBullet* bullet);
};

#endif
