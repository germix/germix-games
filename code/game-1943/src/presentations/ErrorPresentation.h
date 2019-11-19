////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ErrorPresentation
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ErrorPresentation_h___
#define ___ErrorPresentation_h___
#include <src/presentations/Presentation.h>

#include <string>

class ErrorPresentation : public Presentation
{
public:
	ErrorPresentation(const std::string& msg);
	virtual ~ErrorPresentation();
public:
	bool update(double dt);
	void render(Graphics* gr);
};

#endif
