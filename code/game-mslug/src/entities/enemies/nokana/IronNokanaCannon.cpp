////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IronNokanaCannon | Cañón de IronNokana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/nokana/IronNokanaCannon.h>

#define MAX_CANNON_SHOTS		3		// Tres disparos por ráfaga
#define MAX_CANNON_FRAMES		5
#define TIME_FOR_WAITING		2
#define TIME_FOR_SHOOTING		0.07

IronNokanaCannon::IronNokanaCannon()
: state(STATE_STOPPED)
, clock()
, frame(0)
, shots(0)
{
}
IronNokanaCannon::~IronNokanaCannon()
{
}
void IronNokanaCannon::init()
{
	if(state == STATE_STOPPED)
	{
		state = STATE_PREPARING;
	}
}
void IronNokanaCannon::stop()
{
	state = STATE_STOPPED;
	frame = 0;
	clock = null;
}
bool IronNokanaCannon::update(double dt)
{
	bool shootNow = false;
	
	switch(state)
	{
		case STATE_STOPPED:
			break;
		case STATE_PREPARING:
			gotoShootingState();
			break;
		case STATE_WAITING:
			if(clock.update(dt))
			{
				gotoShootingState();
			}
			break;
		case STATE_SHOOTING:
			if(clock.update(dt))
			{
				frame++;
				if(frame >= MAX_CANNON_FRAMES)
				{
					frame = 0;
					shootNow = true;
				}
			}
			break;
	}
	if(shootNow)
	{
		shots++;
		if(shots >= MAX_CANNON_SHOTS)
		{
			gotoWaitingState();
		}
	}
	return shootNow;
}
int IronNokanaCannon::renderableFrame() const
{
	return frame;
}
void IronNokanaCannon::gotoWaitingState()
{
	state = STATE_WAITING;
	frame = 0;
	clock.reset(TIME_FOR_WAITING);
}
void IronNokanaCannon::gotoShootingState()
{
	state = STATE_SHOOTING;
	frame = 0;
	shots = 0;
	clock.reset(TIME_FOR_SHOOTING);
}
