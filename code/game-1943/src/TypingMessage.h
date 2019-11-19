////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TypingMessage
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TypingMessage_h___
#define ___TypingMessage_h___
#include <vector>
#include <string>

#include <gamelib/TimeClock.h>

class Font;
class Graphics;

class TypingMessage
{
	enum STATE
	{
		STATE_NONE,
		STATE_SHOW_MESSAGE,
		STATE_CHANGE_MESSAGE,
		STATE_ENDING_TERMINAL,
	};
	STATE						state;
	bool						finished;

	Font*						font;
	TimeClock					time;
	
	int							initialY;
	
	std::vector<std::string>	lines;

	int							currentLine;
	int							currentLineOffset;
	
public:
	TypingMessage();
	~TypingMessage();
public:
	void init(int y, Font* f, const char* message);
	void update(double dt);
	void render(Graphics* gr);
	bool isFinished() const;
private:
	void selectNextLine();
};

#endif

