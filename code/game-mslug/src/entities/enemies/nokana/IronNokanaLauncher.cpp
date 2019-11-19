////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IronNokanaLauncher | El rocket launcher del IronNokana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/nokana/IronNokanaLauncher.h>
#include <src/routes/Route.h>

#define TIME_WAITING	2.0
#define TIME_LAUCHING	0.4

IronNokanaLauncher::IronNokanaLauncher()
: state(STATE_LAUNCHING)
, clock(TIME_LAUCHING)
, launches(0)
, currentRoute(0)
{
	routes[0] = new Route(0, 0, "0,0 -50,0 -58,2 -64,4 -76,10 -90,24 -96,36 -98,42 -100,50 -100,62 -98,70 -96,76 -90,88 -76,102 -64,108 -50,112 24,112");
	routes[1] = new Route(0, 0, "0,0 -27,0 -32,-1 -36,-3 -39,-6 -41,-10 -42,-14 -42,-16 -41,-20 -39,-24 -36,-27 -32,-29 -28,-30 -26,-30 20,-30 84,-30 95,-29 100,-28 109,-25 121,-19 124,-17 129,-13 137,-5 141,0 143,3 149,15 152,24 153,29 154,40 154,43 153,53 152,58 149,67 143,79 141,82 137,87 129,95 124,99 121,101 109,107 100,110 95,111 84,112 67,112");
}
IronNokanaLauncher::~IronNokanaLauncher()
{
	delete routes[0];
	delete routes[1];
}
Route* IronNokanaLauncher::update(double dt)
{
	switch(state)
	{
		case STATE_WAITING:
			if(clock.update(dt))
			{
				state = STATE_LAUNCHING;
				clock.reset(TIME_LAUCHING);
			}
			break;
		case STATE_LAUNCHING:
			if(clock.update(dt))
			{
				Route* r = routes[currentRoute];
				
				if(++launches >= 2)
				{
					state = STATE_WAITING;
					clock.reset(TIME_WAITING);
					launches = 0;
					currentRoute = (++currentRoute&1);
				}
				return r;
			}
			break;
	}
	return null;
}
