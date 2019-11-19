////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MissionAbortedPresentation
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/presentations/MissionAbortedPresentation.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <mach/Color.h>
#include <mach/Graphics.h>

MissionAbortedPresentation::MissionAbortedPresentation(int percent)
: font(res.findFont("font.2"))
{
	char sz[256];
	sprintf(sz, "ENEMIGO: %d%% DESTRUIDO", percent);
	
	messages.push_back("ATAQUE INICIAL FRACASADO");
	messages.push_back("MISION ABORTADA");
	messages.push_back(sz);
	
	currentMessage = 0;
	typingMessage.init(30, font, messages[currentMessage].c_str());
}
MissionAbortedPresentation::~MissionAbortedPresentation()
{
}
bool MissionAbortedPresentation::update(double dt)
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
void MissionAbortedPresentation::render(Graphics* gr)
{
	gr->fillRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT, Color());
	typingMessage.render(gr);
}

