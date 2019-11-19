////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ListBox
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/base/ListBox.h>
#include <src/Config.h>
#include <src/res/ResourceManager.h>
#include <src/base/Sprite.h>

#include <mach/Math.h>
#include <mach/Keyboard.h>
#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>

ListBox::ListBox(int x, int y, int cols, int rows, const std::vector<String>& l, const Color& background)
	: px(x)
	, py(y)
	, list(l)
	, fontNormal(res.findFont("Font.White"))
	, fontSelected(res.findFont("Font.Red"))
	, columns(cols)
	, scrollPos(0)
	, selectedIndex(0)
	, maxVisibleLines(rows)
	, backgroundColor(background)
{
}
ListBox::~ListBox()
{
}
void ListBox::clear()
{
	list.clear();
}
void ListBox::append(const std::string& s)
{
	list.push_back(s);
}
void ListBox::update(double dt)
{
	if(Keyboard::isPressed(Key::UP))
	{
		select(selectedIndex-1);
	}
	else if(Keyboard::isPressed(Key::DOWN))
	{
		select(selectedIndex+1);
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
		select(selectedIndex-maxVisibleLines);
	}
	else if(Keyboard::isPressed(Key::PAGEDOWN))
	{
		select(selectedIndex+maxVisibleLines);
	}
}
void ListBox::render(Graphics* gr)
{
	int itemY = py;
	int arrowX = px;
	
	if(backgroundColor.alpha() > 0)
	{
		gr->fillRect(
			px-4,
			py-4,
			columns*fontNormal->fontWidth() + 8,
			maxVisibleLines*fontNormal->fontHeight() + 8,
			backgroundColor);
	}
	
	for(int i = 0; i < Math::min(maxVisibleLines, (int)list.size()); i++)
	{
		int itemX = arrowX + 8 + 4;
		int itemIndex = i+scrollPos;
		String mapName = list[itemIndex].toUpper();
		
		if(itemIndex == selectedIndex)
		{
			Config::arrows->render(gr, arrowX, itemY, 1);
		}
		if(itemIndex == selectedIndex)
			fontSelected->render(gr, itemX, itemY, mapName.c_str());
		else
			fontNormal->render(gr, itemX, itemY, mapName.c_str());
		
		itemY += 8;
	}
}
void ListBox::select(int index)
{
	int oldSelectedItem = selectedIndex;
	
	selectedIndex = index;
	if(selectedIndex < 0)
		selectedIndex = 0;
	else if(selectedIndex >= (int)list.size())
		selectedIndex = list.size()-1;
	
	scrollToItem();
}
void ListBox::scrollToItem()
{
	if(selectedIndex < scrollPos)
		scrollPos = selectedIndex;
	else if(selectedIndex >= scrollPos+maxVisibleLines)
		scrollPos = selectedIndex - maxVisibleLines+1;
}
