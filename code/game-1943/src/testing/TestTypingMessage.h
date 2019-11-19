////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestTypingMessage
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestTypingMessage_h___
#define ___TestTypingMessage_h___
#include <mach/Game.h>
#include <src/TypingMessage.h>

class TestTypingMessage : public Game
{
	TypingMessage typingMessage;
public:
	TestTypingMessage();
	~TestTypingMessage();
public:
	virtual void init(Machine* mach);
	virtual void close(Machine* mach);
	virtual void update(Machine* mach, double dt);
	virtual void render(Machine* mach, Graphics* gr);
};

#endif
