////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SelectScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/SelectScreen.h>
#include <src/Config.h>
#include <src/resources/ResourceManager.h>
#include <src/tiled/TiledMap.h>

#include <mach/Math.h>
#include <mach/Color.h>
#include <mach/Graphics.h>
#include <mach/Keyboard.h>

#include <gamelib/Font.h>

SelectScreen::SelectScreen(int ___maxVisibleLines, const char* ___title, const char* tmxName)
: removable(false)
, nextScreen(null)
, title(___title)
, tiledMap(null)
, list()
, scrollPos(0)
, selectedItem(0)
, maxVisibleLines(___maxVisibleLines)
{
	tiledMap = new TiledMap(tmxName);
	
	font1 = res.findFont("Font.White");
	font2 = res.findFont("Font.Red");
	indicator = res.findTexture("ArrowRight");
}
SelectScreen::~SelectScreen()
{
	delete tiledMap;
}
Screen* SelectScreen::getNext()
{
	Screen* s = nextScreen;
	nextScreen = null;
	return s;
}
bool    SelectScreen::isRemovable()
{
	return removable;
}
void    SelectScreen::show(Machine* mach)
{
}
void    SelectScreen::hide(Machine* mach)
{
}
void    SelectScreen::update(Machine* mach, double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		onExit();
	}
	else if(Keyboard::isPressed(Key::UP))
	{
		select(selectedItem-1);
	}
	else if(Keyboard::isPressed(Key::DOWN))
	{
		select(selectedItem+1);
	}
	else if(Keyboard::isPressed(Key::HOME))
	{
		select(0);
	}
	else if(Keyboard::isPressed(Key::END))
	{
		select(list.size()-1);
	}
	else if(Keyboard::isPressed(Key::PAGEUP))
	{
		select(selectedItem-maxVisibleLines);
	}
	else if(Keyboard::isPressed(Key::PAGEDOWN))
	{
		select(selectedItem+maxVisibleLines);
	}
	else if(Keyboard::isPressed(Key::RETURN))
	{
		onEnter(list[selectedItem]);
	}
}
void    SelectScreen::render(Machine* mach, Graphics* gr)
{
	tiledMap->render(gr, 0, 0);
	
	//
	// Dibujar título
	//
	{
		int    titleX = MAP_WIDTH/2 - font1->textWidth(title)/2;
		int    titleY = 16;
		font1->render(gr, titleX, titleY, title);
	}
	//
	// Dibujar lista de mapas
	//
	{
		int itemY = 6*8;
		int arrowX = 8;
		
		for(unsigned int i = 0; i < Math::min(maxVisibleLines, list.size()); i++)
		{
			int itemX = arrowX+8+4;
			int itemIndex = i+scrollPos;
			String text = list[itemIndex].toUpper();
			
			if(itemIndex == selectedItem)
				font2->render(gr, itemX, itemY, text.c_str());
			else
				font1->render(gr, itemX, itemY, text.c_str());
			
			if(itemIndex == selectedItem)
			{
				gr->drawTexture(indicator, arrowX, itemY);
			}
			itemY += 8;
		}
	}
}
void SelectScreen::select(int index)
{
	unsigned int oldSelectedItem = selectedItem;
	
	if(index < 0)
		index = 0;
	else if(index >= list.size())
		index = list.size()-1;
	selectedItem = index;
	
	scrollToItem();
	if(selectedItem != oldSelectedItem)
	{
		onSelectionChanged(selectedItem, list[selectedItem]);
	}
}
void SelectScreen::scrollToItem()
{
	if(selectedItem < scrollPos)
		scrollPos = selectedItem;
	else if(selectedItem >= scrollPos+maxVisibleLines)
		scrollPos = selectedItem - maxVisibleLines+1;
}
