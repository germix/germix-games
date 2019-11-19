////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MissionAbortedPresentation
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MissionAbortedPresentation_h___
#define ___MissionAbortedPresentation_h___
#include <src/presentations/Presentation.h>
#include <src/TypingMessage.h>

#include <string>
#include <vector>

class Font;

class MissionAbortedPresentation : public Presentation
{
	Font*						font;
	TypingMessage				typingMessage;
	std::vector<std::string>	messages;
	int							currentMessage;
public:
	MissionAbortedPresentation(int percent);
	virtual ~MissionAbortedPresentation();
public:
	bool update(double dt);
	void render(Graphics* gr);
};

#endif
