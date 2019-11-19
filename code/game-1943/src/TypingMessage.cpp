////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TypingMessage
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/TypingMessage.h>
#include <src/Config.h>

#include <mach/Math.h>

#include <gamelib/Font.h>

TypingMessage::TypingMessage()
: state(STATE_NONE)
, finished(false)

, font(null)
, time(0.1)

, initialY(70)

, lines()

, currentLine(-1)
, currentLineOffset(0)
{
}
TypingMessage::~TypingMessage()
{
}
void TypingMessage::init(int y, Font* f, const char* message)
{
	font = f;
	initialY = y;

	state = STATE_NONE;
	finished = false;
	
	lines.clear();

	currentLine = -1;
	currentLineOffset = 0;

	// ...
	const char* p = message;
	const char* s = message;
	int n;
	char sz[256];
	
	while(*p)
	{
		if(*p == '\n')
		{
			strncpy(sz, s, n = (p-s));
			sz[n] = 0;
			lines.push_back(sz);
			s = p+1;
		}
		p++;
	}
	strncpy(sz, s, n=(p-s));
	sz[n] = 0;
	lines.push_back(sz);
	
	// ...
	selectNextLine();
}
void TypingMessage::update(double dt)
{
	if(!lines.empty())
	{
		switch(state)
		{
			case STATE_NONE:
				break;
			case STATE_SHOW_MESSAGE:
				if(time.update(dt))
				{
					currentLineOffset++;
					if(currentLineOffset > lines[currentLine].size())
					{
						time.reset(0.5);
						state = STATE_CHANGE_MESSAGE;
					}
				}
				break;
			case STATE_CHANGE_MESSAGE:
				if(time.update(dt))
				{
					selectNextLine();
				}
				break;
			case STATE_ENDING_TERMINAL:
				if(time.update(dt))
				{
					finished = true;
					lines.clear();
				}
				break;
		}
	}
}
void TypingMessage::render(Graphics* gr)
{
	int py = initialY;
	std::string txt;
	for(int i = 0; i <= currentLine; i++)
	{
		txt = lines[i];
		if(i == currentLine)
		{
			txt = txt.substr(0, currentLineOffset);
		}
		font->render(gr, (SCENE_WIDTH/2) - (font->textWidth(txt.c_str())/2), py, txt.c_str());

		py += font->fontHeight() + 8;
	}
}
bool TypingMessage::isFinished() const
{
	return finished;
}
void TypingMessage::selectNextLine()
{
	currentLine++;
	if(currentLine >= lines.size())
	{
		time.reset(1.0);
		state = STATE_ENDING_TERMINAL;
		currentLine = lines.size()-1;
	}
	else
	{
		time.reset(0.1);
		state = STATE_SHOW_MESSAGE;
		currentLineOffset = 0;
	}
}
