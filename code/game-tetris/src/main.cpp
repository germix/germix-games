////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Tetris
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "GameTetris.h"
#include "Resources.h"
#include <mach/Machine.h>

void main()
{
	Machine().start(new GameTetris(), "Tetris", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
}