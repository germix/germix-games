////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SpawnerBlink
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SpawnerBlink_h___
#define ___SpawnerBlink_h___

#include <gamelib/TimeClock.h>

class Sprite;
class Graphics;

class SpawnerBlink
{
	TimeClock	clock;
	Sprite*		blink;
	static int	blinkFrames[];
	int			blinkIndex;
	int			blinkCounter;
public:
	SpawnerBlink();
	~SpawnerBlink();
public:
	void reset();
	bool update(double dt);
	void render(Graphics* gr, int x, int y);
};

#endif

