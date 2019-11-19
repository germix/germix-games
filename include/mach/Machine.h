////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Machine
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Machine_h___
#define ___Machine_h___

class Game;

class Machine
{
public:
	Machine();
	~Machine();
public:
	void start(Game* game, const char* title, int width, int height, int scale = 1, int audioChannels = 16);
	void shutdown();
	void sleep(unsigned int ms);
	void setTitle(const char* title);
	int  getScreenWidth() const;
	int  getScreenHeight() const;
};

#endif
