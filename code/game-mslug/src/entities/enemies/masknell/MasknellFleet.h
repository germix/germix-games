////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MasknellFleet | Flota de Masknell's
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MasknellFleet_h___
#define ___MasknellFleet_h___
#include <src/scene/Entity.h>
//#include <gamelib/TimeClock.h>
#include <vector>

class Route;
class Masknell;
class MasknellLeader;
class MasknellSubordinate;

class MasknellFleet : public Entity
{
	Route*								route;
//	TimeClock							clock;
	MasknellLeader*						leader;
	std::vector<MasknellSubordinate*>	subordinates;
	Masknell*							lastMasknellCreated;
public:
	MasknellFleet(Scene* scene, double x, double y);
	~MasknellFleet();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
