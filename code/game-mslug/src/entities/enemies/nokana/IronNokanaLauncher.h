////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IronNokanaLauncher | El rocket launcher del IronNokana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___IronNokanaLauncher_h___
#define ___IronNokanaLauncher_h___
#include <gamelib/TimeClock.h>

class Route;

class IronNokanaLauncher
{
	enum STATE
	{
		STATE_WAITING,
		STATE_LAUNCHING,
	};
	STATE			state;
	TimeClock		clock;
	int				launches;
	Route*			routes[2];
	int				currentRoute;
public:
	IronNokanaLauncher();
	~IronNokanaLauncher();
public:
	Route* update(double dt);
};

#endif
