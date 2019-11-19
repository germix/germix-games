////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Font
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Font_h___
#define ___Font_h___

class Texture;
class Graphics;

class Font
{
	Texture*	tex;
	int			width;
	int			height;
	int			lastChar;
	int			firstChar;

	friend class FontLoader;
public:
	Font();
	~Font();
public:
	int charWidth(char c);
	int textWidth(const char* s);
	int fontWidth();
	int fontHeight();
	void render(Graphics* gr, int x, int y, char ch, int alpha = 255);
	void render(Graphics* gr, int x, int y, const char* text, int alpha = 255);
};

#endif
