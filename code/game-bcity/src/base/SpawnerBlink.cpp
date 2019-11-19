////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SpawnerBlink
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/base/SpawnerBlink.h>
#include <src/Config.h>
#include <src/base/Sprite.h>

int SpawnerBlink::blinkFrames[] =
{
	0,1,2,3,2,1
};
#define maxBlinkFrames (sizeof(blinkFrames)/sizeof(blinkFrames[0]))

SpawnerBlink::SpawnerBlink()
{
	reset();
	blink = Config::blink;
}
SpawnerBlink::~SpawnerBlink()
{
}
void SpawnerBlink::reset()
{
	clock.reset(0.06);
	blinkIndex = 0;
	blinkCounter = 0;
}
bool SpawnerBlink::update(double dt)
{
	if(clock.update(dt))
	{
		if(++blinkIndex == maxBlinkFrames)
		{
			blinkIndex = 0;
			if(++blinkCounter >= 2)
			{
				return true;
			}
		}
	}
	return false;
}
void SpawnerBlink::render(Graphics* gr, int x, int y)
{
	blink->render(gr, x, y, blinkFrames[blinkIndex]);
}

