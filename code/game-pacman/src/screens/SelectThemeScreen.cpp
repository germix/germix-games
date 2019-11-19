////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SelectThemeScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/SelectThemeScreen.h>
#include <src/Config.h>
#include <src/resources/ResourceManager.h>

#include <windows.h>

SelectThemeScreen::SelectThemeScreen() : SelectScreen(12, "SELECCIONAR TEMA", "pacman/screens/select-theme.tmx")
{
	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	char fname[MAX_PATH];
	
	// ...
	oldTilesetName = Config::currentTilesetName;
	
	//
	// Cargar nombres de tilesets
	//
	if(INVALID_HANDLE_VALUE != (hFind = FindFirstFile("pacman/images/tilesets/*.png", &wfd)))
	{
		do
		{
			char* ptr = strchr(wfd.cFileName, '.');
			int   len = ptr-wfd.cFileName;
			
			strncpy(fname, wfd.cFileName, len);
			fname[len] = '\0';
			
			list.push_back(fname);
		}
		while(FindNextFile(hFind, &wfd));
		FindClose(hFind);
	}
	//
	// Seleccionar item
	//
	for(unsigned int i = 0; i < list.size(); i++)
	{
		if(list[i] == oldTilesetName)
		{
			selectedItem = i;
			break;
		}
	}
	scrollToItem();
}
SelectThemeScreen::~SelectThemeScreen()
{
}
void SelectThemeScreen::onExit()
{
	Config::currentTileset = res.findTexture(oldTilesetName.c_str());
	removable = true;
}
void SelectThemeScreen::onEnter(const String& selection)
{
	Config::currentTilesetName = selection;
	removable = true;
}
void SelectThemeScreen::onSelectionChanged(int index, const String& selection)
{
	Config::currentTileset = res.findTexture(selection.c_str());
}

