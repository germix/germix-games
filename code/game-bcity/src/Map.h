////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Map
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Map_h___
#define ___Map_h___
#include <mach/Rectangle.h>

#include <vector>

#include <gamelib/TimeClock.h>

class Graphics;

class TmxMap;

class Map
{
	int					mapWidth;
	int					mapHeight;
	int					tileWidth;
	int					tileHeight;
	
	//
	// Tiles
	//
	int*				tiles;
	int					tilesCount;
	std::vector<int>	normalTiles;		// Indices de tiles
//	std::vector<int>	waterTiles;			// Indices de tiles (agua)
	std::vector<int>	topmostTiles;		// Indices de tiles (arbustos)

	//
	// Mapa para detectar colisiones
	//
	unsigned short*		walkableMask;
	
	//
	// Atributos para controlar la animación del agua
	//
	TimeClock			waterClock;
	int					waterIndex;
public:
	Map(const TmxMap* tmx);
	Map(const std::string& tmxName);
	~Map();
public:
	int getPixelWidth() const { return mapWidth*tileWidth; }
	int getPixelHeight() const { return mapHeight*tileHeight; }
	
	void update(double dt);
	void render(Graphics* gr);
	void renderTopmost(Graphics* gr);
	
	std::vector<int> getTiles(const Rectangle& entityRect, int dx, int dy) const;
	bool tryMoveTank(const Rectangle& entityRect, int dx, int dy) const;
	bool tryMoveBullet(const Rectangle& entityRect, int dx, int dy) const;
	bool tryMoveTankHorz(const Rectangle& entityRect, int dx) const;
	bool tryMoveTankVert(const Rectangle& entityRect, int dy) const;
	
	void breakTile(const Rectangle& entityRect, int dx, int dy, bool strong);
	void replaceTile(int x, int y, int newTile);
	void replaceTile(int x, int y, int currentTile, int newTile);
private:
	void load(const TmxMap* tmx);
	void loadTiles(const TmxMap* tmx);
	void loadObjects(const TmxMap* tmx);
	void drawTile(Graphics* gr, int dx, int dy, int tileX, int tileY, int tileIndex);
	bool tryMove(const Rectangle& entityRect, int dx, int dy, unsigned short mask) const;
	bool tryMoveHorz(const Rectangle& entityRect, int dx, int dy, unsigned short mask) const;
	bool tryMoveVert(const Rectangle& entityRect, int dx, int dy, unsigned short mask) const;
};

#endif
