#ifndef ___MACH_H___
#define ___MACH_H___
#include <sdl/SDL.h>

#define KEY_FLAG_DOWN		0x01
#define KEY_FLAG_PRESSED	0x02
#define KEY_FLAG_RELEASED	0x04
#define KEY_FLAG_REPEATED	0x08

struct KEY_STATUS
{
	unsigned int flags;
};
struct AUDIO_CHANNEL
{
	bool playing;
};
struct MOUSE_BUTTON
{
	bool down;
	bool pressed;
	bool released;
};
struct MACHINE
{
	int				scale;
	int				width;
	int				height;
	SDL_Window*		window;
	SDL_Renderer*	renderer;
	bool			closeRequested;
	
	//
	// Graphics
	//
	int				graphicsX;
	int				graphicsY;
	
	//
	// Mouse
	//
	int				mouseX;
	int				mouseY;
	MOUSE_BUTTON	mouseButtons[3];
	
	//
	// Keyboard
	//
	KEY_STATUS		keyStatus[SDL_NUM_SCANCODES];
	
	//
	// Audio mixer
	//
	AUDIO_CHANNEL*	audioChannels;
	int				audioChannelsCount;
};

extern MACHINE mach;

#endif
