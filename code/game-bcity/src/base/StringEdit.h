////////////////////////////////////////////////////////////////////////////////////////////////////
//
// StringEdit
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___StringEdit_h___
#define ___StringEdit_h___

#include <mach/String.h>

#include <gamelib/TimeClock.h>

class Font;
class Graphics;

class StringEdit
{
	int			max;
	char*		text;
	Font*		font;
	int			cursor;
	bool		accepted;
	bool		blinkingOn;
	TimeClock	blinkingClock;
	int			blinkingCount;
public:
	StringEdit(int max);
	~StringEdit();
public:
	void update(double dt);
	void render(Graphics* gr, int x, int y);
	
	int getWidth() const;
	const String getString() const;

};

#endif
