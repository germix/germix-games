////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestTypingMessage
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/testing/TestTypingMessage.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <mach/Color.h>
#include <mach/Graphics.h>
#include <mach/Machine.h>

TestTypingMessage::TestTypingMessage()
{
}
TestTypingMessage::~TestTypingMessage()
{
}
void TestTypingMessage::init(Machine* mach)
{
	res.load("1943/resources.xres");
	typingMessage.init(30, res.findFont("font.2"), "UN\nMENSAJE\nDE\nPRUEBA");
//	typingMessage.init(30, res.findFont("font.2"), "UN MENSAJE DE TEXTO MUY PERO QUE MUY LARGO LARGO");
}
void TestTypingMessage::close(Machine* mach)
{
}
void TestTypingMessage::update(Machine* mach, double dt)
{
	typingMessage.update(dt);
	if(typingMessage.isFinished())
	{
		mach->shutdown();
	}
}
void TestTypingMessage::render(Machine* mach, Graphics* gr)
{
	gr->translate(SCENE_X, SCENE_Y);
	gr->fillRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT, Color(120, 120, 120));
	typingMessage.render(gr);
	gr->translate(-SCENE_X, -SCENE_Y);
}
