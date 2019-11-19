////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CampaignResult
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___CampaignResult_h___
#define ___CampaignResult_h___
#include <src/FadingHandler.h>

class Font;
class Texture;
class Graphics;

class CampaignResult
{
	enum EXIT_REASON
	{
		EXIT_REASON_TRY_AGAIN,
		EXIT_REASON_CLOSE_GAME,
	};
public:
	const char*		text;
	Font*			font2;
	Font*			font3;
	FadingHandler	fadingText;
	Texture*		winnerTexture;
	EXIT_REASON		exitReason;
public:
	CampaignResult(bool winnerMode);
	virtual ~CampaignResult();
public:
	bool update(double dt);
	void render(Graphics* gr);
	EXIT_REASON getExitReason() const { return exitReason; }
};

#endif
