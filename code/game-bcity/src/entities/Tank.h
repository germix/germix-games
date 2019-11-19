////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Tank
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Tank_h___
#define ___Tank_h___
#include <src/entities/Entity.h>
#include <src/base/Direction.h>

#include <mach/Point.h>

class Sprite;

class Tank : public Entity
{
public:
	//
	// Modelos de tanque
	//
	enum
	{
		TANK_MODEL_HERO_1 = 0,
		TANK_MODEL_HERO_2 = 1,
		TANK_MODEL_HERO_3 = 2,
		TANK_MODEL_HERO_4 = 3,
		TANK_MODEL_ENEMY_1 = 4,
		TANK_MODEL_ENEMY_2 = 5,
		TANK_MODEL_ENEMY_3 = 6,
		TANK_MODEL_ENEMY_4 = 7,
		MAX_TANK_MODELS = 8,
	};
	
	//
	// Colores de tanque
	//
	enum
	{
		TANK_COLOR_RED = 0,
		TANK_COLOR_GRAY = 1,
		TANK_COLOR_BROWN = 2,
		TANK_COLOR_GREEN = 3,
		MAX_TANK_COLORS = 4,
	};
protected:
	Direction		dir;
	int				tankModel;
	int				tankColor;
	Sprite*			sprite;
	int				animIndex;
public:
	Tank(Map* m, Scene* s, int x, int y, int model, int color);
	~Tank();
public:
	void render(Graphics* gr);
private:
	void updateSprite();
	int getSpriteIndex() const;
	bool moveVert(int dx, int dy);
	bool moveHorz(int dx, int dy);
protected:
	Point getShootPosition(Direction dir) const;
	bool move(int dx, int dy);
	void selectTankModel(int model);
	void selectTankColor(int color);
};

#endif

