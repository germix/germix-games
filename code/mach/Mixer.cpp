////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Mixer
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <mach/Mixer.h>
#include <sdl/SDL_Mixer.h>

#include <stdio.h>
#include <string.h>

#include "mach.h"

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

void SDLCALL ChannelFinishedCallback(int channel)
{
	mach.audioChannels[channel].playing = false;
}
void Mixer::halt(int ms)
{
	if(ms == -1)
	{
		Mix_HaltMusic();
		for(int i = 0; i < mach.audioChannelsCount; i++)
			Mix_HaltChannel(i);
	}
	else
	{
		Mix_FadeOutMusic(ms);
		for(int i = 0; i < mach.audioChannelsCount; i++)
			Mix_FadeOutChannel(i, ms);
	}
}
void Mixer::pause()
{
	Mix_PauseMusic();
	for(int i = 0; i < mach.audioChannelsCount; i++)
		Mix_Pause(i);
}
void Mixer::resume()
{
	Mix_ResumeMusic();
	for(int i = 0; i < mach.audioChannelsCount; i++)
		Mix_Resume(i);
}
void Mixer::haltMusic(int ms)
{
	if(ms == 0)
		Mix_HaltMusic();
	else
		Mix_FadeOutMusic(ms);
}
void Mixer::haltChannel(int channel, int ms)
{
	if(channel != -1)
	{
		if(ms == 0)
			Mix_HaltChannel(channel);
		else
			Mix_FadeOutChannel(channel, ms);
	}
}
void Mixer::playMusic(Music* music, int loops)
{
	Mix_HaltMusic();
	if(music)
	{
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
			mach.audioChannels[channel].playing = true;
		}
		return channel;
	}
	return -1;
}
bool Mixer::isPlayingChannel(int channel)
{
	if(channel >= 0 && mach.audioChannelsCount)
		return mach.audioChannels[channel].playing;
	return false;
}
bool Mixer::isFadingIn()
{
	if(MIX_FADING_IN != Mix_FadingMusic())
		return false;
	for(int i = 0; i < mach.audioChannelsCount; i++)
	{
		if(mach.audioChannels[i].playing)
		{
			if(MIX_FADING_IN != Mix_FadingChannel(i))
				return false;
		}
	}
	return true;
}
bool Mixer::isFadingOut()
{
	if(MIX_FADING_OUT != Mix_FadingMusic())
		return false;
	for(int i = 0; i < mach.audioChannelsCount; i++)
	{
		if(mach.audioChannels[i].playing)
		{
			if(MIX_FADING_OUT != Mix_FadingChannel(i))
				return false;
		}
	}
	return true;
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
