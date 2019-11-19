////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Battle City
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Config.h>
#include <src/GameBattleCity.h>

#include <mach/Machine.h>

#if 0
int main()
#else
#include <windows.h>
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	Machine().start(new GameBattleCity(), "Battle City", SCREEN_WIDTH, SCREEN_HEIGHT, 2, 16);
	return 0;
}
