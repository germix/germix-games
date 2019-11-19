////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RoundInfoPresentation
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/presentations/RoundInfoPresentation.h>
#include <src/ResourceManager.h>

RoundInfoPresentation::RoundInfoPresentation(const std::string& boss)
: bossName(boss)
, bossShown(false)
, typingMessage()
{
	typingMessage.init(30, res.findFont("font.2"), "OBJETIVO ENEMIGO");
}
RoundInfoPresentation::~RoundInfoPresentation()
{
}
bool RoundInfoPresentation::update(double dt)
{
	typingMessage.update(dt);
	if(!bossShown && typingMessage.isFinished())
	{
		bossShown = true;
		typingMessage.init(30, res.findFont("font.3"), bossName.c_str());
	}
	return typingMessage.isFinished();
}
void RoundInfoPresentation::render(Graphics* gr)
{
	typingMessage.render(gr);
}
