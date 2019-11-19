////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestEntities
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestEntities_h___
#define ___TestEntities_h___
#include <mach/Game.h>

#include <src/Scene.h>
#include <src/HeroInfo.h>
#include <src/entities/hero/Hero.h>

class Hero;
class Scene;

class TestEntities : public Game
{
protected:
	HeroInfo	info;
	Hero*		hero;
	Scene*		scene;
	int			weapon;
public:
	TestEntities();
	~TestEntities();
public:
	virtual void init(Machine* mach);
	virtual void close(Machine* mach);
	virtual void update(Machine* mach, double dt);
	virtual void render(Machine* mach, Graphics* gr);
protected:
	virtual void create() = 0;
	virtual void firstCreate()
	{
		create();
	}
};

#endif
