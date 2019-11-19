////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Fps
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Fps_h___
#define ___Fps_h___

class Fps
{
public:
	int fps;		// Frames Per Second
	int ups;		// Updates Per Second
	double frameTimer;
	long lastTime;
	long currentTime;
	long nextSecond;
	long diffTime;

	double TARGET_FPS;
	double OPTIMAL_TIME;
public:
	Fps(int fps);
public:
	void init();
	bool tick(double* dt);
	bool canRender();
};

#endif
