////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BombThrower | Controlador del lanzamiento de bombas
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___BombThrower_h___
#define ___BombThrower_h___

class Scene;

class BombThrower
{
	int count;
	bool infiniteBombs;
public:
	BombThrower(bool infinite);
	~BombThrower();
public:
	bool isEmpty() const { return !(count>0); }
	int  getCount() const { return count; }
	void reset();
	void addBombs(int bombs);
	bool throwBomb(Scene* scene, double posX, double posY, double velocityX, double velocityY);
};

#endif
