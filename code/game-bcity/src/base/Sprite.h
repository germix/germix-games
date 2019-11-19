////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Sprite
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Sprite_h___
#define ___Sprite_h___

class Texture;
class Graphics;

class Sprite
{
	Texture*		texture;
	int				startY;
	int				frameCount;
	int				frameWidth;
	int				frameHeight;
public:
	Sprite(Texture* tex, int count);
	Sprite(Texture* tex, int count, int startY, int frameHeight);
	~Sprite();
public:
	void render(Graphics* gr, int x, int y, int index) const;
	int getFrameCount() const;
	int getFrameWidth() const;
	int getFrameHeight() const;
};

#endif
