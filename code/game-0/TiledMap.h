#ifndef ___TiledMap_h___
#define ___TiledMap_h___

class Graphics;

class TiledMap
{
public:
	int*	tiles;
	int		width;
	int		height;
public:
	TiledMap(const char* fileName);
	~TiledMap();
public:
	void draw(Graphics* gr, int x, int y, int w, int h);
};

#endif
