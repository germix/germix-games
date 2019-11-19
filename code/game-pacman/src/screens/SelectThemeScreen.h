////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SelectThemeScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SelectThemeScreen_h___
#define ___SelectThemeScreen_h___
#include <src/screens/SelectScreen.h>

class SelectThemeScreen : public SelectScreen
{
	std::string oldTilesetName;
public:
	SelectThemeScreen();
	~SelectThemeScreen();
protected:
	virtual void onExit();
	virtual void onEnter(const String& selection);
	virtual void onSelectionChanged(int index, const String& selection);
};

#endif
