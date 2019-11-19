////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestScene
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestScene_h___
#define ___TestScene_h___
#include <mach/Game.h>

#include <src/HeroInfo.h>

class Scene;

class TestScene : public Game
{
	HeroInfo	info;
	Scene*		scene;
	int			area;
	int			round;
	int			weapon;
public:
	TestScene(int area, int round);
	~TestScene();
public:
	virtual void init(Machine* mach);
	virtual void close(Machine* mach);
	virtual void update(Machine* mach, double dt);
	virtual void render(Machine* mach, Graphics* gr);
};

#endif

