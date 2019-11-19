////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CampaignResult
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/CampaignResult.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <mach/Mixer.h>
#include <mach/Color.h>
#include <mach/Graphics.h>
#include <mach/Keyboard.h>

#include <gamelib/Font.h>

CampaignResult::CampaignResult(bool winnerMode)
: text(winnerMode ? "JUEGO GANADO" : "GAME OVER")
, font2(null)
, font3(null)
, fadingText(3.0, 255)
, winnerTexture(null)
{
	if(!winnerMode)
	{
		font2 = res.findFont("font.2");
		font3 = res.findFont("font.3");
		Mixer::playMusic(res.findMusic("loser"));
	}
	else
	{
		font2 = res.findFont("font.2");
		font3 = res.findFont("font.4");
		winnerTexture = res.findTexture("winner");
		Mixer::playMusic(res.findMusic("winner"));
	}
}
CampaignResult::~CampaignResult()
{
	Mixer::halt();
}
bool CampaignResult::update(double dt)
{
	if(Keyboard::isPressed(Key::RETURN))
	{
		exitReason = EXIT_REASON_TRY_AGAIN;
		return true;
	}
	else if(Keyboard::isPressed(Key::ESCAPE))
	{
		exitReason = EXIT_REASON_CLOSE_GAME;
		return true;
	}
	if(!fadingText.update(dt))
	{
		fadingText.reset(!fadingText.isInverted());
	}
	return false;
}
void CampaignResult::render(Graphics* gr)
{
	if(winnerTexture)
	{
		gr->drawTexture(winnerTexture, 0, 0);
	}
	else
	{
		gr->fillRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT, Color(128,128,128));
	}
	const char* lblPlayAgain = "<ENTER> JUGAR OTRA VEZ";
	const char* lblExitOfGame = "<ESCAPE> SALIR DEL JUEGO";

	font3->render(gr, SCENE_WIDTH/2 - font3->textWidth(text)/2, 100, text, fadingText.value());
	font2->render(gr, SCENE_WIDTH/2 - font2->textWidth(lblPlayAgain)/2, 175, lblPlayAgain);
	font2->render(gr, SCENE_WIDTH/2 - font2->textWidth(lblExitOfGame)/2, 200, lblExitOfGame);
}
