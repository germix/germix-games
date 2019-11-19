////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SurfaceForcesConfirmedPresentation
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/presentations/SurfaceForcesConfirmedPresentation.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <mach/Color.h>
#include <mach/Graphics.h>

SurfaceForcesConfirmedPresentation::SurfaceForcesConfirmedPresentation()
: firstPass(true)
{
	typingMessage.init(30, res.findFont("font.2"), "CONTACTO VISUAL CON LAS FUERZAS\n DE LA SUPERFICIE");
}
SurfaceForcesConfirmedPresentation::~SurfaceForcesConfirmedPresentation()
{
}
bool SurfaceForcesConfirmedPresentation::update(double dt)
{
	typingMessage.update(dt);
	if(firstPass)
	{
		if(typingMessage.isFinished())
		{
			firstPass = false;
			typingMessage.init(30, res.findFont("font.2"), "COMENZANDO EL ATAQUE");
		}
	}
	return typingMessage.isFinished();
}
void SurfaceForcesConfirmedPresentation::render(Graphics* gr)
{
	gr->fillRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT, Color());
	typingMessage.render(gr);
}

