////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Pacman
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Config.h>
#include <src/GamePacman.h>

#include <mach/Machine.h>

#if 0
int main()
#else
#include <windows.h>
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	Machine().start(new GamePacman(), "Pacman", SCREEN_WIDTH, SCREEN_HEIGHT, 2, MAX_MIXCHANNELS);
	return 0;
}
