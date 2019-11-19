////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Mixer
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Mixer_h___
#define ___Mixer_h___

class Music;
class Sound;

class Mixer
{
public:
	static void pause();
	static void resume();
	static void halt(int fadems = -1);
	static void haltMusic(int ms = 0);
	static void haltChannel(int channel, int ms = 0);
	static void playMusic(Music* music, int loops = 0);
	static int  playChannel(Sound* sound, int channel = -1, int loops = 0);
	static bool isPlayingChannel(int channel);
	
	static bool isFadingIn();
	static bool isFadingOut();
public:
	static void freeMusic(Music* m);
	static void freeSound(Sound* s);
	static Music* loadMusic(const char* fname);
	static Sound* loadSound(const char* fname);
};

#endif
