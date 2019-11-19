////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bird
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bird_h___
#define ___Bird_h___
#include <src/entities/Entity.h>

class Sprite;

class Bird : public Entity
{
	bool	alive;
	Sprite*	sprite;
public:
	Bird(Map* m, Scene* s, int x, int y);
	~Bird();
public:
	void update(double dt);
	void render(Graphics* gr);
	void kill();
	bool isAlive() const;
};

#endif
