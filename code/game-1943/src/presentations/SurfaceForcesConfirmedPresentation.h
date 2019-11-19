////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SurfaceForcesConfirmedPresentation
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SurfaceForcesConfirmedPresentation_h___
#define ___SurfaceForcesConfirmedPresentation_h___
#include <src/presentations/Presentation.h>
#include <src/TypingMessage.h>

#include <string>

class SurfaceForcesConfirmedPresentation : public Presentation
{
	bool firstPass;
	TypingMessage typingMessage;
public:
	SurfaceForcesConfirmedPresentation();
	virtual ~SurfaceForcesConfirmedPresentation();
public:
	bool update(double dt);
	void render(Graphics* gr);
};

#endif
