////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Mixer
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <gamelib-mixer/Mixer.h>
#include <sdl/SDL_Mixer.h>

#include <stdio.h>
#include <string.h>

//#define MAX_MIX_CHANNELS	24

class Music
{
public:
	Mix_Music*	music;
public:
	Music(Mix_Music* m) : music(m)
	{
	}
	virtual ~Music()
	{
	}
};
class Sound
{
public:
	Mix_Chunk*	chunk;
public:
	Sound(Mix_Chunk* c) : chunk(c)
	{
	}
	virtual ~Sound()
	{
	}
};


static struct
{
	bool playing;
}
channelsInfo[MAX_MIX_CHANNELS];

static void SDLCALL ChannelFinishedCallback(int channel)
{
	channelsInfo[channel].playing = false;
}

void Mixer::run()
{
	memset(channelsInfo, 0, sizeof(channelsInfo));
	//
	// Crear el mixer de audio
	//
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		fprintf(stderr, "Error initializing mixer: %s\n", SDL_GetError());
		return;
	}
	Mix_AllocateChannels(MAX_MIX_CHANNELS);
	Mix_ChannelFinished(ChannelFinishedCallback);
}
void Mixer::halt(int ms)
{
	if(ms == -1)
	{
		Mix_HaltMusic();
		for(int i = 0; i < MAX_MIX_CHANNELS; i++)
			Mix_HaltChannel(i);
	}
	else
	{
		Mix_FadeOutMusic(ms);
		for(int i = 0; i < MAX_MIX_CHANNELS; i++)
			Mix_FadeOutChannel(i, ms);
	}
}
void Mixer::pause()
{
	Mix_PauseMusic();
	for(int i = 0; i < MAX_MIX_CHANNELS; i++)
		Mix_Pause(i);
}
void Mixer::resume()
{
	Mix_ResumeMusic();
	for(int i = 0; i < MAX_MIX_CHANNELS; i++)
		Mix_Resume(i);
}
void Mixer::haltMusic(int ms)
{
	if(ms == 0)
		Mix_HaltMusic();
	else
		Mix_FadeOutMusic(ms);
}
void Mixer::haltChannel(int channel)
{
	if(channel != -1)
		Mix_HaltChannel(channel);
}
void Mixer::playMusic(Music* music, int loops)
{
	if(music)
	{
		Mix_HaltMusic();
		Mix_PlayMusic(music->music, loops);
	}
}
int  Mixer::playChannel(Sound* sound, int channel, int loops)
{
	if(sound)
	{
		channel = Mix_PlayChannel(channel, sound->chunk, loops);
		if(channel != -1)
		{
			channelsInfo[channel].playing = true;
		}
		return channel;
	}
	return -1;
}
bool Mixer::isPlayingChannel(int channel)
{
	return channelsInfo[channel].playing;
}
void Mixer::freeMusic(Music* m)
{
	if(m)
	{
		Mix_FreeMusic(m->music);
		delete m;
	}
}
void Mixer::freeSound(Sound* s)
{
	if(s)
	{
		Mix_FreeChunk(s->chunk);
		delete s;
	}
}
Music* Mixer::loadMusic(const char* fname)
{
	Mix_Music* m = Mix_LoadMUS(fname);
	if(m)
		return new Music(m);
	return null;
}
Sound* Mixer::loadSound(const char* fname)
{
	Mix_Chunk* c = Mix_LoadWAV(fname);
	if(c)
		return new Sound(c);
	return null;
}
