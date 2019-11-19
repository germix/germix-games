////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MissionCompletedPresentation
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/presentations/MissionCompletedPresentation.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <mach/Color.h>
#include <mach/Graphics.h>

MissionCompletedPresentation::MissionCompletedPresentation(int percent)
: font(res.findFont("font.2"))
{
	char sz[256];
	sprintf(sz, "ENEMIGO: %d%% DESTRUIDO", percent);
	
	messages.push_back("MISION COMPLETADA");
	messages.push_back(sz);
	messages.push_back("RETORNANDO AL PORTAAVIONES");
	
	background = res.findTexture("missiom_completed");

	currentMessage = 0;
	typingMessage.init(30, font, messages[currentMessage].c_str());
}
MissionCompletedPresentation::~MissionCompletedPresentation()
{
}
bool MissionCompletedPresentation::update(double dt)
{
	typingMessage.update(dt);
	if(typingMessage.isFinished())
	{
		if(++currentMessage < messages.size())
		{
			typingMessage.init(30, font, messages[currentMessage].c_str());
		}
	}
	return typingMessage.isFinished();
}
void MissionCompletedPresentation::render(Graphics* gr)
{
	gr->drawTexture(background, 0, 0);
	typingMessage.render(gr);
}

