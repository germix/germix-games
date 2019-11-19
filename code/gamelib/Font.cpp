////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Font
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <mach/Texture.h>
#include <mach/Graphics.h>
#include <gamelib/Font.h>

#include <string.h>

Font::Font()
	: tex(0)
	, width(0)
	, height(0)
	, lastChar(0)
	, firstChar(0)
{
}
Font::~Font()
{
	if(tex)
		delete tex;
}
int Font::charWidth(char c)
{
	return width;
}
int Font::textWidth(const char* s)
{
	return (strlen(s) * width);
}
int Font::fontWidth()
{
	return width;
}
int Font::fontHeight()
{
	return height;
}
void Font::render(Graphics* gr, int x, int y, char ch, int alpha)
{
	if(firstChar <= (unsigned char)ch && (unsigned char)ch <= lastChar)
	{
		int ich = ((unsigned char)ch-firstChar);
		
		gr->drawTexture
		(
			tex,
			// Coordenadas de origen
			ich * width,
			0,
			(ich * width) + width,
			0 + height,
			// Coordenadas de destino
			x,
			y,
			x + width,
			y + height,
			// Alpha
			alpha
		);
	}
}
void Font::render(Graphics* gr, int x, int y, const char* text, int alpha)
{
	int i;
	int len = strlen(text);
	for(i = 0; i < len; i++)
	{
		unsigned char ch = text[i];
		if(firstChar <= ch && ch <= lastChar)
		{
			int ich = (ch-firstChar);
			
			gr->drawTexture
			(
				tex,
				// Coordenadas de origen
				ich * width,
				0,
				(ich * width) + width,
				0 + height,
				// Coordenadas de destino
				x,
				y,
				x + width,
				y + height,
				// Alpha
				alpha
			);
			
			x += width;
		}
	}
}
