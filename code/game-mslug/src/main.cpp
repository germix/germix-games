////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Metal Slug
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Config.h>
#include <src/GameMetalSlug.h>

#include <mach/Machine.h>

#include <time.h>

#if 0
int main()
#else
#include <windows.h>
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	Machine().start(new GameMetalSlug(), "Metal Slug", SCREEN_WIDTH, SCREEN_HEIGHT, 3, 0);
//	Machine().start(new GameMetalSlug(), "Metal Slug", SCREEN_WIDTH, SCREEN_HEIGHT, 3, 24);
	return 0;
}
