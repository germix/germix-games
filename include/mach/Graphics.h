////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Graphics
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Graphics_h___
#define ___Graphics_h___

class Color;
class Texture;
class Rectangle;
class Rectanglef;

class Graphics
{
public:
	Graphics();
	~Graphics();
public:
	void clip(int x, int y, int w, int h);
	void translate(int dx, int dy);

	void drawLine(int x1, int y1, int x2, int y2, const Color& color);
	
//	void drawRect(const Rectangle& r, const Color& c);
	void drawRect(const Rectanglef& r, const Color& c);
	void drawRect(int x, int y, int w, int h, const Color& c);
	
	void fillRect(const Rectanglef& r, const Color& c);
	void fillRect(int x, int y, int w, int h, const Color& c);
	
	void drawTexture(Texture* texture, int x, int y);
	void drawTexture(Texture* texture, int sx1, int sy1, int sx2, int sy2, int dx1, int dy1, int dx2, int dy2);
	void drawTexture(Texture* texture, int x, int y, int alpha);
	void drawTexture(Texture* texture, int sx1, int sy1, int sx2, int sy2, int dx1, int dy1, int dx2, int dy2, int alpha);
	void drawTexture(Texture* texture, int sx1, int sy1, int sx2, int sy2, int dx1, int dy1, int dx2, int dy2, const Color& color);
};

#endif
