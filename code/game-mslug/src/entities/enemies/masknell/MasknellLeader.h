////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MasknellLeader | Helicóptero Masknell líder de la flota
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MasknellLeader_h___
#define ___MasknellLeader_h___
#include <src/entities/enemies/masknell/Masknell.h>

#include <gamelib/TimeClock.h>

#include <gamelib-sprites/Sprite.h>

class MasknellLeader : public Masknell
{
	enum STATE
	{
		STATE_STARTING,
		STATE_SHOOTING,
		STATE_ROTATING,
	};
	STATE			state;
	TimeClock		clock;
	double			distanceToRotation;
public:
	MasknellLeader(Scene* scene, double x, double y, Route* r);
	~MasknellLeader();
public:
	void update(double dt);
};

#endif
