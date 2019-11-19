////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SelectMapScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/SelectMapScreen.h>

#include <src/screens/PlayingScreen.h>

#include <windows.h>

SelectMapScreen::SelectMapScreen() : SelectScreen(27, "SELECCIONAR MAPA", "pacman/screens/select-map.tmx")
{
	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	char fname[MAX_PATH];
	
	if(INVALID_HANDLE_VALUE != (hFind = FindFirstFile("pacman/levels/*.tmx", &wfd)))
	{
		do
		{
			char* ptr = strrchr(wfd.cFileName, '.');
			int   len = ptr-wfd.cFileName;
			
			strncpy(fname, wfd.cFileName, len);
			fname[len] = '\0';
			
			list.push_back(fname);
		}
		while(FindNextFile(hFind, &wfd));
		FindClose(hFind);
	}
}
SelectMapScreen::~SelectMapScreen()
{
}
void SelectMapScreen::onExit()
{
	removable = true;
}
void SelectMapScreen::onEnter(const String& selection)
{
	nextScreen = new PlayingScreen((selection+".tmx").c_str());
}
void SelectMapScreen::onSelectionChanged(int index, const String& selection)
{
}


