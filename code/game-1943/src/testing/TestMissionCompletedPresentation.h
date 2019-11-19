////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestMissionCompletedPresentation
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestMissionCompletedPresentation_h___
#define ___TestMissionCompletedPresentation_h___
#include <mach/Game.h>
#include <src/TypingMessage.h>

class Presentation;

class TestMissionCompletedPresentation : public Game
{
	Presentation* presentation;
public:
	TestMissionCompletedPresentation();
	~TestMissionCompletedPresentation();
public:
	virtual void init(Machine* mach);
	virtual void close(Machine* mach);
	virtual void update(Machine* mach, double dt);
	virtual void render(Machine* mach, Graphics* gr);
};

#endif
