////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SelectMapScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SelectMapScreen_h___
#define ___SelectMapScreen_h___
#include <src/screens/SelectScreen.h>

class SelectMapScreen : public SelectScreen
{
public:
	SelectMapScreen();
	~SelectMapScreen();
protected:
	virtual void onExit();
	virtual void onEnter(const String& selection);
	virtual void onSelectionChanged(int index, const String& selection);
};

#endif
