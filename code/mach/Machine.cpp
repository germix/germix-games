////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Machine
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <mach/Machine.h>
#include <mach/Game.h>
#include <mach/Graphics.h>
#include <mach/Mouse.h>

#include <stdio.h>
#include <sdl/sdl.h>
#include <sdl/SDL_Mixer.h>

#include "mach.h"
#include "Fps.h"
#include "Debug.h"

MACHINE mach;
void SDLCALL ChannelFinishedCallback(int channel);

Machine::Machine()
{
}
Machine::~Machine()
{
}
void Machine::start(Game* game, const char* title, int width, int height, int scale, int audioChannels)
{
	Graphics gr;
	Fps fps(60);
	
	memset(&mach, 0, sizeof(mach));
	mach.scale = 1;
	if(scale > 1)
	{
		mach.scale = scale;
		if(scale > 4)
			mach.scale = 4;
	}
	mach.width = width;
	mach.height = height;
	
	//
	// Inicializar SDL
	//
	if(0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO))
	{
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		return;
	}
	//
	// Crear ventana
	//
	if(NULL == (mach.window = SDL_CreateWindow(	title,
												SDL_WINDOWPOS_CENTERED,
												SDL_WINDOWPOS_CENTERED,
												width*mach.scale,
												height*mach.scale,
												SDL_WINDOW_FOREIGN)))
	{
		fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return;
	}
	//
	// Crear el renderer
	//
	if(NULL == (mach.renderer = SDL_CreateRenderer(	mach.window,
												-1,
												SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
	{
		fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(mach.window);
		SDL_Quit();
		return;
	}
	SDL_RenderSetScale(mach.renderer, mach.scale, mach.scale);
#if 0
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"); 
	SDL_RenderSetLogicalSize(mach.renderer, width*mach.scale, height*mach.scale);
	{
		int w, h;
		SDL_GetWindowSize(mach.window, &w, &h);
		printf("width: %d\n", w);
		printf("height: %d\n", h);
	}
#endif
	//
	// Crear el mixer de audio
	//
	if(audioChannels > 0)
	{
		if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
			fprintf(stderr, "Error initializing mixer: %s\n", SDL_GetError());
			
			SDL_DestroyRenderer(mach.renderer);
			SDL_DestroyWindow(mach.window);
			SDL_Quit();
			return;
		}
		mach.audioChannels = new AUDIO_CHANNEL[audioChannels];
		mach.audioChannelsCount = audioChannels;
		memset(mach.audioChannels, 0, audioChannels*sizeof(AUDIO_CHANNEL));
		
		Mix_AllocateChannels(audioChannels);
		Mix_ChannelFinished(ChannelFinishedCallback);
	}
	game->init(this);
	
	fps.init();
	while(!mach.closeRequested)
	{
		SDL_Event e;
		double    dt;
		
		if(fps.tick(&dt))
		{
			for(int i = 0; i < sizeof(mach.keyStatus)/sizeof(KEY_STATUS); i++)
			{
				mach.keyStatus[i].flags &= ~(KEY_FLAG_PRESSED|KEY_FLAG_RELEASED);
				if(mach.keyStatus[i].flags & KEY_FLAG_DOWN)
				{
					mach.keyStatus[i].flags |= KEY_FLAG_REPEATED;
				}
			}
			mach.mouseButtons[MouseButton_Left].pressed = false;
			mach.mouseButtons[MouseButton_Right].pressed = false;
			mach.mouseButtons[MouseButton_Middle].pressed = false;
			mach.mouseButtons[MouseButton_Left].released = false;
			mach.mouseButtons[MouseButton_Right].released = false;
			mach.mouseButtons[MouseButton_Middle].released = false;
			SDL_GetMouseState(&mach.mouseX, &mach.mouseY);
			// ...
			while(SDL_PollEvent(&e))
			{
				if(e.type == SDL_QUIT)
				{
					//mach.closeRequested = true;
				}
				else if(e.type == SDL_KEYUP)
				{
					mach.keyStatus[e.key.keysym.scancode].flags |= KEY_FLAG_RELEASED;
					mach.keyStatus[e.key.keysym.scancode].flags &= ~(KEY_FLAG_DOWN|KEY_FLAG_PRESSED|KEY_FLAG_REPEATED);
				}
				else if(e.type == SDL_KEYDOWN)
				{
					mach.keyStatus[e.key.keysym.scancode].flags |= KEY_FLAG_DOWN|KEY_FLAG_PRESSED;
				}
				else if(e.type == SDL_MOUSEMOTION)
				{
				}
				else if(e.type == SDL_MOUSEBUTTONDOWN)
				{
					switch(e.button.button)
					{
						case SDL_BUTTON_LEFT:
							mach.mouseButtons[MouseButton_Left].down = true;
							mach.mouseButtons[MouseButton_Left].pressed = true;
							break;
						case SDL_BUTTON_RIGHT:
							mach.mouseButtons[MouseButton_Right].down = true;
							mach.mouseButtons[MouseButton_Right].pressed = true;
							break;
						case SDL_BUTTON_MIDDLE:
							mach.mouseButtons[MouseButton_Middle].down = true;
							mach.mouseButtons[MouseButton_Middle].pressed = true;
							break;
					}
				}
				else if(e.type == SDL_MOUSEBUTTONUP)
				{
					switch(e.button.button)
					{
						case SDL_BUTTON_LEFT:
							mach.mouseButtons[MouseButton_Left].down = false;
							mach.mouseButtons[MouseButton_Left].released = true;
							break;
						case SDL_BUTTON_RIGHT:
							mach.mouseButtons[MouseButton_Right].down = false;
							mach.mouseButtons[MouseButton_Right].released = true;
							break;
						case SDL_BUTTON_MIDDLE:
							mach.mouseButtons[MouseButton_Middle].down = false;
							mach.mouseButtons[MouseButton_Middle].released = true;
							break;
					}
				}
			}
			//
			// Actualizar juego
			//
			game->update(this, dt);
			
			//
			// Renderizar juego
			//
			if(fps.canRender() && !mach.closeRequested)
			{
//				SDL_RenderClear(mach.renderer);
				game->render(this, &gr);
				SDL_RenderPresent(mach.renderer);
			}
		}
	}
	game->close(this);

	//
	// Cerrar todo
	//
	delete game;
	
	Mix_CloseAudio();
	delete [] mach.audioChannels;
	
	SDL_DestroyRenderer(mach.renderer);
	SDL_DestroyWindow(mach.window);
	SDL_Quit();
}
void Machine::shutdown()
{
	mach.closeRequested = true;
}
void Machine::sleep(unsigned int ms)
{
	SDL_Delay(ms);
}
void Machine::setTitle(const char* title)
{
	SDL_SetWindowTitle(mach.window, title);
}
int  Machine::getScreenWidth() const
{
	return mach.width;
}
int  Machine::getScreenHeight() const
{
	return mach.height;
}
