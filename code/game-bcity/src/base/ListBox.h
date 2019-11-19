////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ListBox
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ListBox_h___
#define ___ListBox_h___

#include <vector>
#include <mach/Color.h>
#include <mach/String.h>

class Font;
class Graphics;

class ListBox
{
	int						px;
	int						py;
	Font*					fontNormal;
	Font*					fontSelected;
	std::vector<String>		list;
	int						columns;
	int						scrollPos;
	int						selectedIndex;
	int						maxVisibleLines;
	Color					backgroundColor;
public:
	ListBox(int x, int y, int cols, int rows, const std::vector<String>& l, const Color& background = Color(0,0,0,0));
	~ListBox();
public:
	void clear();
	void append(const std::string& s);
	void update(double dt);
	void render(Graphics* gr);
	
	int getSelectedIndex() const
	{
		return selectedIndex;
	}
	String getSelectedString() const
	{
		return list[selectedIndex];
	}
private:
	void select(int index);
	void scrollToItem();
};

#endif
