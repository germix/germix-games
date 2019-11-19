////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MissionCompletedPresentation
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MissionCompletedPresentation_h___
#define ___MissionCompletedPresentation_h___
#include <src/presentations/Presentation.h>
#include <src/TypingMessage.h>

#include <string>
#include <vector>

class Font;
class Texture;

class MissionCompletedPresentation : public Presentation
{
	Font*						font;
	TypingMessage				typingMessage;
	std::vector<std::string>	messages;
	int							currentMessage;
	Texture*					background;
public:
	MissionCompletedPresentation(int percent);
	virtual ~MissionCompletedPresentation();
public:
	bool update(double dt);
	void render(Graphics* gr);
};

#endif
