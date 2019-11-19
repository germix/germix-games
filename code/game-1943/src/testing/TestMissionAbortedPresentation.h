////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestMissionAbortedPresentation
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestMissionAbortedPresentation_h___
#define ___TestMissionAbortedPresentation_h___
#include <mach/Game.h>
#include <src/TypingMessage.h>

class Presentation;

class TestMissionAbortedPresentation : public Game
{
	Presentation* presentation;
public:
	TestMissionAbortedPresentation();
	~TestMissionAbortedPresentation();
public:
	virtual void init(Machine* mach);
	virtual void close(Machine* mach);
	virtual void update(Machine* mach, double dt);
	virtual void render(Machine* mach, Graphics* gr);
};

#endif
