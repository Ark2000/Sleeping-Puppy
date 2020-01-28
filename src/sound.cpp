#include "sound.h"
#include "position.h"

Music ImportMusicFromFile(const char* path)
{
	assert(POSITION == INIT_);

	return Music(new Music_(Mix_LoadMUS(path)));
}

Sound ImportSoundFromFile(const char* path)
{
	assert(POSITION == INIT_);

	return Sound(new Sound_(Mix_LoadWAV(path)));
}

void PlayMusic(Music mus, int loops)
{
	assert(POSITION != CONFIG_);

	Mix_PlayMusic(mus->data, loops);
}

void PauseMusic()
{
	assert(POSITION != CONFIG_);

	Mix_PauseMusic();
}

void ResumeMusic()
{
	assert(POSITION != CONFIG_);

	Mix_ResumeMusic();
}

int MusicPlaying()
{
	assert(POSITION != CONFIG_);

	return Mix_PlayingMusic();
}

void PlaySound(Sound s, int loops)
{
	assert(POSITION != CONFIG_);

	Mix_PlayChannel(-1, s->data, loops);
}

void SetMusicVolume(int v)
{
	assert(POSITION != CONFIG_);

	if (v < 0) v = 0;
	if (v > 128) v = 128;

	Mix_VolumeMusic(v);
}

void SetSoundVolume(int v)
{
	assert(POSITION != CONFIG_);

	if (v < 0) v = 0;
	if (v > 128) v = 128;

	Mix_Volume(-1, v);
}