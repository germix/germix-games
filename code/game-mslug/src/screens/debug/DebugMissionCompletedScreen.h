////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugMissionCompletedScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___DebugMissionCompletedScreen_h___
#define ___DebugMissionCompletedScreen_h___
#include <gamelib/Screen.h>

#include <src/MissionCompleted.h>

class DebugMissionCompletedScreen : public Screen
{
	bool				removable;
	MissionCompleted	missionCompleted;
	Screen*				nextScreen;
public:
	DebugMissionCompletedScreen();
	~DebugMissionCompletedScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
