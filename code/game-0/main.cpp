#include <mach/Game.h>
#include <mach/Machine.h>
#include <mach/Key.h>
#include <mach/Keyboard.h>
#include <mach/Graphics.h>
#include <mach/TextureLoader.h>

#include <stdio.h>
#include <mach/Vector2f.h>
#include <gamelib/TimeClock.h>

class Game0 : public Game
{
	Texture*	texture;
	TimeClock	clock;
	int			second;
public:
	Game0()
		: clock(1)
		, second(0)
	{
		Vector2f v(1, -1);
		printf("angle: %f\n", v.getAngle());
	}
	~Game0()
	{
		if(texture)
			delete texture;
	}
public:
	virtual void init(Machine* mach)
	{
		texture = TextureLoader::load("0/test.png");
	}
	virtual void close(Machine* mach)
	{
	}
	virtual void update(Machine* mach, double dt)
	{
		if(Keyboard::isPressed(Key::ESCAPE))
		{
			mach->shutdown();
		}
		else if(Keyboard::isPressed(Key::LETTER_A))
		{
			printf("a");
		}
		else if(Keyboard::isReleased(Key::LETTER_A))
		{
			printf("A");
		}
		if(clock.update(dt))
		{
			//if(firstTime == 0)
			{
				//firstTime = System.currentTimeMillis();
			}
			second++;
			printf("segundos=%d", second);
		}
	}
	virtual void render(Machine* mach, Graphics* gr)
	{
		//gr->drawTexture(texture, 0, 0);
	}
};

void main(void)
{
	Machine().start(new Game0(), "Game 0", 800, 600);
}
