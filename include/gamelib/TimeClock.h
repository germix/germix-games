////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TimeClock
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TimeClock_h___
#define ___TimeClock_h___

class TimeClock
{
	double timeStep;
	double elapsedTime;
	double relativeTime;
public:
	TimeClock();
	TimeClock(double step);
public:
	double time();
	void   reset();
	void   reset(double step);
	bool   update(double deltaTime);
};

#endif
