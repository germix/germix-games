////////////////////////////////////////////////////////////////////////////////////////////////////
//
// StringEdit
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/base/StringEdit.h>
#include <src/res/ResourceManager.h>

#include <mach/Keyboard.h>
#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib/Font.h>

StringEdit::StringEdit(int ___max)
: max(___max)
, text(null)
, font(res.findFont("Font.Black"))
, cursor(0)
, accepted(false)
, blinkingOn(false)
, blinkingClock(0.2)
, blinkingCount(0)
{
	text = new char[max+1];
	text[0] = 0;
}
StringEdit::~StringEdit()
{
	delete [] text;
}
void StringEdit::update(double dt)
{
	static struct
	{
		int k;
		char ch;
	}keys[] =
	{
		{ Key::LETTER_A, 'A' },
		{ Key::LETTER_B, 'B' },
		{ Key::LETTER_C, 'C' },
		{ Key::LETTER_D, 'D' },
		{ Key::LETTER_E, 'E' },
		{ Key::LETTER_F, 'F' },
		{ Key::LETTER_G, 'G' },
		{ Key::LETTER_H, 'H' },
		{ Key::LETTER_I, 'I' },
		{ Key::LETTER_J, 'J' },
		{ Key::LETTER_K, 'K' },
		{ Key::LETTER_L, 'L' },
		{ Key::LETTER_M, 'M' },
		{ Key::LETTER_N, 'N' },
		{ Key::LETTER_O, 'O' },
		{ Key::LETTER_P, 'P' },
		{ Key::LETTER_Q, 'Q' },
		{ Key::LETTER_R, 'R' },
		{ Key::LETTER_S, 'S' },
		{ Key::LETTER_T, 'T' },
		{ Key::LETTER_U, 'U' },
		{ Key::LETTER_V, 'V' },
		{ Key::LETTER_W, 'W' },
		{ Key::LETTER_X, 'X' },
		{ Key::LETTER_Y, 'Y' },
		{ Key::LETTER_Z, 'Z' },
		
		{ Key::NUMBER_0, '0' },
		{ Key::NUMBER_1, '1' },
		{ Key::NUMBER_2, '2' },
		{ Key::NUMBER_3, '3' },
		{ Key::NUMBER_4, '4' },
		{ Key::NUMBER_5, '5' },
		{ Key::NUMBER_6, '6' },
		{ Key::NUMBER_7, '7' },
		{ Key::NUMBER_8, '8' },
		{ Key::NUMBER_9, '9' },
		
		{ Key::KP_0, '0' },
		{ Key::KP_1, '1' },
		{ Key::KP_2, '2' },
		{ Key::KP_3, '3' },
		{ Key::KP_4, '4' },
		{ Key::KP_5, '5' },
		{ Key::KP_6, '6' },
		{ Key::KP_7, '7' },
		{ Key::KP_8, '8' },
		{ Key::KP_9, '9' },
		
		{ Key::MINUS, '-' },
		{ Key::KP_MINUS, '-' },
	};
	if(cursor > 0)
	{
		if(Keyboard::isPressed(Key::BACKSPACE))
		{
			text[--cursor] = 0;
		}
	}
	if(cursor < max)
	{
		for(int i = 0; i < (sizeof(keys)/sizeof(keys[0])); i++)
		{
			if(Keyboard::isPressed(keys[i].k))
			{
				text[cursor++] = keys[i].ch;
				break;
			}
		}
		text[cursor] = 0;
	}
	if(blinkingClock.update(dt))
	{
		if(blinkingCount < 10)
		{
			blinkingOn = !blinkingOn;
			if(accepted)
			{
				if(10 == ++blinkingCount)
				{
					blinkingOn = true;
				}
			}
		}
	}
}
void StringEdit::render(Graphics* gr, int x, int y)
{
	gr->fillRect(x-4,y-4, max*font->fontWidth()+8, font->fontHeight()+8, Color(255,255,255));
	if(accepted)
	{
		if(blinkingOn)
			font->render(gr, x, y, text);
	}
	else
	{
		font->render(gr, x, y, text);
		if(blinkingOn)
		{
			gr->fillRect(x+font->fontWidth()*cursor+1, y-1, 2, font->fontHeight()+2, Color());
		}
	}
}
int StringEdit::getWidth() const
{
	return max*font->fontWidth();
}
const String StringEdit::getString() const
{
	return text;
}
