////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RoundInfoPresentation
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___RoundInfoPresentation_h___
#define ___RoundInfoPresentation_h___
#include <src/presentations/Presentation.h>
#include <src/TypingMessage.h>

class RoundInfoPresentation : public Presentation
{
	std::string			bossName;
	bool				bossShown;
	TypingMessage		typingMessage;
public:
	RoundInfoPresentation(const std::string& boss);
	virtual ~RoundInfoPresentation();
public:
	bool update(double dt);
	void render(Graphics* gr);
};

#endif
