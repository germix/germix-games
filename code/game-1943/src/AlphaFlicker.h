#ifndef ___AlphaFlicker_h___
#define ___AlphaFlicker_h___
#include <gamelib/TimeClock.h>

class AlphaFlicker
{
	int			dir;
	int			step;
	int			alpha;
	TimeClock	clock;
public:
	AlphaFlicker(int s = 10, double ms = (1.0/1000.0)) : dir(-1), step(s), alpha(255), clock(ms)
	{
	}
	~AlphaFlicker()
	{
	}
public:
	int value() const
	{
		return alpha;
	}
	void update(double dt)
	{
		if(clock.update(dt))
		{
			alpha += dir*step;
			if(alpha <= 0)
			{
				dir = +1;
				alpha = 0;
			}
			else if(alpha >= 255)
			{
				dir = -1;
				alpha = 255;
			}
		}
	}
};

#endif
