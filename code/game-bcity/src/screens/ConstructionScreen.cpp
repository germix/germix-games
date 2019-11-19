////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ConstructionScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/ConstructionScreen.h>
#include <src/Config.h>
#include <src/res/ResourceManager.h>
#include <src/Tiles.h>
#include <src/utils.h>
#include <src/base/ListBox.h>
#include <src/base/StringEdit.h>

#include <mach/String.h>
#include <mach/Keyboard.h>
#include <mach/Texture.h>
#include <mach/Graphics.h>

#include <tmx/TmxMap.h>
#include <tmx/layers/TmxPatternLayer.h>
#include <tmx/layers/TmxTilesetLayer.h>

#include <gamelib/Font.h>

#include <tinyxml2/tinyxml2.h>

#define MAX_CURSOR_X		((MAP_WIDTH/8)/2)
#define MAX_CURSOR_Y		((MAP_HEIGHT/8)/2)

#define MAX_TILES			(26*26)
#define MAX_PATTERNS		14

static const int patterns[MAX_PATTERNS][4] =
{
	{ Tiles::TILE_EMPTY,  Tiles::TILE_EMPTY, Tiles::TILE_EMPTY, Tiles::TILE_EMPTY },
	
	{ Tiles::TILE_WALL, Tiles::TILE_WALL, Tiles::TILE_WALL, Tiles::TILE_WALL},
	{ Tiles::TILE_WALL, Tiles::TILE_WALL, Tiles::TILE_EMPTY, Tiles::TILE_EMPTY},
	{ Tiles::TILE_WALL, Tiles::TILE_EMPTY, Tiles::TILE_WALL, Tiles::TILE_EMPTY},
	{ Tiles::TILE_EMPTY, Tiles::TILE_EMPTY, Tiles::TILE_WALL, Tiles::TILE_WALL},
	{ Tiles::TILE_EMPTY, Tiles::TILE_WALL, Tiles::TILE_EMPTY, Tiles::TILE_WALL},
	
	{ Tiles::TILE_METAL, Tiles::TILE_METAL, Tiles::TILE_METAL, Tiles::TILE_METAL},
	{ Tiles::TILE_METAL, Tiles::TILE_METAL, Tiles::TILE_EMPTY, Tiles::TILE_EMPTY},
	{ Tiles::TILE_METAL, Tiles::TILE_EMPTY, Tiles::TILE_METAL, Tiles::TILE_EMPTY},
	{ Tiles::TILE_EMPTY, Tiles::TILE_EMPTY, Tiles::TILE_METAL, Tiles::TILE_METAL},
	{ Tiles::TILE_EMPTY, Tiles::TILE_METAL, Tiles::TILE_EMPTY, Tiles::TILE_METAL},
	
	{ Tiles::TILE_SAND, Tiles::TILE_SAND, Tiles::TILE_SAND, Tiles::TILE_SAND},
	{ Tiles::TILE_GRASS, Tiles::TILE_GRASS, Tiles::TILE_GRASS, Tiles::TILE_GRASS},
	{ Tiles::TILE_WATER, Tiles::TILE_WATER, Tiles::TILE_WATER, Tiles::TILE_WATER},
};

static tinyxml2::XMLElement* newElement(
	tinyxml2::XMLDocument& doc,
	const char* name,
	tinyxml2::XMLElement* parent = 0)
{
	tinyxml2::XMLElement* elem = doc.NewElement(name);
	if(parent)
		parent->LinkEndChild(elem);
	else
		doc.InsertFirstChild(elem);
	return elem;
}
static void writeObject(
	tinyxml2::XMLDocument& doc,
	tinyxml2::XMLElement* objectGroupElement,
	int id,
	int x,
	int y,
	int w,
	int h,
	const char* name,
	const char* type)
{
	tinyxml2::XMLElement* objectElement = newElement(doc, "object", objectGroupElement);
	
	objectElement->SetAttribute("id", id);
	objectElement->SetAttribute("x", x);
	objectElement->SetAttribute("y", y);
	objectElement->SetAttribute("width", w);
	objectElement->SetAttribute("height", h);
	objectElement->SetAttribute("name", name);
	objectElement->SetAttribute("type", type);
}
ConstructionScreen::ConstructionScreen()
: state(STATE_EDIT)
, removable(false)
, tiles(null)
, mapWidth(MAP_WIDTH/8)
, mapHeight(MAP_HEIGHT/8)
, tileWidth(8)
, tileHeight(8)
, cursor(res.findTexture("Cursor"))
, cursorX(0)
, cursorY(0)
, cursorBlinkIndex(0)
, cursorBlinkClock(0.4)
, patternIndex(0)

, fontBlack(res.findFont("Font.Black"))
, fontOrange(res.findFont("Font.Orange"))

, listBox(null)
, stringEdit(null)
{
	newMap();
}
ConstructionScreen::~ConstructionScreen()
{
	delete [] tiles;
}
Screen* ConstructionScreen::getNext()
{
	return null;
}
bool    ConstructionScreen::isRemovable()
{
	return removable;
}
void    ConstructionScreen::show(Machine* mach)
{
}
void    ConstructionScreen::hide(Machine* mach)
{
}
void    ConstructionScreen::update(Machine* mach, double dt)
{
	switch(state)
	{
		case STATE_EDIT:
			updateEdit(dt);
			break;
		case STATE_LOAD:
			updateLoad(dt);
			break;
		case STATE_SAVE:
			updateSave(dt);
			break;
	}
}
void    ConstructionScreen::render(Machine* mach, Graphics* gr)
{
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color(128,128,128));
	
	gr->translate(MAP_X, MAP_Y);
	
	gr->fillRect(0, 0, MAP_WIDTH, MAP_HEIGHT, Config::mapBackgroundColor);
	
	//
	// Dibujar tiles
	//
	for(int tx = 0; tx < mapWidth; tx++)
	{
		for(int ty = 0; ty < mapHeight; ty++)
		{
			if(tiles[(ty*mapWidth)+tx] != Tiles::TILE_EMPTY)
				drawTile(gr, 0, 0, tx, ty, tiles[(ty*mapWidth)+tx]);
		}
	}
	if(state == STATE_EDIT)
	{
		//
		// Dibujar cursor
		//
		if((cursorBlinkIndex&1) == 0)
		{
			gr->drawTexture(cursor, cursorX*16, cursorY*16);
		}
	}
	// ...
	gr->translate(-MAP_X, -MAP_Y);
	{
		int i = 0;
		const int* pat = &patterns[patternIndex][0];

		gr->translate(MAP_X+MAP_WIDTH+8, MAP_Y);
		for(int y = 0; y < 2; y++)
		{
			for(int x = 0; x < 2; x++)
			{
				drawTile(gr, 0, 0, x, y, pat[i++]);
			}
		}
		gr->translate(-(MAP_X+MAP_WIDTH+8), -MAP_Y);
	}
	//
	// ...
	//
	{
		const char* s = "F1-NUEVO  F2-CARGAR  F3-GUARDAR";
		int tx = SCREEN_WIDTH/2 - fontBlack->textWidth(s)/2;
		int ty = MAP_Y+MAP_HEIGHT + ((SCREEN_HEIGHT-MAP_Y-MAP_HEIGHT)/2 - 8/2);
		fontBlack->render(gr, tx, ty, s);
	}
	if(state == STATE_LOAD || state == STATE_SAVE)
	{
		int w = 240;//200;
		int h = 160;
		int x = SCREEN_WIDTH/2 - w/2;
		int y = SCREEN_HEIGHT/2 - h/2;
		
		gr->fillRect(x, y, w, h, Color(98, 98, 98, 200));
		
		if(state == STATE_LOAD)
		{
			listBox->render(gr);
		}
		else
		{
			stringEdit->render(gr, SCREEN_WIDTH/2 - stringEdit->getWidth()/2, SCREEN_HEIGHT/2);
		}
		const char* s = (state == STATE_LOAD ? "CARGAR MAPA" : "GUARDAR MAPA");
		
		fontOrange->render(gr, SCREEN_WIDTH/2 - fontOrange->textWidth(s)/2, y+32, s);
	}
}
void ConstructionScreen::updateEdit(double dt)
{
	if(cursorBlinkClock.update(dt))
	{
		cursorBlinkIndex++;
	}
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		removable = true;
	}
	else if(Keyboard::isPressed(Key::TAB))
	{
		if(Keyboard::isDown(Key::LEFT_SHIFT))
		{
			if(--patternIndex < 0)
			{
				patternIndex = MAX_PATTERNS-1;
			}
		}
		else
		{
			if(++patternIndex == MAX_PATTERNS)
			{
				patternIndex = 0;
			}
		}
	}
	else if(Keyboard::isPressed(Key::SPACE))
	{
		replaceTiles();
	}
	else if(Keyboard::isPressed(Key::UP))
	{
		if(cursorY > 0)
		{
			cursorY--;
			cursorBlinkIndex = 0;
			cursorBlinkClock.reset();
		}
	}
	else if(Keyboard::isPressed(Key::DOWN))
	{
		if(cursorY < MAX_CURSOR_Y-1)
		{
			cursorY++;
			cursorBlinkIndex = 0;
			cursorBlinkClock.reset();
		}
	}
	else if(Keyboard::isPressed(Key::LEFT))
	{
		if(cursorX > 0)
		{
			cursorX--;
			cursorBlinkIndex = 0;
			cursorBlinkClock.reset();
		}
	}
	else if(Keyboard::isPressed(Key::RIGHT))
	{
		if(cursorX < MAX_CURSOR_X-1)
		{
			cursorX++;
			cursorBlinkIndex = 0;
			cursorBlinkClock.reset();
		}
	}
	else if(Keyboard::isPressed(Key::F1))
	{
		newMap();
	}
	else if(Keyboard::isPressed(Key::F2))
	{
		state = STATE_LOAD;
		listBox = new ListBox(
			16+8,
			8*12,
			28,
			9,
			getMapsFromCustomMapsFolder(),
			Color(128,128,128));
	}
	else if(Keyboard::isPressed(Key::F3))
	{
		state = STATE_SAVE;
		stringEdit = new StringEdit(26);
	}
}
void ConstructionScreen::updateLoad(double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		state = STATE_EDIT;
	}
	else if(Keyboard::isPressed(Key::RETURN) || Keyboard::isPressed(Key::KP_ENTER))
	{
		char sz[256];

		sprintf(sz, "bcity/custommaps/%s.tmx", listBox->getSelectedString().toLower().c_str());
		
		loadMap(sz);
		state = STATE_EDIT;
	}
	else
	{
		listBox->update(dt);
	}
}
void ConstructionScreen::updateSave(double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		delete stringEdit;
		state = STATE_EDIT;
	}
	else if(Keyboard::isPressed(Key::RETURN) || Keyboard::isPressed(Key::KP_ENTER))
	{
		char sz[256];

		sprintf(sz, "bcity/custommaps/%s.tmx", stringEdit->getString().toLower().c_str());
		
		saveMap(sz);
		delete stringEdit;
		state = STATE_EDIT;
	}
	else
	{
		stringEdit->update(dt);
	}
}
void ConstructionScreen::newMap()
{
	if(tiles)
		delete [] tiles;
	
	tiles = new int[MAX_TILES];
	memset(tiles, 0, MAX_TILES*sizeof(int));
	
	tiles[661] = Tiles::TILE_WALL;
	tiles[635] = Tiles::TILE_WALL;
	tiles[609] = Tiles::TILE_WALL;
	tiles[610] = Tiles::TILE_WALL;
	tiles[611] = Tiles::TILE_WALL;
	tiles[612] = Tiles::TILE_WALL;
	tiles[638] = Tiles::TILE_WALL;
	tiles[664] = Tiles::TILE_WALL;
}
void ConstructionScreen::loadMap(const char* fileName)
{
	if(tiles)
		delete [] tiles;
	// ...
	TmxMap* tmx = new TmxMap(fileName);
	std::vector<int> gids = tmx->getPatternLayer("map")->getIds();
	int firstGidTileset = tmx->getTilesetLayer("bcity")->getFirstGid();
	
	//
	// Cargar tiles visuales
	//
	tiles = new int[gids.size()];
	for(unsigned int i = 0; i < gids.size(); i++)
	{
		tiles[i] = gids[i]-firstGidTileset;
		if(tiles[i] == -1)
			tiles[i] = 0;
	}
}
void ConstructionScreen::saveMap(const char* fileName)
{
	int firstGid = 1;
	tinyxml2::XMLDocument doc;

	replaceTiles(0, 0, 0);
	replaceTiles(0, 6, 0);
	replaceTiles(0, 12, 0);
	replaceTiles(0, 4, 12);
	replaceTiles(0, 6, 12);
	replaceTiles(0, 8, 12);
	
	tinyxml2::XMLElement* root = newElement(doc, "map");
	root->SetAttribute("version", "1.0");
	root->SetAttribute("orientation", "orthogonal");
	root->SetAttribute("renderorder", "right-down");
	root->SetAttribute("width", "26");
	root->SetAttribute("height", "26");
	root->SetAttribute("tilewidth", "8");
	root->SetAttribute("tileheight", "8");
	root->SetAttribute("nextobjectid", "4");
	
	//
	// Escribir tileset
	//
	tinyxml2::XMLElement* tilesetElement = newElement(doc, "tileset", root);
	tilesetElement->SetAttribute("firstgid", firstGid);
	tilesetElement->SetAttribute("name", "bcity");
	tilesetElement->SetAttribute("tilewidth", "8");
	tilesetElement->SetAttribute("tileheight", "8");
	tilesetElement->SetAttribute("tilecount", "8");
	tilesetElement->SetAttribute("columns", "8");
	
	tinyxml2::XMLElement* tilesetImageElement = newElement(doc, "image", tilesetElement);
	tilesetImageElement->SetAttribute("source", "bcity.png");
	tilesetImageElement->SetAttribute("width", "64");
	tilesetImageElement->SetAttribute("height", "8");

	//
	// Escribir el grupo de objetos
	//
	tinyxml2::XMLElement* objectGroupElement = newElement(doc, "objectgroup", root);
	objectGroupElement->SetAttribute("name", "objects");
	writeObject(doc, objectGroupElement, 1, 96, 192, 16, 16, "bird", "bird");
	writeObject(doc, objectGroupElement, 2, 64, 192, 16, 16, "player1", "player1");
	writeObject(doc, objectGroupElement, 3, 128, 192, 16, 16, "player2", "player2");
	
	//
	// Escribir la capa de tiles
	//
	tinyxml2::XMLElement* layerElement = newElement(doc, "layer", root);
	layerElement->SetAttribute("name", "map");
	layerElement->SetAttribute("width", "26");
	layerElement->SetAttribute("height", "26");
	
	tinyxml2::XMLElement* dataLayerElement = newElement(doc, "data", layerElement);
	dataLayerElement->SetAttribute("encoding", "csv");

	String content;
	for(int i = 0; i < MAX_TILES; i++)
	{
		if((i % mapWidth) == 0)
			content += "\n";
		if(tiles[i] == Tiles::TILE_EMPTY)
			content += "0";
		else
			content += String::fromInt(tiles[i]+firstGid);
		if(i < MAX_TILES-1)
			content += ",";
	}
	content += "\n";
	dataLayerElement->SetText(content.c_str());

	// Guardar
	doc.SaveFile(fileName);
}
void ConstructionScreen::drawTile(Graphics* gr, int dx, int dy, int tileX, int tileY, int tileIndex)
{
	int dx1 = dx + tileX*tileWidth;
	int dy1 = dy + tileY*tileHeight;
	if(tileIndex >= 0)
	{
		int dx2 = dx1+tileWidth;
		int dy2 = dy1+tileHeight;
		int sx1 = (tileIndex%(Config::tileset->getWidth()/tileWidth))*tileWidth;
		int sy1 = (tileIndex/(Config::tileset->getWidth()/tileWidth))*tileWidth;
		int sx2 = sx1+tileWidth;
		int sy2 = sy1+tileHeight;
		
		gr->drawTexture(Config::tileset, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2);
	}
	else
	{
		gr->fillRect(dx1, dy1, tileWidth, tileHeight, Color());
	}
}
void ConstructionScreen::replaceTiles()
{
	replaceTiles(patternIndex, cursorX, cursorY);
}
void ConstructionScreen::replaceTiles(int idx, int curX, int curY)
{
	int i = 0;
	const int* pat = &patterns[idx][0];
	
	for(int y = 0; y < 2; y++)
	{
		for(int x = 0; x < 2; x++)
		{
			int cx = curX*2;
			int cy = curY*2;
			
			tiles[((cy+y)*mapWidth)+(cx+x)] = pat[i++];
		}
	}
}

